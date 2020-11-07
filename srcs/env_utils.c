/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:14:39 by gejeanet          #+#    #+#             */
/*   Updated: 2020/11/07 14:18:30 by gejeanet         ###   ########.fr       */
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
		if (!ft_strncmp(*env, var, len))
		{
			if (*(*env + len) == '=')
				return (*env + len + 1);
			if (*(*env + len) == '\0')
				return (*env + len);
		}
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

	if ((result = find_var(var, g_env)))
		return (result);
	else if ((result = find_var(var, g_env_local)))
		return (result);
	else
		return (NULL);
}

/*
** Creates environment variable "var" with given "value" (of length "len")
** at a given pointer to the environment array.
** Helper function for the "env_set_var" function.
** Returns 1 on error, or 0 otherwise.
*/

static int		create_var(char *var, char *value, char **env, size_t len)
{
	size_t	new_len;

	if (value == NULL)
		new_len = len + 1;
	else
		new_len = len + ft_strlen(value) + 2;
	if (*env != NULL)
		free(*env);
	if (!(*env = ft_calloc(new_len, 1)))
		errman(ERR_SYS, NULL); 
	ft_strlcpy(*env, var, len + 1);
	if (value == NULL)
		return (0);
	*(*env + len) = '=';
	ft_strlcat(*env, value, new_len);
	return (0);
}


/*
** Sets the "var" variable to the value "value" in the given environment "env".
** If "var" does not exists, it is created with the given value.
** The function returns 1 on error, or 0 otherwise.
*/

int				env_set_var(char *var, char *value, char ***env)
{
	size_t	len;
	int		env_size;
	char	**tmp;

	len = ft_strlen(var);
	env_size = 0;
	tmp = *env;
	while (*tmp != NULL)
	{
		if (!(ft_strncmp(*tmp, var, len)) && ((*(*tmp + len) == '=') || \
												(*(*tmp + len) == '\0')))
		{
			create_var(var, value, tmp, len);
			return (0);
		}
		tmp++;
		env_size++;
	}
	if (!(tmp = ft_realloc(*env, sizeof(char *) * (env_size + 2), \
								sizeof(char *) * (env_size + 1))))
		errman(ERR_SYS, NULL);
	create_var(var, value, tmp + env_size, len);
	*(tmp + env_size + 1) = NULL;
	*env = tmp;
	return (0);
}

/*
** Delete a variable "var" from given environment "env" and returns 0.
** Do nothing if the specified variable does not exist and returns 1.
*/

int				env_del_var(char *var, char **env)
{
	size_t	len;

	if (!var || !env)
		return (1);
	len = ft_strlen(var);
	while (*env != NULL)
	{
		if (!(ft_strncmp(*env, var, len)) && ((*(*env + len) == '=') || \
												(*(*env + len) == '\0')))
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
