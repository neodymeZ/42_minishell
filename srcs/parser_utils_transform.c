/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_transform.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/27 23:38:16 by larosale          #+#    #+#             */
/*   Updated: 2020/10/28 00:43:33 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		concat_tokens(t_token *token, t_input *in)
{
	t_token	*read;
	char	*tmp;

	tmp = NULL;
	while ((read = tokenize_input(in)) && read->concat)
	{
		if (!(tmp = ft_strjoin(token->text, read->text)))
			return (1);
		free(token->text);
		token->text = tmp;
		delete_token(read);
	}
	if (!(tmp = ft_strjoin(token->text, read->text)))
		return (1);
	free(token->text);
	token->text = tmp;
	delete_token(read);
	return (0);
}
