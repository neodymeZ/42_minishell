/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 23:12:19 by larosale          #+#    #+#             */
/*   Updated: 2020/11/22 02:25:49 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

typedef enum		e_node_types
{
	NODE_SEMIC,
	NODE_PIPE,
	NODE_CMD,
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
	int				fd_in;
	int				fd_out;
	int				fd1_close;
	int				fd2_close;
	int				last_redir;
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
void				*free_parse_input(t_token *token, t_node *tree);

/*
** Parsing functions
*/

t_node				*parse_temp(t_token *token);
t_node				*parse_input(t_input *in);

/*
** Token transformation functions
*/

int					concat_tokens(t_token *token, t_input *in);
int					subst_env(t_token *token);
int					remove_escapes(t_token *token);

#endif
