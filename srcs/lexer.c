/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 01:43:42 by larosale          #+#    #+#             */
/*   Updated: 2020/10/16 18:58:13 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void		delete_buffer(t_tokbuf *buffer)
{
	if (buffer && buffer->buffer)
		free(buffer->buffer);
	free(buffer);
	return ;
}

static t_tokbuf	*create_buffer(void)
{
	t_tokbuf	*buffer;

	if (!(buffer = ft_calloc(1, sizeof(t_tokbuf))))
	{
		errman(ERR_SYS);
		return (NULL);
	}
	buffer->size = 1024;
	buffer->pos = 0;
	if (!(buffer->buffer = ft_calloc(1, buffer->size)))
	{
		errman(ERR_SYS);
		return (NULL);
	}
	return (buffer);
}

static int		add_to_buffer(char c, t_tokbuf *buffer)
{
	char *tmp;

	buffer->buffer[buffer->pos++] = c;
	if (buffer->pos >= buffer->size)
	{
		if (!(tmp = ft_realloc(buffer->buffer, buffer->size * 2, buffer->size)))
			return (errman(ERR_SYS));
		buffer->buffer = tmp;
		buffer->size *= 2;
	}
	return (0);
}

t_token			*tokenize_input(t_input *in)
{
	t_tokbuf	*buffer;
	t_token		*token;
	char		c;

	token = NULL;
	if (!in || !in->buffer || !in->size || (c = next_c(in)) == ERRCHAR)
		return (errman(ERR_SYS) ? NULL : NULL);	
	if (c == EOL)
		return (null_token());
	buffer = create_buffer();
	while (c != EOL)
	{
		if ((c == ' ' || c == '\t') && buffer->pos > 0)
			break ;
		if (c != ' ' && c != '\t')
			add_to_buffer(c, buffer);
		c = next_c(in);
	}
	if (buffer->pos == 0)
		return (null_token());
	if (!(token = create_token(buffer->buffer)))
		return (errman(ERR_SYS) ? NULL : NULL);
	token->in = in;
	delete_buffer(buffer);
	return (token);
}

void			test_tokenize(char *input)
{
	t_token	*token;
	t_token	*null_t;
	t_input	in;

	printf("Input is: %s\n", input);

	null_t = null_token();
	in.buffer = input;
	in.size = ft_strlen(input);
	in.pos = INIT_SRC_POS;
	token = tokenize_input(&in);
	while (ft_memcmp(token, null_t, sizeof(t_token)))
	{
		printf("Token is: %s, its length is: %d\n", token->text, token->len);
		token = tokenize_input(&in);
	}
}
