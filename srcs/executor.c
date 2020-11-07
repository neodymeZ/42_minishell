/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:51:09 by larosale          #+#    #+#             */
/*   Updated: 2020/11/07 20:27:15 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		run_builtin(char **args, t_node *cmd)
{
	// Is it ok not to check return values? All builtin functions should
	// call errman if it is the case.
//	configure_fds(cmd);
	const t_builtin	funcs[] = { {"exit", ft_exit}, {"cd", ft_cd},
		{"pwd", ft_pwd}, {"env", ft_env}, {"echo", ft_echo},
		{"export", ft_export}, {"unset", ft_unset} };
	int 			i;

	if (cmd)
		;
	i = 0;
	while (i < 7)
	{
		if (!ft_strncmp(*args, funcs[i].cmd, ft_strlen(funcs[i].cmd) + 1))
		{
			configure_fds(cmd);
			funcs[i].builtin_f(args);
//			close_fds(cmd, DUP);
			return (0);
		}
		i++;
	}
	return (1);
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
	if (!run_builtin(argv, cmd))
		return (free_argv(argc, argv));
	if ((child_pid = fork()) < 0)
		return (errman(ERR_SYS));
	else if (child_pid == 0)
		exec_cmd(argv, cmd);
	else
	{
		close_fds(cmd, NODUP);
		set_signals(SIGNAL_SET_WAIT);
		if (waitpid(child_pid, &stat_loc, WUNTRACED) < 0)
			return (errman(ERR_SYS));
		set_signals(SIGNAL_SET);
	}
	free_argv(argc, argv);
	return (0);
}

int		run_pipe(t_node *pipe)
{
	t_node	*child;

	// Add errman call
	if (!pipe || !(child = pipe->first_child))
		return (1);
	create_pipes(pipe);
	while (child)
	{
//		printf("Child fd_in: %d, fd_out: %d, fd to close: %d, fd to close: %d\n", child->fd_in, child->fd_out, child->fd1_close, child->fd2_close);
		if (child->type == NODE_CMD)
			run_simplecom(child);
		child = child->next_sibling;
	}
	return (0);
	// close fds
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
