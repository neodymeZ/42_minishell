/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_io.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 03:34:21 by larosale          #+#    #+#             */
/*   Updated: 2020/11/09 09:51:14 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		create_pipes(t_node *pipe_node)
{
	t_node	*child;
	int		pipe_fd[2];

	child = pipe_node->first_child;
	while (child)
	{
		if (child->next_sibling)
		{
			if (pipe(pipe_fd))
				return (errman(ERR_SYS, NULL));
			child->fd_out = pipe_fd[1];
			child->next_sibling->fd_in = pipe_fd[0];
			child->fd1_close = pipe_fd[0];
			child->next_sibling->fd2_close = pipe_fd[1];
		}
		child = child->next_sibling;
	}
	return (0);
}

int		configure_fds(t_node *cmd)
{
	if (cmd->fd1_close)
		close(cmd->fd1_close);
	if (cmd->fd2_close)
		close(cmd->fd2_close);
	if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
		return (errman(ERR_SYS, NULL));
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
		return (errman(ERR_SYS, NULL));
	return (0);
}

int		close_fds(t_node *cmd)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	return (0);
}
