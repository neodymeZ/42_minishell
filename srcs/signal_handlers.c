/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 00:56:54 by larosale          #+#    #+#             */
/*   Updated: 2020/11/07 14:49:37 by gejeanet         ###   ########.fr       */
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
** Setups signal handling based on the flag:
** - SIGNAL_DFL - reset to default behavior;
** - SIGNAL_IGN - ignore all signals;
** - SIGNAL_SET - set the signal handler for SIGINT and SIGQUIT;
** Error code is returned, or 0 if no error occurred.
*/

int		set_signals(int flag)
{
	if (flag == SIGNAL_DFL)
	{
		if (signal(SIGINT, SIG_DFL) == SIG_ERR ||
			signal(SIGQUIT, SIG_DFL) == SIG_ERR ||
			signal(SIGTERM, SIG_DFL) == SIG_ERR)
			errman(ERR_SYS, NULL);
	}
	else if (flag == SIGNAL_IGN)
	{
		if (signal(SIGINT, SIG_IGN) == SIG_ERR ||
			signal(SIGQUIT, SIG_IGN) == SIG_ERR)
			errman(ERR_SYS, NULL);
	}
	else if (flag == SIGNAL_SET)
	{
		if (signal(SIGINT, signal_handler) == SIG_ERR ||
			signal(SIGQUIT, signal_handler) == SIG_ERR ||
			signal(SIGTERM, SIG_IGN) == SIG_ERR)
			errman(ERR_SYS, NULL);
	}
	return (0);
}
