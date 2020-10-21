/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:48:28 by larosale          #+#    #+#             */
/*   Updated: 2020/10/21 20:29:01 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *parse_simplecom(t_token *token)
{
	t_node	*cmd;
	t_node	*arg;
	t_input	*in;
	t_token *null_t;

	// Add errman
	if (!token)
		return (NULL);
	if (!(cmd = create_node(NODE_CMD)))
		return (errman(ERR_SYS) ? NULL : NULL);
	in = token->in;
	null_t = null_token();
	while (ft_memcmp(token, null_t, sizeof(t_token)))
	{
		if (!(arg = create_node(NODE_ARG)))
			return (errman(ERR_SYS) ? NULL : NULL);
		set_node_data(arg, token->text);
        add_child_node(cmd, arg);
		delete_token(token);
		token = tokenize_input(in);
	} 
	delete_token(token);
	delete_token(null_t);
	return (cmd);
}

void	test_parser(t_input *in)
{
    t_token *token;
    t_token *null_t;
	t_node *node;

    printf("Input is: %s\n", in->buffer);

    null_t = null_token();
    token = tokenize_input(in);
	node = parse_simplecom(token);
	printf("Node type is: %d, node data is: %s, number of childen is: %d\n", node->type, node->data, node->children);
	node = node->first_child;
	while (node->next_sibling)
	{
		printf("Node type is: %d, node data is: %s, number of childen is: %d\n", node->type, node->data, node->children);
		node = node->next_sibling;
	}
	printf("Node type is: %d, node data is: %s, number of childen is: %d\n", node->type, node->data, node->children);
}
