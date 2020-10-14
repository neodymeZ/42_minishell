/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 13:51:28 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/14 15:29:19 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	**do_copy(char **env_copy, char **env)
{
	char	**tmp;

	tmp = env_copy;
	while (*env != NULL)
	{
		*tmp = ft_strdup(*env);
		if (*tmp == NULL)
		{
			while (tmp != env_copy)
			{
				tmp--;
				free(*tmp);
			}
			free(tmp);
			return (NULL);
		}
		tmp++;
		env++;
	}
	*tmp = NULL;
	return (env_copy);
}

void			env_free(char **env)
{
	char	**tmp;

	tmp = env;
	if (tmp == NULL)
		return;
	while (*tmp != NULL)
	{
		free(*tmp);
		tmp++;
	}
	free(env);
}

/*
** make a copy of given environment and return a pointer to it
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
	if ((env_copy = (char **)malloc((i + 1) * sizeof(char *))) == NULL)
	{
		errman(ERR_SYS);
		return (NULL);
	}
	if (do_copy(env_copy, env) == NULL)
	{
		errman(ERR_SYS);
		return (NULL);
	}
	return (env_copy);
}
