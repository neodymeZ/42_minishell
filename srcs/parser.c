/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:48:28 by larosale          #+#    #+#             */
/*   Updated: 2020/11/14 02:11:22 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parses tokens which are part of a simple command.
** If CMD node does not exists, creates CMD and appends an ARG as its child.
** Returns 0 if no error occurred, or error code otherwise.
*/

static int	parse_simplecom(t_token *token, t_node **simplecom)
{
	t_node *arg;
	
	if (!(*simplecom))
	{
		if (!(*simplecom = create_node(NODE_CMD)))
			errman(ERR_SYS, NULL);
	}
	if (!(arg = create_node(NODE_ARG)))
		errman(ERR_SYS, NULL);
	set_node_data(arg, token->text);
	if (token->type == REDIR_IN || token->type == REDIR_OUT ||
		token->type == REDIR_APP)
	{
		if ((*simplecom)->last_redir)
			errman(ERR_TOKEN, NULL);
		(*simplecom)->last_redir = 1;
		arg->type = (int)token->type;
	}
	else
		(*simplecom)->last_redir = 0;
	add_child_node(*simplecom, arg);
	return (0);
}

/*
** Parses PIPE tokens.
** If the PIPE node does not exists, creates PIPE node.
** Adds CMD node "simplecom" as the PIPE node child, then sets simplecom
** pointer to NULL.
** Returns 0 if no error occurred, or error code otherwise.
*/

static int	parse_pipe(t_node **simplecom, t_node **pipe)
{
	if (!(*simplecom))
		errman(ERR_TOKEN, NULL);
	if (!(*pipe))
	{
		if (!(*pipe = create_node(NODE_PIPE)))
			errman(ERR_SYS, NULL);
	}
	if ((*simplecom)->last_redir)
		errman(ERR_TOKEN, NULL);
	add_child_node(*pipe, *simplecom);
	*simplecom = NULL;
	return (0);
}

/*
** Parses SEMIC tokens.
** If no PIPE node is on input, appends the CMD node "simplecom" as a direct
** child.
** Else if both PIPE and CMD nodes exist, appends PIPE node "pipe" as a child,
** if no PIPE or CMD nodes exist (empty string), returns 0.
** Returns 0 if no error occurred, or error code otherwise.
*/

static int	parse_semic(t_node **simplecom, t_node **pipe,
	t_node **semic, int eol_flag)
{
	if (*simplecom && (*simplecom)->last_redir)
		eol_flag ? errman(ERR_TOKEN, NULL) : errman(ERR_TOKEN, NULL);
	if (*simplecom && !(*pipe))
	{
		add_child_node(*semic, *simplecom);
		*simplecom = NULL;
	}
	else if (*simplecom && *pipe)
	{
		add_child_node(*pipe, *simplecom);
		add_child_node(*semic, *pipe);
		*simplecom = NULL;
		*pipe = NULL;
	}
	else if (!(*simplecom) && !(*pipe))
		return (0);
	else
		errman(ERR_TOKEN, NULL);
	return (0);
}

/*
** Parses the input token "token" based on its type.
** Returns 0 if no error occurred, or error code otherwise.
*/

static int	parse_token(t_token *token, t_node **simplecom, t_node **pipe,
	t_node **semic)
{
	if (token->type == PIPE)
		return (parse_pipe(simplecom, pipe));
	else if (token->type == SEMIC)
		return (parse_semic(simplecom, pipe, semic, NO_EOL));
	else
		return (parse_simplecom(token, simplecom));
	return (0);
}

/*
** Parses the input string and builds an abstract syntax tree for further
** processing.
** The tree consists of an SEMIC root node, with child PIPE or CMD nodes.
** PIPE nodes contain CMD nodes as their children.
** CMD nodes contain ARG nodes as their children.
** Returns the root node address, or NULL on error.
**
** Example: for command 'echo -n "test" | cat -e ; ls -la' the tree will be:
** 								SEMIC
** 				PIPE								CMD
** 		CMD				CMD						ARG		ARG
**	ARG	ARG	ARG		ARG		ARG					ls		-la	
** 	echo -n test	cat		-e
*/

t_node	*parse_input(t_input *in)
{
	t_token	*token;
	t_node	*simplecom;
	t_node	*pipe;
	t_node	*semic;

	simplecom = NULL;
	pipe = NULL;
	if (!(semic = create_node(NODE_SEMIC)))
		errman(ERR_SYS, NULL);
	// For parser testing. REMOVE on finalizing the project.
	if (!ft_strncmp(in->buffer, "parser", 6))
	{
		token = tokenize_input(in);
		delete_token(token);
	}
	// End
	while ((token = tokenize_input(in)) &&
		ft_memcmp(token, g_null_token, sizeof(t_token)))
	{
		subst_env(token);
		if (token->concat)
		{
			if (concat_tokens(token, in))
				return (NULL);
		}
		if (parse_token(token, &simplecom, &pipe, &semic))
			return (NULL);
		delete_token(token);
	}
	parse_semic(&simplecom, &pipe, &semic, EOL);
	delete_token(token);
	delete_input(in);
	return (semic);
}

/*
** For testing purposes, remove
*/

char *node_types(t_node_types type)
{
	char	*str;

	str = NULL;
	if (type == NODE_SEMIC)
		str = ft_strdup("SEMIC");
	else if (type == NODE_PIPE)
		str = ft_strdup("PIPE");
	else if (type == NODE_CMD)
		str = ft_strdup("CMD");
	else if (type == NODE_ARG)
		str = ft_strdup("ARG");
	return (str);
}

/*
** For testing purposes, remove before submitting
** The function is used for testing parser.
** To launch, enter "parser <command>" in minishell prompt.
*/

void	test_parser(t_input *in)
{
	t_node *node;
	t_node *node2;
	t_node *node3;
	t_node *node4;
	char *str;

	setbuf(stdout, NULL);
    printf("Input is: %s\n", in->buffer);
	node = parse_input(in);
	if (!node)
		return ;
	str = node_types(node->type);
	printf("%s(%d)\n\n", str, node->children);
	node = node->first_child;
	node2 = node;
	while (node)
	{
		str = node_types(node->type);
		printf("%s(%d)   ", str, node->children);
		node = node->next_sibling;
	}
	printf ("\n\n");
	node = node2;
	while (node)
	{
		node3 = node->first_child;
		while (node3)
		{
			if (node3->type == NODE_ARG)
				printf("%s   ", node3->data);
			else if (node3->type == NODE_REDIR_IN || node3->type == NODE_REDIR_OUT || node3->type == NODE_REDIR_APP)
				printf("redir: %d ", node3->type);
		else
			{
				str = node_types(node3->type);
				printf("%s(%d)   ", str, node3->children);
			}
			node3 = node3->next_sibling;
		}
		printf(" | ");
		node = node->next_sibling;
	}
	printf("\n\n");
	node = node2;
	while (node)
	{
		node3 = node->first_child;
		while (node3)
		{
			node4 = node3->first_child;
			while (node4)
			{
				if (node4->type == NODE_ARG)
					printf("%s   ", node4->data);
				else if (node4->type == NODE_REDIR_IN || node4->type == NODE_REDIR_OUT || node4->type == NODE_REDIR_APP)
					printf("redir: %d ", node4->type);
				node4 = node4->next_sibling;
			}
			node3 = node3->next_sibling;
		}
		printf(" | ");
		node = node->next_sibling;
	}
	printf("\n");
}
