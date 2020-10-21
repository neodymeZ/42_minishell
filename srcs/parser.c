/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:48:28 by larosale          #+#    #+#             */
/*   Updated: 2020/10/15 00:54:25 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *parse_simplecom(t_token *token)
{
	t_node	*cmd;
	t_input	*in;
	t_token *null_t;

	if (!token)
		return (NULL);
	if (!cmd = create_node(NODE_CMD))
		return (NULL);
	in = token->in;
	null_t = null_token();
	while (ft_memcmp(token, null_t, sizeof(t_token)))
	{


	} 
	delete_token(token);
	delete_token(null_t);
}
