/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:22:12 by larosale          #+#    #+#             */
/*   Updated: 2020/10/31 20:55:36 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*g_joined;

/*
** Clears the ^D symbols from stdout
*/

static	void	clear_ctrl_d(void)
{
	ft_putstr_fd("  \b\b", 1);
}

/*
** Helper func to gnl_wrapper() to pass norminette requirements
*/

static	int		suppress_ctrl_d(int fd, char **tmp, char **joined_tmp, char **l)
{
	int		res;

	while ((res = get_next_line(fd, tmp)) == 0)
	{
		clear_ctrl_d();
		if ((**tmp == '\0') && (*g_joined == '\0'))
		{
			free(g_joined);
			g_joined = ft_strdup("exit");
			*l = g_joined;
			free(*tmp);
			break ;
		}
		else
		{
			*joined_tmp = ft_strjoin(g_joined, *tmp);
			free(g_joined);
			g_joined = *joined_tmp;
		}
		free(*tmp);
	}
	return (res);
}

/*
** Wrapper function for the get_next_line function to implement
** Ctrl-D handling similarly to bash.
**
** this is pre-norminette version, more clear to understand :)
**
** int		gnl_wrapper(int fd, char **line)
** {
** 	int			res;
** 	char		*tmp;
** 	char		*joined_tmp;
** 	sig_t		sig_ctrl_c;
** 	sig_t		sig_ctrl_backslash;
**
** 	set_new_signal_handlers(&sig_ctrl_c, &sig_ctrl_backslash);
** 	joined = malloc(1);		// aggregates input while \n
** 	*joined = '\0';
** 	while ((res = get_next_line(fd, &tmp)) == 0)
** 	{
** 		clear_ctrl_d();
** // ONLY ctrl-D was pressed and no previous input in joined
** 		if ((*tmp == '\0') && (*joined == '\0'))
** 		{
** 			free(joined);
** 			joined = ft_strdup("exit");
** 			*line = joined;
** 			free(tmp);
** 			break ;
** 		}
** 		else			// there are some symbols AND ctrl-D
** 		{
** 			joined_tmp = ft_strjoin(joined, tmp);	// append theese symbols
** 			free(joined);
** 			joined = joined_tmp;
** 		}
** 		free(tmp);
** 	}
** 	if (res > 0)		// normal line with \n
** 	{
** 		joined_tmp = ft_strjoin(joined, tmp);
** 		free(joined);
** 		joined = joined_tmp;
** 		*line = joined;
** 		free(tmp);
** 	}
** 	else if (res < 0)	// some error occurs
** 		free(joined);
** 	restore_signal_handlers(sig_ctrl_c, sig_ctrl_backslash);
** 	return (res);
** }
*/

int				gnl_wrapper(int fd, char **line)
{
	int			res;
	char		*tmp;
	char		*joined_tmp;
	sig_t		sig_ctrl_c;
	sig_t		sig_ctrl_backslash;

	set_new_signal_handlers(&sig_ctrl_c, &sig_ctrl_backslash);
	g_joined = malloc(1);
	*g_joined = '\0';
	res = suppress_ctrl_d(fd, &tmp, &joined_tmp, line);
	if (res > 0)
	{
		joined_tmp = ft_strjoin(g_joined, tmp);
		free(g_joined);
		g_joined = joined_tmp;
		*line = g_joined;
		free(tmp);
	}
	else if (res < 0)
		free(g_joined);
	restore_signal_handlers(sig_ctrl_c, sig_ctrl_backslash);
	return (res);
}

/*
** Searches the input string for opened single and double quotes that are
** not closed.
** Returns 0 if no such quotes were found, 1 if " single quote was found,
** and 2 if ' single quote was found.
*/

int				check_quotes(char *input)
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
