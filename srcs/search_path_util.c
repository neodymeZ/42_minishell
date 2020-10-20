/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search_path_util.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 20:52:10 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/20 23:47:51 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char	**g_env;
/*
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
*/
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
//	char			**tmp;
	char			*result;
	struct	stat	sb;

	char	*rrr;
	rrr = env_get_var("PATH");
	write(1, rrr, ft_strlen(rrr));

	if ((p = ft_split(env_get_var("PATH"), ':')) == NULL || *p == NULL) 
		return (NULL);
	ft_putstr_fd(arg, 2);
//	tmp = p;
	while (*p != NULL)
	{
		ft_putstr_fd(*p, 2);
		ft_putstr_fd("\n", 2);
		result = ft_strjoin(*p, arg);
		ft_putstr_fd(result, 2);
		if (stat(result, &sb) == 0)
		{
			if ((sb.st_mode & S_IFMT) == S_IFREG)
				break ;
//			else
//				free(result);
		}
		p++;
	}
//	free_splitted(tmp);
	return (result);
}
