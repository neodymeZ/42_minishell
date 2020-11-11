/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:51:21 by larosale          #+#    #+#             */
/*   Updated: 2020/11/11 23:52:11 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/*
** MAX_ARGS defines maximum number of arguments of a single simple command.
*/

# define MAX_ARGS		(255)

# define IN_PIPE		(1)
# define NOT_PIPE		(0)

/*
** Functions to execute the AST
*/

int		run_ast(t_node *ast);
int		spawn_child(char **argv, t_node *cmd);

/*
** Executor utils - handling the arguments
*/

char	*search_path(char *arg);
int		get_argv(t_node *arg, int *argc, char **argv);
int		free_argv(int argc, char **argv);
int		is_builtin(char **argv, int flag, t_builtin_f *f);

/*
** Executor utils - handling the I/O
*/

int		create_pipes(t_node *pipe_node);
int		create_files(t_node *cmd);
int		configure_fds(t_node *cmd);
int		close_fds(t_node *cmd);
int		restore_fds(t_node *cmd, int *saved_fds);
int		close_fds(t_node *cmd);

#endif
