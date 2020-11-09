/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:51:21 by larosale          #+#    #+#             */
/*   Updated: 2020/11/08 18:24:26 by larosale         ###   ########.fr       */
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
int		run_builtin(char **argv, int flag);

/*
** Executor utils
*/

int		capture_status(int status);
char	*search_path(char *arg);
int		spawn_child(char **argv, t_node *cmd);
int		get_argv(t_node *arg, int *argc, char **argv);
int		free_argv(int argc, char **argv);
int		create_pipes(t_node *pipe_node);
int		configure_fds(t_node *cmd);
int		close_fds(t_node *cmd);

#endif
