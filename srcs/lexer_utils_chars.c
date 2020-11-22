/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_chars.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:07:34 by larosale          #+#    #+#             */
/*   Updated: 2020/11/22 04:27:50 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Determines, whether the input char "c" is a control char and returns
** its enum value.
*/

int		is_ctrl(char c)
{
	if (c == '|')
		return (PIPE);
	else if (c == '<')
		return (REDIR_IN);
	else if (c == '>')
		return (REDIR_OUT);
	else if (c == ';')
		return (SEMIC);
	return (0);
}

/*
** Determines, whether the input char "c" is a whitespace symbol and returns
** its enum value.
*/

int		is_white(char c)
{
	if (c == ' ')
		return (SPACE);
	else if (c == '\t')
		return (TAB);
	return (0);
}

/*
** Determines, whether the input char "c" is a quote and returns its enum
** value (DQ for double quote, SQ for single quote).
*/

int		is_quote(char c)
{
	if (c == '"')
		return (DQ);
	else if (c == '\047')
		return (SQ);
	return (0);
}

/*
** Determines, if the character at "c_pos" position in the string "str" is
** escaped by '\' symbol.
*/

int		is_escaped(char *str, char *c_pos)
{
	int i;

	i = 0;
	if (c_pos == str)
		return (0);
	while (c_pos - str && *(c_pos - 1) == '\\')
	{
		c_pos--;
		i++;
	}
	if (i % 2 != 0)
		return (1);
	return (0);
}
