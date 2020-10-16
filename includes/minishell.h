/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 19:07:41 by larosale          #+#    #+#             */
/*   Updated: 2020/10/15 01:31:31 by larosale         ###   ########.fr       */
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
# include "lexer.h"
//# include "parser.h"

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
** Input handling
*/

char		**read_input(int *gnl_result);


/*
** Signal handlers
*/

void   		signal_handler(int signo);

/*
** Utils
*/

void		print_prompt(void);
void		print_prompt2(void);

#endif
