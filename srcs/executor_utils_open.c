/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_open.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/12 00:49:43 by larosale          #+#    #+#             */
/*   Updated: 2020/11/12 00:49:45 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** For each command in pipe opens a pipe and fills the information about pipes
** to the command structure.
** fd1_close and fd2_close parameters describe the FDs to be closed by a child
** process, as they are used by other processes on the other ends of the
** pipes.
** fd_in and fd_out are the file descriptors of opened pipes for a given
** command.
** Returns 0 on error or calls errman on error.
*/

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
//		printf("Fds after creating pipes: %d, %d\n", child->fd_in, child->fd_out);
		child = child->next_sibling;
	}
	return (0);
}

/*
** Helper function for "create_files" function.
** Opens files based on the node type and sets the respective
** parameters in the "cmd" structure.
** If some file descriptors were already specified - closes them.
** Returns 0 on success, or calls errman on error.
*/

static int		open_files(t_node *cmd, t_node *child)
{
	char	*filename;
	int		fd;
	int		prev_fd;
	
	fd = 0;
	prev_fd = (child->type == NODE_REDIR_IN ? cmd->fd_in : cmd->fd_out);
	if (prev_fd != 0 && prev_fd != 1)
		close(prev_fd);
	filename = child->next_sibling->data;
	if (child->type == NODE_REDIR_IN)
		fd = open(filename, O_RDONLY);
	else if (child->type == NODE_REDIR_OUT)
		fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	else if (child->type == NODE_REDIR_APP)
		fd = open(filename, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (fd == -1)
		errman(ERR_SYS, NULL);
	if (child->type == NODE_REDIR_IN)
		cmd->fd_in = fd;
	else
		cmd->fd_out = fd;
	cmd->fd1_close == fd ? cmd->fd1_close = 0 : 0;
	cmd->fd2_close == fd ? cmd->fd2_close = 0 : 0;
	return (0);
}

/*
** Traverses through the arguments of "cmd" subtree and opens all files,
** specified after nodes of redirection types (NODE_REDIR_IN, NODE_REDIR_OUT,
** NODE_REDIR_APP).
** If any file descriptors were already specified for the cmd (e.g. by open
** pipe, or previous redirection), they are overwritten.
** Returns 0 on success, errors are handled by helper function.
*/

int		create_files(t_node *cmd)
{
	t_node *child;

	if (!cmd || !(child = cmd->first_child))
		return (0);
	while (child)
	{
		if (child->next_sibling && (child->type == NODE_REDIR_IN ||
			child->type == NODE_REDIR_OUT ||
			child->type == NODE_REDIR_APP))
		{
			open_files(cmd, child);
		}
		child = child->next_sibling;
	}
	return (0);
}
