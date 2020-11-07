/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:07:26 by larosale          #+#    #+#             */
/*   Updated: 2020/11/07 14:41:55 by gejeanet         ###   ########.fr       */
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
		errman(ERR_SYS, NULL);
	return (nullt);
}

/*
** Creates token from the input string str.
** Returns a pointer to the created structure or NULL on error.
*/

t_token	*create_token(t_tokbuf *buffer)
{
	t_token	*token;

	token = null_token();
	if (!token || !buffer)
		errman(ERR_SYS, NULL);
	token->len = ft_strlen(buffer->buffer);
	if (!(token->text = ft_strdup(buffer->buffer)))
		errman(ERR_SYS, NULL);
	token->type = buffer->type;
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
