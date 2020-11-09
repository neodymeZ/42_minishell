/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 00:56:54 by larosale          #+#    #+#             */
/*   Updated: 2020/11/09 09:42:43 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Signal handler function.
** On SIGINT it clears '^C' symbols and prints new prompt. If the signal
** came while joining EOF-ed strings in gnl_wrapper function, the accumulated
** string is cleared (pointed to by g_gnl_str).
** On SIGQUIT '^\' symbols are cleared.
*/

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b\n", 1);
		print_prompt();
		if (g_gnl_str)
			*g_gnl_str = '\0';
	}
	else if (signo == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
	return ;
}

/*
** Prints newline on SIGINT (used if child is interrupted with SIGINT).
*/

void	signal_handler_wait(int signo)
{
	if (signo == SIGINT)
		ft_putchar_fd('\n', 1);
	return ;
}

/*
** Setups signal handling based on the flag:
** - SIGNAL_DFL - reset to default behavior;
** - SIGNAL_IGN - ignore all signals;
** - SIGNAL_SET - set the signal handler for SIGINT and SIGQUIT;
** - SIGNAL_SET_WAIT - set the signal handler for SIGINT and
**   ignore SIGTERM (used while waiting for child).
** Error code is returned, or 0 if no error occurred.
*/

int		set_signals(int flag)
{
	if (flag == SIGNAL_DFL && (signal(SIGINT, SIG_DFL) == SIG_ERR ||
		signal(SIGQUIT, SIG_DFL) == SIG_ERR))
		return (errman(ERR_SYS, NULL));
	else if (flag == SIGNAL_IGN && (signal(SIGINT, SIG_IGN) == SIG_ERR ||
		signal(SIGQUIT, SIG_IGN) == SIG_ERR))
		return (errman(ERR_SYS, NULL));
	else if (flag == SIGNAL_SET && (signal(SIGINT, signal_handler) == SIG_ERR ||
		signal(SIGQUIT, signal_handler) == SIG_ERR ||
		signal(SIGTERM, SIG_IGN) == SIG_ERR))
		return (errman(ERR_SYS, NULL));
	else if (flag == SIGNAL_SET_WAIT &&
		(signal(SIGINT, signal_handler_wait) == SIG_ERR ||
		signal(SIGQUIT, SIG_IGN) == SIG_ERR))
		return (errman(ERR_SYS, NULL));
	return (0);
}
