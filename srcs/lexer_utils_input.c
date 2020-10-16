/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:07:10 by larosale          #+#    #+#             */
/*   Updated: 2020/10/14 23:10:24 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Moves the position pointer one symbol back in the input string.
*/


void	unget_c(t_input *in)
{
	if (in->pos < 0)
		return ;
	in->pos--;
	return ;
}

/*
** Returns the next symbol in the input string and moves the position pointer.
*/

char	next_c(t_input *in)
{
	if (!in || !in->buffer)
		return (ERRCHAR);
	if (in->pos == INIT_SRC_POS)
		in->pos = -1;
	if (++in->pos >= in->size)
	{
		in->pos = in->size;
		return (EOL);
	}
	return (in->buffer[in->pos]);
}

/*
** Returns the next symbol in the input string without moving the position
** pointer.
*/

char	peek_c(t_input *in)
{
	int	pos;

	pos = in->pos;
	if (!in || !in->buffer)
		return (ERRCHAR);
	if (pos == INIT_SRC_POS)
		pos++;
	pos++;
	if (pos >= in->size)
		return (EOL);
	return (in->buffer[pos]);
}

/*
** Skips whitespaces in the input string.
*/

void	skip_white(t_input *in)
{
	char c;

	c = 0;
	if (!in || !in->buffer)
		return ;
	while (((c = peek_c(in)) != EOL) && (c == ' ' || c == '\t'))
		next_c(in);
	return ;
}
