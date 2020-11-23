/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 04:34:29 by larosale          #+#    #+#             */
/*   Updated: 2020/11/23 03:16:47 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <fcntl.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <stdio.h>
# include <signal.h>
# include "libft.h"
# include "errors.h"
# include "lexer.h"
# include "parser.h"
# include "builtin.h"
# include "executor.h"

/*
** Global variables' declarations
*/

extern char		**g_env;
extern char		**g_env_local;
extern t_token	*g_null_token;
extern char		*g_gnl_str;
extern char		*g_ml_str;
extern int		g_status;

/*
** Input handling
*/

t_input		*read_input(void);
int			gnl_wrapper(int fd, char **line);
int			check_quotes(char *input);
int			check_esc(char *input);

/*
** Signal handlers
*/

# define SIGNAL_DFL			(0)
# define SIGNAL_IGN			(1)
# define SIGNAL_SET 		(2)
# define SIGNAL_SET_WAIT 	(3)

void		signal_handler(int signo);
void		signal_handler_wait(int signo);
int			set_signals(int flag);

/*
** Environment handling
*/

char		**env_init(char **env);
void		env_free(char **env);
int			env_del_var(char *var, char **env);
int			env_set_var(char *var, char *value, char ***env);
char		*env_get_var(char *var);
char		*find_var(char *var, char **env);
void		env_export_var(char *name, char *value);

/*
** Utils
*/

void		print_prompt(void);
void		print_prompt2(void);
void		*free_read_input(char **input, char **temp);

#endif
