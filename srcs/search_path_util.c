/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:52:10 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/21 11:01:33 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char	**g_env;

static	void	free_splitted(char **p)
{
	char	**tmp;

	if (p == NULL)
		return;
	tmp = p;
	while (*p != NULL)
		free(*p++);
	free(tmp);
}

/*
** search executable file with name equal to *arg
** and return feeable pointer to string with path + filename
** (ready to pass to execve()).
** Return NULL if file does not exist.
** We search in $PATH first, then (if search failed),
** we search in current directory.
** ATTENTION!!!  returned path MAY be relative path (or absolute)
** because in the PATH env variable we can store path of ANY type
*/

char			*search_path(char *arg)
{
	char			**p;
	char			**tmp;
	char			*result;
	char			*result_tmp;
	struct	stat	sb;

	if ((p = ft_split(env_get_var("PATH"), ':')) == NULL || *p == NULL) 
		return (NULL);
	tmp = p;
	while (*p != NULL)
	{
		result_tmp = ft_strjoin(*p, "/");
		result = ft_strjoin(result_tmp, arg);
		free(result_tmp);
		if (stat(result, &sb) == 0)
		{
			if ((sb.st_mode & S_IFMT) == S_IFREG)
				break ;
		}
		free(result);
		result = NULL;
		p++;
	}
	free_splitted(tmp);
	return (result);
}
