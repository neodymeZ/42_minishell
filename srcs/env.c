/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 13:51:28 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/26 21:26:54 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees the memory of global (or local - see args) environment table
** (g_env or g_env_local global variables).
*/

void			env_free(char **env)
{
	char	**tmp;

	tmp = env;
	if (tmp == NULL)
		return ;
	while (*tmp != NULL)
	{
		free(*tmp);
		tmp++;
	}
	free(env);
}

/*
** Copies the array of strings "env" to the given array of strings "env_copy".
*/

static	char	**do_copy(char **env_copy, char **env)
{
	char	**tmp;

	tmp = env_copy;
	while (*env != NULL)
	{
		if (!(*tmp = ft_strdup(*env)))
			return (errman(ERR_SYS) ? NULL : NULL);
		tmp++;
		env++;
	}
	*tmp = NULL;
	return (env_copy);
}

/*
** Copies the environment variables' array to a new array and returns
** a pointer to the new array, or NULL on error.
*/

char			**env_init(char **env)
{
	char	**env_copy;
	char	**tmp;
	int		i;

	if (env == NULL)
		return (NULL);
	i = 0;
	tmp = env;
	while (*tmp++ != NULL)
		i++;
	if (!(env_copy = malloc((i + 1) * sizeof(char *))))
	{
		errman(ERR_SYS);
		return (NULL);
	}
	if (!do_copy(env_copy, env))
		return (NULL);
	return (env_copy);
}
