/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_buffer.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/21 01:39:25 by larosale          #+#    #+#             */
/*   Updated: 2020/11/17 17:27:37 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Deletes the token buffer, used by "tokenize_input" function.
*/

void		delete_buffer(t_tokbuf *buffer)
{
	if (buffer && buffer->buffer)
		free(buffer->buffer);
	free(buffer);
	return ;
}

/*
** Creates the token buffer, used by "tokenize_input" function and fills it
** with default values:
** - size = 1024;
** - pos = 0;
** - type = STR;
** - concat = NO_CONCAT.
** Returns buffer, or NULL on error.
*/

t_tokbuf	*create_buffer(void)
{
	t_tokbuf	*buffer;

	if (!(buffer = ft_calloc(1, sizeof(t_tokbuf))))
	{
		errman(ERR_SYSCMD, NULL, NULL);
		return (NULL);
	}
	buffer->size = 1024;
	buffer->pos = 0;
	if (!(buffer->buffer = ft_calloc(1, buffer->size)))
	{
		errman(ERR_SYSCMD, NULL, NULL);
		free(buffer);
		return (NULL);
	}
	buffer->type = STR;
	buffer->concat = NO_CONCAT;
	return (buffer);
}

/*
** Adds the char "c" to the token buffer, used by "tokenize_input" function.
** Enlarges buffer, if needed.
** Returns 1 on error, or 0 otherwise.
*/

int			add_to_buffer(char c, t_tokbuf *buffer)
{
	char *tmp;

	buffer->buffer[buffer->pos++] = c;
	if (buffer->pos >= buffer->size)
	{
		if (!(tmp = ft_realloc(buffer->buffer, buffer->size * 2, buffer->size)))
		{
			errman(ERR_SYSCMD, NULL, NULL);
			return (1);
		}
		buffer->buffer = tmp;
		buffer->size *= 2;
	}
	return (0);
}
