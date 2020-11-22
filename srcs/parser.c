/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 23:48:28 by larosale          #+#    #+#             */
/*   Updated: 2020/11/22 03:33:45 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Parses tokens which are part of a simple command.
** If CMD node does not exists, creates CMD and appends an ARG as its child.
** Returns 0 if no error occurred, or 1 otherwise.
*/

static int	parse_simplecom(t_token *token, t_node **simplecom)
{
	t_node *arg;

	if (!(*simplecom))
	{
		if (!(*simplecom = create_node(NODE_CMD)))
			return (1);
	}
	if (!(arg = create_node(NODE_ARG)))
		return (1);
	if (set_node_data(arg, token->text))
		return (1);
	if (token->type == REDIR_IN || token->type == REDIR_OUT ||
		token->type == REDIR_APP)
	{
		if ((*simplecom)->last_redir && errman(ERR_TOKEN, token->text, NULL))
			return (1);
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
** Returns 0 if no error occurred, or 1 otherwise.
*/

static int	parse_pipe(t_node **simplecom, t_node **pipe)
{
	if (!(*simplecom) && errman(ERR_TOKEN, "|", NULL))
		return (1);
	if (!(*pipe))
	{
		if (!(*pipe = create_node(NODE_PIPE)))
			return (1);
	}
	if ((*simplecom)->last_redir && errman(ERR_TOKEN, "|", NULL))
		return (1);
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
	if (((*simplecom && (*simplecom)->last_redir) ||
		(!(*simplecom) && *pipe)) &&
		eol_flag && errman(ERR_TOKEN, "(newline)", NULL))
		return (1);
	if (*simplecom && !(*pipe) && !(*simplecom)->last_redir)
	{
		add_child_node(*semic, *simplecom);
		*simplecom = NULL;
	}
	else if (*simplecom && *pipe && !(*simplecom)->last_redir)
	{
		add_child_node(*pipe, *simplecom);
		add_child_node(*semic, *pipe);
		*simplecom = NULL;
		*pipe = NULL;
	}
	else if (!(*simplecom) && !(*pipe))
		;
	else if (errman(ERR_TOKEN, ";", NULL))
		return (1);
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

t_node		*parse_input(t_input *in)
{
	t_token	*token;
	t_node	*simplecom;
	t_node	*pipe;
	t_node	*semic;

	simplecom = NULL;
	pipe = NULL;
	if (!(semic = create_node(NODE_SEMIC)))
		return (NULL);
	while ((token = tokenize_input(in)) &&
		ft_memcmp(token, g_null_token, sizeof(t_token)))
	{
		subst_env(token);
		remove_escapes(token);
		if (token->concat && concat_tokens(token, in))
			return (free_parse_input(token, semic));
		if (parse_token(token, &simplecom, &pipe, &semic))
			return (free_parse_input(token, semic));
		delete_token(token);
	}
	if (!token || parse_semic(&simplecom, &pipe, &semic, EOL))
		return (free_parse_input(token, semic));
	delete_token(token);
	delete_input(in);
	return (semic);
}
