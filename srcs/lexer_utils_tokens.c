/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:07:26 by larosale          #+#    #+#             */
/*   Updated: 2020/11/18 01:23:54 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** The function returns a null token (pointer) to indicate the end of input.
** On error, NULL is returned.
*/

t_token	*null_token(void)
{
	t_token	*nullt;

	if (!(nullt = ft_calloc(1, sizeof(t_token))))
	{
		errman(ERR_SYSCMD, NULL, NULL);
		return (NULL);
	}
	return (nullt);
}

/*
** Creates token from the input string str.
** Returns a pointer to the created structure or NULL on error.
*/

t_token	*create_token(t_tokbuf *buffer, t_input *in)
{
	t_token	*token;
	char	c;

	token = null_token();
	if (!token || !buffer)
		return (NULL);
	token->len = ft_strlen(buffer->buffer);
	if (!(token->text = ft_strdup(buffer->buffer)))
	{
		errman(ERR_SYSCMD, NULL, NULL);
		return (NULL);
	}
	token->type = buffer->type;
	token->in = in;
	c = peek_c(in);
	if (c != '|' && c != '<' && c != '>' && c != ';')
		token->concat = buffer->concat;
	return (token);
}

/*
** Frees the memory of "token".
*/

void	delete_token(t_token *token)
{
	if (token && token->text)
		free(token->text);
	free(token);
	return ;
}
