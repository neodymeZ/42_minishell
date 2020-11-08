/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:51:09 by larosale          #+#    #+#             */
/*   Updated: 2020/11/08 02:25:33 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int 	run_simplecom(t_node *cmd, int flag)
{
	t_node	*arg;
	int		argc;
	char	*argv[MAX_ARGS + 1];

	// Add errman
	if (!cmd || !(arg = cmd->first_child))
		return (1);
	get_argv(arg, &argc, argv);
	if (!flag && !ft_strncmp(arg->data, "exit", 5))
		ft_exit(argv);
	else
		spawn_child(argv, cmd);
	free_argv(argc, argv);
	return (0);
}

static int		run_pipe(t_node *pipe)
{
	t_node	*child;

	// Add errman call
	if (!pipe || !(child = pipe->first_child))
		return (1);
	create_pipes(pipe);
	while (child)
	{
		if (child->type == NODE_CMD)
			run_simplecom(child, IN_PIPE);
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
			run_simplecom(child, NOT_PIPE);
		child = child->next_sibling;
	}
	return (0);
}
