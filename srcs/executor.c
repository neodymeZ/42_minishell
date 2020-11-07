/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:51:09 by larosale          #+#    #+#             */
/*   Updated: 2020/11/07 14:22:44 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_builtin(char **command)
{
	// Is it ok not to check return values? All builtin functions should
	// call errman if it is the case.
	if (!ft_strncmp(*command, "exit", 5))
		ft_exit();
	else if (!ft_strncmp(*command, "cd", 3))
		ft_cd(command);
	else if (!ft_strncmp(*command, "pwd", 4))
	{
		ft_pwd();
		ft_putchar_fd('\n', 1);
	}
	else if (!ft_strncmp(*command, "env", 4))
		ft_env();
	else if (!ft_strncmp(*command, "echo", 5))
		ft_echo(command);
	else if (!ft_strncmp(*command, "export", 7))
		ft_export(command);
	else if (!ft_strncmp(*command, "unset", 6))
		ft_unset(command);
	else
		return (1);
	return (0);
}

int 	run_simplecom(t_node *cmd)
{
	t_node	*arg;
	int		argc;
	char	*argv[MAX_ARGS + 1];
	pid_t	child_pid;
	int		stat_loc;

	// Add errman
	if (!cmd || !(arg = cmd->first_child))
		return (1);
	get_argv(arg, &argc, argv);
	if (!run_builtin(argv))
		return (free_argv(argc, argv));
	if ((child_pid = fork()) < 0)
		errman(ERR_SYS, NULL);
	else if (child_pid == 0 && !set_signals(SIGNAL_DFL))
		exec_cmd(argv);
	else
	{
		set_signals(SIGNAL_IGN);
		// waitpid returns pid of child process, if it exited. If it happens, we can then work with the return code, etc.
		if (waitpid(child_pid, &stat_loc, WUNTRACED) < 0)
			errman(ERR_SYS, NULL);
		set_signals(SIGNAL_SET);
	}
	free_argv(argc, argv);
	return (0);
}

int		run_pipe(t_node *pipe)
{
	t_node *child;

	// Add errman call
	if (!pipe || !(child = pipe->first_child))
		return (1);
	while (child)
	{
		if (child->type == NODE_CMD)
			run_simplecom(child);
		child = child->next_sibling;
	}
	return (0);
}

int		run_ast(t_node *ast)
{
	t_node	*child;

	// Add errman call
	if (!ast || !(child = ast->first_child))
		return (0);
	while (child)
	{
		if (child->type == NODE_PIPE)
			run_pipe(child);
		else
			run_simplecom(child);
		child = child->next_sibling;
	}
	return (0);
}
