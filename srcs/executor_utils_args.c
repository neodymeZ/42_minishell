/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:35:02 by larosale          #+#    #+#             */
/*   Updated: 2020/11/09 09:48:39 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Helper function for "search_path" function.
** Frees the array of strings "p".
*/

static	void	free_splitted(char **p)
{
	char	**tmp;

	if (p == NULL)
		return ;
	tmp = p;
	while (*p != NULL)
		free(*p++);
	free(tmp);
}

/*
** Search executable file with name equal to *arg
** and return freeable pointer to string with path + filename
** (ready to pass to execve()).
** Return NULL if file does not exist.
** We search in $PATH.
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

/*
** Frees the "argv" array after its use.
*/

int		free_argv(int argc, char **argv)
{
	if (!argc)
		return (0);
	while (argc--)
		free(argv[argc]);
	return (0);
}

/*
** Scans arg nodes of a given command and fills the "argv" array of strings
** with arguments.
** Returns 0 if successful, or error number on error.
*/

int		get_argv(t_node *arg, int *argc, char **argv)
{
	int	arg_count;

	*argc = 0;
	arg_count = *argc;
	while (arg)
	{
		if (!(argv[arg_count] = ft_strdup(arg->data)))
			return (errman(ERR_SYS, NULL));
		if (++arg_count >= MAX_ARGS)
			break ;
		arg = arg->next_sibling;
	}
	argv[arg_count] = NULL;
	return (0);
}
