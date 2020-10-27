/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:51:09 by larosale          #+#    #+#             */
/*   Updated: 2020/10/27 19:41:55 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argv(int argc, char **argv)
{
	if (!argc)
		return ;
	while (argc--)
		free(argv[argc]);
	return ;
}

int		exec_cmd(char **argv)
{
//	char	*path;

	if (1)
//	if (ft_strchr(argv[0], '/'))
	{
		if (execve(argv[0], argv, g_env) < 0)
			return (errman(ERR_SYS));
	}
// Implement searching in $PATH
/*	else
	{
		// Add err man (executable not found)
		if (!(path = search_path(argv[0])))
			return (1);
		if (execve(path, argv, g_env) < 0)
			return (errman(ERR_SYS));
		free(path);
	}
*/	return (0);
}

int		run_builtin(char **command, int gnl_result)
{
	// Ctrl-D handling
	if (!(*command) && gnl_result)
		return (0);
	else if ((!gnl_result && !(*command)) || !ft_strncmp(*command, "exit", 5))
		ft_exit();
	else if (!ft_strncmp(*command, "cd", 3))
	{
		if (ft_cd(command))
			return (errman(ERR_SYS));
		return (0);
	}
	else if (!ft_strncmp(*command, "pwd", 4))
	{
		if (ft_pwd())
			return (errman(ERR_SYS));
		ft_putchar_fd('\n', 1);
		return (0);
	}
	else if (!ft_strncmp(*command, "env", 4))
	{
		if (ft_env())
			return (errman(ERR_SYS));
		return (0);
	}
	else if (!ft_strncmp(*command, "echo", 5))
	{
		if (ft_echo(command))
			return (errman(ERR_SYS));
		return (0);
	}
	else if (!ft_strncmp(*command, "export", 7))
	{
		ft_export(command);
		return (0);
	}
	else if (!ft_strncmp(*command, "unset", 6))
	{
		ft_unset(command);
		return (0);
	}
	return (-1);
}

int 	run_simplecom(t_node *node, int gnl_res)
{
	t_node	*child;
	int		argc;
	char	*argv[MAX_ARGS + 1];
	pid_t	child_pid;
	int		stat_loc;

	// Add errman
	if (!node || !(child = node->first_child))
		return (1);
	argc = 0;
	while (child)
	{
		if (!(argv[argc] = ft_strdup(child->data)))
			return (errman(ERR_SYS));
		if (++argc >= MAX_ARGS)
			break ;
		child = child->next_sibling;
	}
	argv[argc] = NULL;
	// Pass GNL result to run_builtin to handle Ctrl-D?
	if (!run_builtin(argv, gnl_res))
	{
		free_argv(argc, argv);
		return (0);
	}
	// Fork main process
	if ((child_pid = fork()) < 0)
		return (errman(ERR_SYS));
	else if (child_pid == 0)
	{
		// Execute command in child process
		exec_cmd(argv);
	}
	else
	{
		signal(SIGINT, SIG_IGN);
		signal(SIGQUIT, SIG_IGN);
		signal(SIGTERM, SIG_IGN);
		// Wait for child process in the parent (main) process
		if (waitpid(child_pid, &stat_loc, WUNTRACED) < 0)
			return (errman(ERR_SYS));
		if (signal(SIGINT, signal_handler) == SIG_ERR)
			return (errman(ERR_SYS));
		if (signal(SIGQUIT, signal_handler) == SIG_ERR)
			return (errman(ERR_SYS));
		if (signal(SIGTERM, SIG_IGN) == SIG_ERR)
			return (errman(ERR_SYS));
	}
	free_argv(argc, argv);
	return (0);
}
