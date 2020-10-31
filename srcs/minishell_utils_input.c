/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:22:12 by larosale          #+#    #+#             */
/*   Updated: 2020/10/31 13:00:01 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	char	*joined;

/*
** Clears the ^D symbols from stdin
*/

static	void	clear_ctrl_d(void)
{
	ft_putstr_fd("  \b\b", 1);
}

static	void	gnl_signal_handler(int signo)
{
	if (signo == SIGINT)
	{
		if (joined == NULL || *joined == '\0')
		{
			signal_handler(signo);
			return ;
		}
		free(joined);
		joined = malloc(1);
		*joined = '\0';
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

static	void	set_new_signal_handlers(sig_t *sig_c, sig_t *sig_slash)
{
	*sig_c = signal(SIGINT, gnl_signal_handler);
	if (*sig_c == SIG_ERR)
		exit (-1);
	*sig_slash = signal(SIGQUIT, gnl_signal_handler);
	if (*sig_slash == SIG_ERR)
		exit (-1);
}

/*
** Restore signal handlers? saved by set_new_signal_handlers()
*/

static	void	restore_signal_handlers(sig_t sig_c, sig_t sig_slash)
{
		if (signal(SIGINT, sig_c) == SIG_ERR)
			exit (-1);
		if (signal(SIGQUIT, sig_slash) == SIG_ERR)
			exit (-1);
}

/*
** Wrapper function for the get_next_line function to implement
** Ctrl-D handling similarly to bash.
*/

int		gnl_wrapper(int fd, char **line)
{
	int			res;
	char		*tmp;
	char		*joined_tmp;
	sig_t		sig_ctrl_c;
	sig_t		sig_ctrl_backslash;

	set_new_signal_handlers(&sig_ctrl_c, &sig_ctrl_backslash);
	joined = malloc(1);		// aggregates input while \n
	*joined = '\0';
	tmp = NULL;
	while ((res = get_next_line(fd, &tmp)) == 0)
	{
		clear_ctrl_d();
		if ((*tmp == '\0') && (*joined == '\0'))	// ONLY ctrl-D was pressed and no previous input in joined
		{
			free(joined);
			joined = ft_strdup("exit");
			*line = joined;
			free(tmp);
			break ;
		}
		else			// there are some symbols AND ctrl-D
		{
			joined_tmp = ft_strjoin(joined, tmp);	// append theese symbols
			free(joined);
			joined = joined_tmp;
		}
		free(tmp);
	}
	if (res > 0)		// normal line with \n
	{
		joined_tmp = ft_strjoin(joined, tmp);
		free(joined);
		joined = joined_tmp;
		*line = joined;
		free(tmp);
	}
	else if (res < 0)	// some error occurs
		free(joined);
	restore_signal_handlers(sig_ctrl_c, sig_ctrl_backslash);
	return (res);
}

/*
** Searches the input string for opened single and double quotes that are
** not closed.
** Returns 0 if no such quotes were found, 1 if " single quote was found,
** and 2 if ' single quote was found. 
*/

int		check_quotes(char *input)
{
	int i;
	int len;
	int	quote_found;

	i = 0;
	quote_found = 0;
	len = ft_strlen(input);
	while (i < len)
	{
		if (input[i] == '"' && !quote_found)
			quote_found = 1;
		else if (input[i] == '\047' && !quote_found)
			quote_found = 2;
		while (quote_found && i < len)
		{
			i++;
			if ((input[i] == '"' && quote_found == 1) ||
				(input[i] == '\047' && quote_found == 2))
				quote_found = 0;
		}
		i++;
	}
	return (quote_found);
}
