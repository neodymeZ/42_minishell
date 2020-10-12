/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:07:41 by larosale          #+#    #+#             */
/*   Updated: 2020/10/13 01:26:03 by larosale         ###   ########.fr       */
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

extern char	**environ;
extern int	errno;


/*
** Builtin functions
*/

int			ft_cd(char **command);
int			ft_pwd(void);
void		ft_exit(void);

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
** Utils
*/

void		print_prompt(void);

#endif
