/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor_utils_fildes.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/07 03:34:21 by larosale          #+#    #+#             */
/*   Updated: 2020/11/18 18:09:00 by larosale         ###   ########.fr       */
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
	{
		errman(ERR_SYSCMD, NULL, NULL);
		return (1);
	}
	if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
	{
		errman(ERR_SYSCMD, NULL, NULL);
		return (1);
	}
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
** Duplicates standard fildes to new file descriptors and saves them to
** the "saved_fds" array.
*/

int		save_fds(int *saved_fds)
{
	if ((saved_fds[0] = dup(STDIN_FILENO)) < 0 &&
		errman(ERR_SYSCMD, NULL, NULL))
		return (1);
	if ((saved_fds[1] = dup(STDOUT_FILENO)) < 0 &&
		errman(ERR_SYSCMD, NULL, NULL))
	{
		close(saved_fds[0]);
		return (1);
	}
	return (0);
}

/*
** Closes file descriptors, to which the standard fildes were
** previously duplicated.
*/

int		close_saved_fds(int *saved_fds)
{
	close(*saved_fds);
	close(*(saved_fds + 1));
	return (1);
}

/*
** Restores file descriptor configuration after running a command.
** Uses previously saved STDIN and STDOUT (in "saved_fds").
** Iterates through command siblings and closes all open fds.
*/

int		restore_fds(t_node *cmd, int *saved_fds)
{
	if ((dup2(*saved_fds, STDIN_FILENO) < 0 ||
		dup2(*(saved_fds + 1), STDOUT_FILENO) < 0) &&
		errman(ERR_SYSCMD, NULL, NULL))
		return (1);
	while (cmd)
	{
		close_fds(cmd);
		cmd = cmd->next_sibling;
	}
	return (0);
}
