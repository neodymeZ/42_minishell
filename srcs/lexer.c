/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 01:43:42 by larosale          #+#    #+#             */
/*   Updated: 2020/11/07 15:17:34 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Determines, whether the input char "c" is a control char and returns
** its enum value.
*/

static int		is_ctrl(char c)
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
			if (c == '>' && (nextc = peek_c(in)) == '>')
			{
				in->pos++;
				buffer->type = REDIR_APP;
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

	if ((buffer->pos > 0 && ((c == ' ' || c == '\t') && buffer->type == STR)) ||
		(c == '"' && buffer->type == STRDQ) ||
		(c == '\047' && buffer->type == STRSQ))
	{	
		if ((c == '"' || c == '\047') && (nextc = peek_c(in)) &&
			(nextc != ' ' && nextc != '\t' && nextc != EOL))
			buffer->concat = CONCAT;
		return (0);
	}
	else if ((c == '"' || c == '\047') && !buffer->pos &&
		buffer->type != STRDQ && buffer->type != STRSQ)
		buffer->type = (c == '"' ? STRDQ : STRSQ);
	else if ((c == '"' || c == '\047') && buffer->pos > 0 &&
		buffer->type != STRDQ && buffer->type != STRSQ)
	{
		buffer->concat = CONCAT;
		unget_c(in);
		return (0);
	}
	else if ((c == ' ' || c == '\t') && buffer->type == STR)
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

	token = NULL;
	res = 0;
	c = '\0';
	if (!in || !in->buffer || (c = next_c(in)) == ERRCHAR)
		errman(ERR_SYS, NULL);
	if (c == EOL)
		return (null_token());
	buffer = create_buffer();
	while (c != EOL)
	{
		if (!parse_ctrl(c, buffer, in) || !(res = parse_char(c, buffer, in)))
			break ;
		if (res == 2)
			add_to_buffer(c, buffer);
		c = next_c(in);
	}
	if (buffer->type == 0 && *(buffer->buffer) == '\0')
		return (null_token());
	if (!(token = create_token(buffer)))
		errman(ERR_SYS, NULL);
	token->in = in;
	delete_buffer(buffer);
	return (token);
}

/*
** The function is used to test lexer, remove before submission
** Usage: lexer <command> in minishell prompt.
*/

void			test_tokenize(t_input *in)
{
	t_token	*token;

	printf("Input is: %s\n", in->buffer);
	token = tokenize_input(in);
	while (ft_memcmp(token, g_null_token, sizeof(t_token)))
	{
		printf("Token is: %s, its length is: %d, type is: %d, concat is: %d\n", token->text, token->len, token->type, token->concat);
		token = tokenize_input(in);
	}
}
