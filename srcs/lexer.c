/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 01:43:42 by larosale          #+#    #+#             */
/*   Updated: 2020/11/22 04:28:30 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parses escape character '\'.
** The function does nothing and returns 0 if the current character is not '\'
** If the next character is EOL, the function returns 0 and ungets the char.
** Otherwise, the next char is added to buffer.
** In case of double or single quoted buffers (or if the next char is $, \), the
** preceding '\' is added to the buffer too.
** NB: Handling escapes in double quotes should be done later (when expanding
** environment vars).
*/

static int		parse_esc(char c, t_tokbuf *buffer, t_input *in)
{
	char	nextc;

	if (c == '\\' && (buffer->type == STR || buffer->type == STRDQ))
	{
		if ((nextc = next_c(in)) == EOL || (buffer->type == STRDQ &&
			nextc != '$' && nextc != '"' && nextc != '\\'))
		{
			unget_c(in);
			return (0);
		}
		if ((buffer->type == STR && (nextc == '$' || nextc == '\\')) ||
			(buffer->type == STRDQ && (nextc == '$' || nextc == '\\' ||
			nextc == '"')))
		{
			add_to_buffer(c, buffer);
			add_to_buffer(nextc, buffer);
			return (1);
		}
		else if (buffer->type == STR && nextc != '$' && nextc != '\\')
		{
			add_to_buffer(nextc, buffer);
			return (1);
		}
	}
	return (0);
}

/*
** Parses control symbols (|;<>) and sets the buffer type respectively.
** Returns 0 if token has ended, or 1 otherwise.
*/

static int		parse_ctrl(char c, t_tokbuf *buffer, t_input *in)
{
	char	nextc;
	int		ctrl_type;

	if ((ctrl_type = is_ctrl(c)) && buffer->type == STR)
	{
		if (buffer->pos > 0)
			unget_c(in);
		else if (!buffer->pos)
		{
			add_to_buffer(c, buffer);
			if (c == '>' && (nextc = peek_c(in)) == '>')
			{
				in->pos++;
				buffer->type = REDIR_APP;
				add_to_buffer(nextc, buffer);
			}
			else
				buffer->type = ctrl_type;
		}
		return (0);
	}
	return (1);
}

/*
** Parses the input string symbol and:
**  - sets the necessary parameters and returns 0 if the token has ended;
**  - does nothing on whitespace and returns 1;
**  - sets the STRSQ and STRDQ types if c is " or ' and the token
**    has just started, and returns 1;
**  - returns 2 if the symbol shall be added to the buffer.
*/

static int		parse_char(char c, t_tokbuf *buffer, t_input *in)
{
	char	nextc;

	if ((buffer->pos > 0 && is_white(c) && buffer->type == STR) ||
		(is_quote(c) == DQ && buffer->type == STRDQ) ||
		(is_quote(c) == SQ && buffer->type == STRSQ))
	{
		if (is_quote(c) && (nextc = peek_c(in)) &&
			!is_white(nextc) && nextc != EOL)
			buffer->concat = CONCAT;
		return (0);
	}
	else if (is_quote(c) && !buffer->pos &&
		buffer->type != STRDQ && buffer->type != STRSQ)
		buffer->type = (c == '"' ? STRDQ : STRSQ);
	else if (is_quote(c) && buffer->pos > 0 && buffer->type != STRDQ &&
		buffer->type != STRSQ && (buffer->concat = CONCAT))
	{
		unget_c(in);
		return (0);
	}
	else if (is_white(c) && buffer->type == STR)
		;
	else
		return (2);
	return (1);
}

/*
** Main lexer function.
** Parses input string and splits it into tokens (struct of t_token type)
** with all the necessary information for further processing.
** Parses one token per run, returns the created token or NULL on error.
*/

t_token			*tokenize_input(t_input *in)
{
	t_tokbuf	*buffer;
	t_token		*token;
	char		c;
	int			res;

	res = 0;
	if (!(buffer = create_buffer()))
		return (NULL);
	if (peek_c(in) == EOL)
		return (null_token());
	while ((c = next_c(in)) != EOL)
	{
		if (parse_esc(c, buffer, in))
			continue ;
		if (!parse_ctrl(c, buffer, in) || !(res = parse_char(c, buffer, in)))
			break ;
		res == 2 ? add_to_buffer(c, buffer) : 0;
	}
	if (buffer->type == 0 && *(buffer->buffer) == '\0')
		token = null_token();
	else
		token = create_token(buffer, in);
	delete_buffer(buffer);
	return (token);
}
