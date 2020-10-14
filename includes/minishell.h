/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:07:41 by larosale          #+#    #+#             */
/*   Updated: 2020/10/14 15:34:22 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <sys/wait.h>
# include <sys/errno.h>
# include <stdio.h>
# include <signal.h>
# include "libft.h"
# include "errors.h"

/*
** External variables' declarations
*/

/*
** extern char	**environ;
*/
extern int	errno;

/*
** Builtin functions
*/

int			ft_cd(char **command);
int			ft_pwd(void);
void		ft_exit(void);
int			ft_env(void);

/*
** Signal handlers
*/

void   		signal_handler(int signo);

/*
** Error handling
*/

void		print_error(int e);
int			errman(int errnum);

/*
** Environment handling
*/

char		**env_init(char **env);
void		env_free(char **env);

/*
** Utils
*/

void		print_prompt(void);

#endif
