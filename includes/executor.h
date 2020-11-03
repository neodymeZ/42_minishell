/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executor.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 16:51:21 by larosale          #+#    #+#             */
/*   Updated: 2020/11/04 02:03:24 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTOR_H
# define EXECUTOR_H

/*
** MAX_ARGS defines maximum number of arguments of a single simple command.
*/

# define MAX_ARGS		(255)

/*
** Functions to execute the AST
*/

int		run_ast(t_node *ast);
int		run_pipe(t_node *pipe);
int		run_simplecom(t_node *node);
int		run_builtin(char **command);

/*
** Executor utils
*/

char	*search_path(char *arg);
int		exec_cmd(char **argv);
int		get_argv(t_node *arg, int *argc, char **argv);
int		free_argv(int argc, char **argv);

#endif
