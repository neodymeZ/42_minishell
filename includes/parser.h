/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:12:19 by larosale          #+#    #+#             */
/*   Updated: 2020/10/21 20:29:55 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum		e_node_types
{
	NODE_ROOT,
    NODE_CMD,
	NODE_PIPE,
	NODE_SEMIC,
    NODE_ARG,
	NODE_REDIR_IN,
	NODE_REDIR_OUT,
	NODE_REDIR_APP
}					t_node_types;

typedef struct		s_node
{
	t_node_types	type;
	char			*data;
	int				children;
	int				concat;
	struct s_node	*first_child;
	struct s_node	*prev_sibling;
	struct s_node	*next_sibling;
}					t_node;

/*
** Functions to manipulate the abstract syntax tree nodes
*/

t_node				*create_node(t_node_types type);
int					add_child_node(t_node *parent, t_node *child);
void				delete_tree(t_node *root);
int					set_node_data(t_node *node, char *data);

/*
** Parsing functions
*/

t_node				*parse_simplecom(t_token *token);

// TESTING

void				test_parser(t_input *in);

#endif
