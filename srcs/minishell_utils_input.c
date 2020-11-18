/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:22:12 by larosale          #+#    #+#             */
/*   Updated: 2020/11/17 15:29:40 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Helper function for GNL wrapper.
*/

static int	join_str(char **line, char **tmp)
{
	if (!(*tmp = ft_strjoin(g_gnl_str, *line)))
		return (1);
	free(*line);
	free(g_gnl_str);
	g_gnl_str = *tmp;
	return (0);
}

/*
** Wrapper function for the get_next_line function to implement
** Ctrl-D handling similarly to bash.
** If GNL ends with non-zero result (line was read, or error returned)
** the wrapper does nothing.
** If GNL returns 0 (EOF) and the line is empty, minishell exits.
** Otherwise, the line is being read in a loop while GNL returns 0.
** Read lines are joined until non-zero GNL return.
** The global variable gnl_str keeps pointer to the joined string for
** correct signal handling behavior.
** Interface of the wrapper is similar to GNL's.
*/

int			gnl_wrapper(int fd, char **line)
{
	int		gnl_res;
	char	*tmp;

	if ((gnl_res = get_next_line(fd, line)))
		return (gnl_res);
	if (**line == '\0')
		ft_exit(NULL);
	if (!(g_gnl_str = ft_calloc(1, 1)))
		return (-1);
	ft_putstr_fd("  \b\b", 1);
	while (!gnl_res)
	{
		if (join_str(line, &tmp) || (gnl_res = get_next_line(fd, line)) < 0)
			return (-1);
		ft_putstr_fd("  \b\b", 1);
	}
	if (join_str(line, &tmp))
		return (-1);
	*line = tmp;
	g_gnl_str = NULL;
	return (gnl_res);
}

/*
** Searches the input string for opened single and double quotes that are
** not closed.
** Returns 0 if no such quotes were found, 1 if " single quote was found,
** and 2 if ' single quote was found.
*/

int			check_quotes(char *input)
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
