/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:14:39 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/27 03:35:24 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Finds the variable "var" in a given environment "env" and returns a
** pointer to its value, or NULL if the variable was not found.
*/

static	char	*find_var(char *var, char **env)
{
	size_t	len;

	if (env == NULL || var == NULL)
		return (NULL);
	len = ft_strlen(var);
	while (*env != NULL)
	{
		if (!ft_strncmp(*env, var, len) && *(*env + len) == '=')
			return (*env + len + 1);
		env++;
	}
	return (NULL);
}

/*
** Returns a pointer to the variable "var" value.
** Search is performed in both local and global env contexts.
** The returned pointer MUST NOT be passed to free() !!!
** Returns NULL if variable does not exist.
*/

char			*env_get_var(char *var)
{
	char	*result;

	if ((result = find_var(var, g_env)) != NULL)
		return (result);
	else if ((result = find_var(var, g_env_local)) != NULL)
		return (result);
	else
		return (NULL);
}

/*
** Sets the "var" variable to the value "value" in the given environment "env".
** If "var" does not exists, it is created with the given value.
** The function returns 1 on error, or 0 otherwise.
*/

int				env_set_var(char *var, char *value, char **env)
{
	size_t	len;
	size_t	new_len;
	int		env_size;
	char	**tmp;

	len = ft_strlen(var);
	env_size = 0;
	new_len = len + ft_strlen(value) + 1;
	tmp = env;
	while (*env != NULL)
	{
		if (!(ft_strncmp(*env, var, len)) && (*(*env + len) == '='))
		{
			free(*env);
			if (!(*env = ft_calloc(new_len, 1)))
				return(errman(ERR_SYS)); 
			ft_strlcpy(*env, var, len + 1);
			*(*env + len) = '=';
			ft_strlcat(*env, value, new_len + 1);
			return (0);
		}
		env++;
		env_size++;
	}
	env = tmp;
	if (!(tmp = ft_realloc(env, sizeof(char *) * (env_size + 2), sizeof(char *) * (env_size + 1))))
		return (errman(ERR_SYS));
	if (!(*(env + env_size) = ft_calloc(new_len, 1)))
		return (errman(ERR_SYS));
	ft_strlcpy(*(env + env_size), var, len + 1);
	*(*(env + env_size) + len) = '=';
	ft_strlcat(*(env + env_size), value, new_len + 1);
	return (0);
}

/*
** Deletes a variable "var" from given environment "env" and returns 0.
** Does nothing if the specified variable does not exist and returns 1.
*/

int				env_del_var(char *var, char **env)
{
	size_t	len;

	len = ft_strlen(var);
	while (*env != NULL)
	{
		if (!(ft_strncmp(*env, var, len)) && ((*(*env + len) == '=')))
		{
			free(*env);
			while (*env != NULL)
			{
				*env = *(env + 1);
				env++;
			}
			return (0);
		}
		env++;
	}
	return (1);
}
