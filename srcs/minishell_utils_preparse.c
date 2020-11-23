/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_preparse.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 19:32:00 by larosale          #+#    #+#             */
/*   Updated: 2020/11/23 02:59:14 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <minishell.h>

/*
** Checks the input string for the trailing backslashes (escape chars).
** Returns 0 if the string is not ending with '\', or 1 otherwise.
*/

int			check_esc(char *input)
{
	int len;
	int	i;

	i = 0;
	len = ft_strlen(input);
	while (i < len && input[len - 1 - i] == '\\')
		i++;
	if (i % 2 == 0)
		return (0);
	else
		return (1);
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
		if (input[i] == '"' && !quote_found && !is_escaped(input, input + i))
			quote_found = 1;
		else if (input[i] == '\047' && !quote_found &&
			!is_escaped(input, input + i))
			quote_found = 2;
		while (quote_found && i < len)
		{
			i++;
			if ((input[i] == '"' && quote_found == 1 &&
				!is_escaped(input, input + i)) ||
				(input[i] == '\047' && quote_found == 2))
				quote_found = 0;
		}
		i++;
	}
	return (quote_found);
}
