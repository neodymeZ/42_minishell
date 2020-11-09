/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_spawn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:45:24 by larosale          #+#    #+#             */
/*   Updated: 2020/11/09 09:26:52 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int	exec_cmd(char **argv)
{
	char	*path;

	if (ft_strchr(argv[0], '/'))
	{
		if (execve(argv[0], argv, g_env) < 0)
			errman(ERR_NOFDIR, argv[0]);
	}
	else
	{
		if (!(path = search_path(argv[0])))
			errman(ERR_NOCMD, argv[0]);
		if (execve(path, argv, g_env) < 0)
			errman(ERR_SYS, NULL);
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
		return (errman(ERR_SYS, NULL));
	else if (child_pid == 0)
	{
		set_signals(SIGNAL_DFL);
		configure_fds(cmd);
		if (run_builtin(argv, IN_PIPE))
			exec_cmd(argv);
		exit(g_status);
	}
	else
 	{   
 		close_fds(cmd);
		set_signals(SIGNAL_SET_WAIT);
 		if (waitpid(child_pid, &stat_loc, WUNTRACED) < 0)
			return (errman(ERR_SYS, NULL));
		capture_status(stat_loc);
		set_signals(SIGNAL_SET);
 	}
	return (stat_loc);
}
