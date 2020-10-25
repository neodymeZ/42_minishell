/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:22:12 by larosale          #+#    #+#             */
/*   Updated: 2020/10/26 02:39:10 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Clears the ^D symbols from stdin
*/

static	void	clear_ctrl_d(void)
{
	ft_putstr_fd("  \b\b", 1);
}

/*
** Wrapper function for the get_next_line function to implement
** Ctrl-D handling similarly to bash.
*/

int		gnl_wrapper(int fd, char **line)
{
	int			res;
	char		*tmp;
	char		*joined;
	char		*joined_tmp;

	joined = malloc(1);
	*joined = '\0';
	while (1)
	{
		res = get_next_line(fd, &tmp);
		joined_tmp = ft_strjoin(joined, tmp);
		free(joined);
		joined = joined_tmp;
		if (res != 0)
		{
			*line = joined;
			free(tmp);
			return (res);
		}
		else
		{
			if (*tmp == '\0')
			{
				clear_ctrl_d();
				if (*joined == '\0')
				{
					*line = joined;
					free(tmp);
					return (res);
				}
				free(tmp);
				continue ;
			}
			else
			{
				clear_ctrl_d();
			}
		}
	}
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
