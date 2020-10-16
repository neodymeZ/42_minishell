/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils_tokens.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 19:07:26 by larosale          #+#    #+#             */
/*   Updated: 2020/10/16 18:55:06 by larosale         ###   ########.fr       */
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
		errman(ERR_SYS);
		return (NULL);
	}
	return (nullt);
}

/*
** Creates token from the input string str.
** Returns a pointer to the created structure or NULL on error.
*/

t_token	*create_token(char *str)
{
	t_token	*token;

	token = null_token();
	if (!token || !str)
	{
		errman(ERR_SYS);
		return (NULL);
	}
	token->len = ft_strlen(str);
	if (!(token->text = ft_strdup(str)))
	{
		errman(ERR_SYS);
		return (NULL);
	}
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
