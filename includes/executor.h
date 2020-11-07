/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:51:21 by larosale          #+#    #+#             */
/*   Updated: 2020/11/07 19:26:05 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/*
** MAX_ARGS defines maximum number of arguments of a single simple command.
*/

# define MAX_ARGS		(255)

# define DUP			(1)
# define NODUP			(0)

/*
** Functions to execute the AST
*/

int		run_ast(t_node *ast);
int		run_pipe(t_node *pipe);
int		run_simplecom(t_node *node);
int		run_builtin(char **args, t_node *cmd);

/*
** Executor utils
*/

char	*search_path(char *arg);
int		exec_cmd(char **argv, t_node *cmd);
int		get_argv(t_node *arg, int *argc, char **argv);
int		free_argv(int argc, char **argv);
int		create_pipes(t_node *pipe_node);
int		configure_fds(t_node *cmd);
int		close_fds(t_node *cmd, int flag);

#endif
