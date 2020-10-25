/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:48:28 by larosale          #+#    #+#             */
/*   Updated: 2020/10/24 17:57:27 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_node *parse_simplecom(t_token *token)
{
	t_node	*cmd;
	t_node	*arg;
	t_input	*in;

	// Add errman
	if (!token)
		return (NULL);
	if (!(cmd = create_node(NODE_CMD)))
		return (errman(ERR_SYS) ? NULL : NULL);
	in = token->in;
	while (ft_memcmp(token, g_null_token, sizeof(t_token)) &&
		token->type != PIPE && token->type != SEMIC)
	{
		if (!(arg = create_node(NODE_ARG)))
			return (errman(ERR_SYS) ? NULL : NULL);
		set_node_data(arg, token->text);
        add_child_node(cmd, arg);
		delete_token(token);
		token = tokenize_input(in);
	} 
	if (token->type == PIPE || token->type == SEMIC)
		unget_c(in);
	delete_token(token);
	return (cmd);
}

t_node	*parse_input(t_input *in)
{
	t_token *token;
	t_node	*simplecom;
	t_node	*pipe;
	t_node	*semic;

	simplecom = NULL;
	pipe = NULL;
	// For parser testing
	if (!ft_strncmp(in->buffer, "parser", 6))
	{
		token = tokenize_input(in);
		delete_token(token);
	}
	if (!(semic = create_node(NODE_SEMIC)))
		return (errman(ERR_SYS) ? NULL : NULL);
	while ((token = tokenize_input(in)))
	{
		printf("Simplecom is: %p\n", simplecom);
		printf("token type is: %d, token text is: %s\n", token->type, token->text);
		if (!simplecom && token->type != PIPE && token->type != SEMIC)
			simplecom = parse_simplecom(token);
		else if (token->type == PIPE && simplecom)
		{
			if (!pipe)
			{
				if (!(pipe = create_node(NODE_PIPE)))
					return (errman(ERR_SYS) ? NULL : NULL);
			}
			add_child_node(pipe, simplecom);
			delete_token(token);
			simplecom = NULL;
		}
		else if ((token->type == SEMIC || 
			!ft_memcmp(token, g_null_token, sizeof(t_token))) && (simplecom || pipe))
		{
			if (simplecom && !pipe)
			{
				add_child_node(semic, simplecom);
				simplecom = NULL;
			}
			else if (simplecom && pipe)
			{
				add_child_node(pipe, simplecom);
				add_child_node(semic, pipe);
				simplecom = NULL;
				pipe = NULL;
			}
			if (!ft_memcmp(token, g_null_token, sizeof(t_token)))
				break ;
			delete_token(token);
		}
		else
		{
			printf("Error with tokens\n");
			return (NULL);
		}
	}
	delete_token(token);
	return (semic);
}

void	test_parser(t_input *in)
{
	t_node *node;
	t_node *node2;

    printf("Input is: %s\n", in->buffer);
	node = parse_input(in);
	if (!node)
		return ;
	printf("Root node type is: %d, node data is: %s, number of childen is: %d\n", node->type, node->data, node->children);
	node = node->first_child;
	while (node->next_sibling)
	{
		printf("2nd level node type is: %d, node data is: %s, number of childen is: %d\n", node->type, node->data, node->children);
		node2 = node->first_child;
		while (node2->next_sibling)
		{
			printf("3d level node type is: %d, node data is: %s, number of childen is: %d\n", node2->type, node2->data, node2->children);
			node2 = node2->next_sibling;
		}
		printf("Last 3d level node type is: %d, node data is: %s, number of childen is: %d\n", node2->type, node2->data, node2->children);
		node = node->next_sibling;
	}
	printf("Last 2nd level node type is: %d, node data is: %s, number of childen is: %d\n", node->type, node->data, node->children);
	node2 = node->first_child;
		while (node2->next_sibling)
		{
			printf("3d level node type is: %d, node data is: %s, number of childen is: %d\n", node2->type, node2->data, node2->children);
			node2 = node2->next_sibling;
		}
		printf("Last 3d level node type is: %d, node data is: %s, number of childen is: %d\n", node2->type, node2->data, node2->children);
}
