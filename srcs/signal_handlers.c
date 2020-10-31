/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal_handlers.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 00:56:54 by larosale          #+#    #+#             */
/*   Updated: 2020/10/31 20:57:47 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char	*g_joined;

void	signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		ft_putstr_fd("\b\b  \b\b\n", 1);
		print_prompt();
	}
	else if (signo == SIGQUIT)
		ft_putstr_fd("\b\b  \b\b", 1);
	return ;
}

void	gnl_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (g_joined == NULL || *g_joined == '\0')
		{
			signal_handler(signo);
			return ;
		}
		free(g_joined);
		g_joined = malloc(1);
		*g_joined = '\0';
		signal_handler(signo);
	}
	else if (signo == SIGQUIT)
	{
		signal_handler(signo);
	}
}

/*
** Set new handlers and save previous handlers
*/

void	set_new_signal_handlers(sig_t *sig_c, sig_t *sig_slash)
{
	*sig_c = signal(SIGINT, gnl_signal_handler);
	if (*sig_c == SIG_ERR)
		exit(-1);
	*sig_slash = signal(SIGQUIT, gnl_signal_handler);
	if (*sig_slash == SIG_ERR)
		exit(-1);
}

/*
** Restore signal handlers? saved by set_new_signal_handlers()
*/

void	restore_signal_handlers(sig_t sig_c, sig_t sig_slash)
{
	if (signal(SIGINT, sig_c) == SIG_ERR)
		exit(-1);
	if (signal(SIGQUIT, sig_slash) == SIG_ERR)
		exit(-1);
}
