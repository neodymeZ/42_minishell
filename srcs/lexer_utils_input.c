/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_input.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:07:10 by larosale          #+#    #+#             */
/*   Updated: 2020/11/17 03:37:30 by larosale         ###   ########.fr       */
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
	if (in->pos == INIT_INPUT_POS)
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
	if (pos == INIT_INPUT_POS)
		pos++;
	pos++;
	if (pos >= in->size)
		return (EOL);
	return (in->buffer[pos]);
}

/*
** Creates the structure of "t_input" type and fills it with data.
** Returns the created structure, or NULL on error.
*/

t_input	*create_input(char *buffer)
{
	t_input	*result;

	if (!(result = ft_calloc(1, sizeof(t_input))) ||
		!(result->buffer = ft_strdup(buffer)))
	{
		errman(ERR_SYSCMD, NULL, NULL);
		return (NULL);
	}
	result->size = ft_strlen(buffer);
	result->pos = INIT_INPUT_POS;
	return (result);
}

/*
** Deletes the structure of "t_input" type.
*/

void	delete_input(t_input *input)
{
	if (input && input->buffer)
		free(input->buffer);
	free(input);
	return ;
}
