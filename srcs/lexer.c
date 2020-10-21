/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 01:43:42 by larosale          #+#    #+#             */
/*   Updated: 2020/10/21 20:28:17 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static int		parse_char(char c, t_tokbuf *buffer, t_input *in)
{
	char	nextc;

	if ((buffer->pos > 0 && ((c == ' ' || c == '\t') && buffer->type == STR)) ||
		(c == '"' && buffer->type == STRDQ) ||
		(c == '\047' && buffer->type == STRSQ))
	{	
//		printf("End of token\n");
		if ((c == '"' || c == '\047') && (nextc = peek_c(in)) &&
			(nextc != ' ' && nextc != '\t' && nextc != EOL))
		{
//			printf("End of token with concat\n");
			buffer->concat = CONCAT;
		}
		return (0);
	}
	else if ((c == '"' || c == '\047') && !buffer->pos &&
		buffer->type != STRDQ && buffer->type != STRSQ)
	{
		buffer->type = (c == '"' ? STRDQ : STRSQ);
//		printf("Start of quoted token\n");
	}
	else if ((c == '"' || c == '\047') && buffer->pos > 0 &&
		buffer->type != STRDQ && buffer->type != STRSQ)
	{
		buffer->concat = CONCAT;
		unget_c(in);
//		printf("End of token, immediately followed by quote\n");
		return (0);
	}
	else if ((c == ' ' || c == '\t') && buffer->type == STR)
	{
//		printf("Skipping whitespace\n");
		;
	}
	else
	{
		add_to_buffer(c, buffer);
//		printf("Adding to buffer\n");
	}
	return (1);
}

static void		parse_token(t_token *token)
{
	if (token->type == STR && !ft_strncmp(token->text, "|", 2))
		token->type = PIPE;
	else if (token->type == STR && !ft_strncmp(token->text, ">", 2))
		token->type = REDIR_OUT;
	else if (token->type == STR && !ft_strncmp(token->text, "<", 2))
		token->type = REDIR_IN;
	else if (token->type == STR && !ft_strncmp(token->text, ">>", 3))
		token->type = REDIR_APP;
	else if (token->type == STR && !ft_strncmp(token->text, ";", 2))
		token->type = SEMIC;
	return ;
}

t_token			*tokenize_input(t_input *in)
{
	t_tokbuf	*buffer;
	t_token		*token;
	char		c;
	int			res;

	token = NULL;
	if (!in || !in->buffer || !in->size || (c = next_c(in)) == ERRCHAR)
		return (errman(ERR_SYS) ? NULL : NULL);	
	if (c == EOL)
		return (null_token());
	buffer = create_buffer();
	while (c != EOL)
	{
		res = parse_char(c, buffer, in);
		if (!res)
			break ;
		c = next_c(in);
	}
	if (!(token = create_token(buffer)))
		return (errman(ERR_SYS) ? NULL : NULL);
	parse_token(token);
	token->in = in;
	delete_buffer(buffer);
	return (token);
}

void			test_tokenize(t_input *in)
{
	t_token	*token;
	t_token	*null_t;

	printf("Input is: %s\n", in->buffer);
	null_t = null_token();
	token = tokenize_input(in);
	while (ft_memcmp(token, null_t, sizeof(t_token)))
	{
		printf("Token is: %s, its length is: %d, type is: %d, concat is: %d\n", token->text, token->len, token->type, token->concat);
		token = tokenize_input(in);
	}
}
