/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_io.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 03:34:21 by larosale          #+#    #+#             */
/*   Updated: 2020/11/12 00:48:39 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Configures file descriptors for use.
** If file descriptors to be closed were specified - they are closed first.
** Then the dup2 call closes standard descriptors and points them to the
** objects, pointed to by custom file descriptors.
*/

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

/*
** Closes file descriptors used by a command
*/

int		close_fds(t_node *cmd)
{
	if (cmd->fd_in != 0)
		close(cmd->fd_in);
	if (cmd->fd_out != 1)
		close(cmd->fd_out);
	return (0);
}

/*
** Restores file descriptor configuration after running a command.
** Uses previously saved STDIN and STDOUT (in "saved_fds").
** Iterates through command siblings and closes all open fds.
*/

int		restore_fds(t_node *cmd, int *saved_fds)
{
	if (dup2(*saved_fds, STDIN_FILENO) < 0 ||
		dup2(*(saved_fds + 1), STDOUT_FILENO) < 0)
		errman(ERR_SYS, NULL);
	while (cmd)
	{
		close_fds(cmd);
		cmd = cmd->next_sibling;
	}
	close(*saved_fds);
	close(*(saved_fds + 1));
	return (0);
}
