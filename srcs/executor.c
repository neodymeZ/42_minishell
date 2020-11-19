/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:51:09 by larosale          #+#    #+#             */
/*   Updated: 2020/11/19 12:53:34 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Helper function to run a simple command (SIMPLECOM subtree) of AST.
** First, the function generates an argv array to be passed further.
** Second, if it executes not in pipe, the builtin functions are launched
** from the parent process (if any).
** Otherwise, for external commands, or builtins in pipe, a child process is
** spawned, and the commands are executed using the "spawn_child" function.
** Returns 0 on success, or calls errman on error.
*/

static int	run_simplecom(t_node *cmd, int flag)
{
	t_node		*arg;
	int			argc;
	char		*argv[MAX_ARGS + 1];
	t_builtin_f	f;

	argc = 0;
	if (!cmd || !(arg = cmd->first_child) ||
		get_argv(arg, &argc, argv) || create_files(cmd))
		return (free_argv(argc, argv));
	if (!flag && is_builtin(argv, flag, &f))
	{
		if (configure_fds(cmd))
			return (free_argv(argc, argv));
		g_status = f(argv);
		close_fds(cmd);
		free_argv(argc, argv);
		return (0);
	}
	if (spawn_child(argv, cmd))
		return (free_argv(argc, argv));
	free_argv(argc, argv);
	return (0);
}

/*
** Helper functions for the "run_ast" function.
** Launches commands in a PIPE subtree of AST.
** Returns 0 on success, or calls errman or error.
*/

static int	run_pipe(t_node *pipe)
{
	t_node	*child;

	if (!pipe || !(child = pipe->first_child))
		return (1);
	if (create_pipes(pipe))
		return (1);
	while (child)
	{
		if (child->type == NODE_CMD)
		{
			if (run_simplecom(child, IN_PIPE))
				return (1);
		}
		child = child->next_sibling;
	}
	return (0);
}

/*
** Traverses the abstract syntax tree and launches the commands it contains.
** To do so, iterates over the root (SEMIC) children (PIPE or SIMPLECOM) and
** launches the respective helper functions.
** Returns 0 on success or 1 on error.
*/

int			run_ast(t_node *ast)
{
	t_node	*child;
	int		saved_fds[2];
	int		res;

	if (!ast || !(child = ast->first_child) || save_fds(saved_fds))
		return (1);
	while (child)
	{
		if (child->type == NODE_PIPE)
			res = run_pipe(child);
		else
			res = run_simplecom(child, NOT_PIPE);
		child->type == NODE_PIPE ? restore_fds(child->first_child, saved_fds) :
			restore_fds(child, saved_fds);
		if (res)
			return (close_saved_fds(saved_fds));
		child = child->next_sibling;
	}
	close_saved_fds(saved_fds);
	return (0);
}
