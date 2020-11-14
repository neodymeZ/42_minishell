/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_args.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:35:02 by larosale          #+#    #+#             */
/*   Updated: 2020/11/14 03:01:11 by larosale         ###   ########.fr       */
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
	struct stat		sb;

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

int				free_argv(int argc, char **argv)
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
** Skips REDIR nodes.
** Returns 0 if successful, or error number on error.
*/

int				get_argv(t_node *arg, int *argc, char **argv)
{
	int	arg_count;

	*argc = 0;
	arg_count = *argc;
	while (arg)
	{
		if (arg->type == NODE_REDIR_IN || arg->type == NODE_REDIR_OUT ||
			arg->type == NODE_REDIR_APP)
		{
			arg = arg->next_sibling->next_sibling;
			if (!arg)
				break ;
			continue ;
		}
		if (!(argv[arg_count] = ft_strdup(arg->data)))
			return (errman(ERR_SYS, NULL));
		if (++arg_count >= MAX_ARGS)
			break ;
		arg = arg->next_sibling;
	}
	argv[arg_count] = NULL;
	return (0);
}

/*
** Helper function which returns a pointer to the builtin function.
** It uses two different arrays of structures with pointers to the builtin
** functions, one for executing in the child process (in pipe), second for
** executing in parent process (not in pipe).
*/

int		is_builtin(char **argv, int flag, t_builtin_f *f)
{
	const t_builtin	funcs_notpipe[] = { {"exit", ft_exit}, {"cd", ft_cd},
		{"pwd", ft_pwd}, {"env", ft_env}, {"echo", ft_echo},
		{"export", ft_export}, {"unset", ft_unset} };
	const t_builtin	funcs_pipe[] = { {"exit", ft_exit_pipe}, {"cd", ft_cd},
		{"pwd", ft_pwd}, {"env", ft_env}, {"echo", ft_echo},
		{"export", ft_export}, {"unset", ft_unset} };
	t_builtin		*funcs;
	int 			i;

	i = 0;
	*f = NULL;
	funcs = (flag ? (t_builtin *)funcs_pipe : (t_builtin *)funcs_notpipe);
	while (i < 7)
	{
		if (!ft_strncmp(*argv, funcs[i].cmd, ft_strlen(funcs[i].cmd) + 1))
		{
			*f = funcs[i].f;
			return (1);
		}
		i++;
	}
	return (0);
}
