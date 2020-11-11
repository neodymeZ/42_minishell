/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_spawn.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 00:45:24 by larosale          #+#    #+#             */
/*   Updated: 2020/11/12 01:05:31 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Helper function to save the exit status to "g_status" global variable.
*/

static int	capture_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	return (0);
}

/*
** Helper function to launch an external command.
** If no '/' symbols exist in first command argument, $PATH is searched
** for executable.
*/

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

/*
** Spawns a child process by forking the minishell process.
** In child process, signal handling is reset to default, then file
** descriptors are configured in accordance with the "cmd" parameters.
** After that, a builtin function or external command is launched.
** Parent process closes file descriptors used in child (for SIGPIPE to work),
** sets signals to the WAIT configuration, then waits for the child.
** After child process termination, parent captures the child exit status
** to "g_status" global variable and sets default signal configuration.
*/

int		spawn_child(char **argv, t_node *cmd)
{
	int     stat_loc;
	pid_t	child_pid;
	t_builtin_f	f;

	stat_loc = 0;
	if ((child_pid = fork()) < 0)
		return (errman(ERR_SYS, NULL));
	else if (child_pid == 0)
	{
		set_signals(SIGNAL_DFL);
		configure_fds(cmd);
		if (is_builtin(argv, IN_PIPE, &f))
			g_status = f(argv);
		else
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
