/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:51:09 by larosale          #+#    #+#             */
/*   Updated: 2020/11/08 18:52:55 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	capture_status(int status)
{
	if (WIFEXITED(status))
		g_status = WEXITSTATUS(status);
	return (0);
}

int	run_builtin(char **argv, int flag)
{
	const t_builtin	funcs_notpipe[] = { {"exit", ft_exit}, {"cd", ft_cd},
		{"pwd", ft_pwd}, {"env", ft_env}, {"echo", ft_echo},
		{"export", ft_export}, {"unset", ft_unset} };
	const t_builtin	funcs_pipe[] = { {"exit", ft_test}, {"cd", ft_cd},
		{"pwd", ft_pwd}, {"env", ft_env}, {"echo", ft_echo},
		{"export", ft_export}, {"unset", ft_unset} };
	t_builtin		*funcs;
	int 			i;

	i = 0;
	if (flag)
		funcs = (t_builtin *)funcs_pipe;
	else
		funcs = (t_builtin *)funcs_notpipe;
	while (i < 7)
	{
		if (!ft_strncmp(*argv, funcs[i].cmd, ft_strlen(funcs[i].cmd) + 1))
		{
			g_status = funcs[i].builtin_f(argv);
			return (0);
		}
		i++;
	}
	return (1);
}

static int 	run_simplecom(t_node *cmd, int flag)
{
	t_node	*arg;
	int		argc;
	char	*argv[MAX_ARGS + 1];

	// Add errman
	if (!cmd || !(arg = cmd->first_child))
		return (1);
	get_argv(arg, &argc, argv);
	if (!flag && !run_builtin(argv, flag))
		return (free_argv(argc, argv));
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
