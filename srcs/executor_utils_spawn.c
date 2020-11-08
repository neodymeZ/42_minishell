/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_spawn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:45:24 by larosale          #+#    #+#             */
/*   Updated: 2020/11/08 13:29:00 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_builtin(char **argv)
{
	const t_builtin	funcs[] = { {"exit", ft_test}, {"cd", ft_cd},
		{"pwd", ft_pwd}, {"env", ft_env}, {"echo", ft_echo},
		{"export", ft_export}, {"unset", ft_unset} };
	int 			i;

	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(*argv, funcs[i].cmd, ft_strlen(funcs[i].cmd) + 1))
		{
			funcs[i].builtin_f(argv);
			return (0);
		}
		i++;
	}
	return (1);
}

static int	exec_cmd(char **argv)
{
	char	*path;

	if (ft_strchr(argv[0], '/'))
	{
		if (execve(argv[0], argv, g_env) < 0)
			return (errman(ERR_SYS));
	}
	else
	{
		// Add err man (executable not found)
		if (!(path = search_path(argv[0])))
			return (errman(ERR_NOCMD));
		if (execve(path, argv, g_env) < 0)
			return (errman(ERR_SYS));
		free(path);
	}
	return (0);
}

int		spawn_child(char **argv, t_node *cmd)
{
	int     stat_loc;
	pid_t	child_pid;

	stat_loc = 0;
	if ((child_pid = fork()) < 0)
		return (errman(ERR_SYS));
	else if (child_pid == 0)
	{
		set_signals(SIGNAL_DFL);
		configure_fds(cmd);
		if (exec_builtin(argv))
			exec_cmd(argv);
		exit(0);
	}
	else
 	{   
 		close_fds(cmd);
		set_signals(SIGNAL_SET_WAIT);
 		if (waitpid(child_pid, &stat_loc, WUNTRACED) < 0)
			return (errman(ERR_SYS));
		set_signals(SIGNAL_SET);
 	}
	return (stat_loc);
}

