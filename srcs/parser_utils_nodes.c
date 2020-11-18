/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser_utils_nodes.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/20 01:00:36 by larosale          #+#    #+#             */
/*   Updated: 2020/11/17 17:14:33 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Creates a new node of the tree of type "type".
** Returns a pointer to the created node, or NULL on error.
*/

t_node	*create_node(t_node_types type)
{
	t_node	*node;

	if (!(node = ft_calloc(1, sizeof(t_node))))
	{
		errman(ERR_SYSCMD, NULL, NULL);
		return (NULL);
	}
	node->type = type;
	node->fd_out = 1;
	return (node);
}

/*
** Adds the child node ("child") to the parent node ("parent") as a last
** sibling.
** Returns 0 on success, or 1 on error.
*/

int		add_child_node(t_node *parent, t_node *child)
{
	t_node	*sibling;

	if (!parent->first_child)
		parent->first_child = child;
	else
	{
		sibling = parent->first_child;
		while (sibling->next_sibling)
			sibling = sibling->next_sibling;
		sibling->next_sibling = child;
		child->prev_sibling = sibling;
	}
	parent->children += 1;
	return (0);
}

/*
** Sets the node "data" string to the given "data".
** Allocates memory for the new string.
** Returns 0 on success, or 1 on error.
*/

int		set_node_data(t_node *node, char *data)
{
	if (!data)
		node->data = NULL;
	else if (!(node->data = ft_strdup(data)))
	{
		errman(ERR_SYSCMD, NULL, NULL);
		return (1);
	}
	return (0);
}

/*
** Deletes the parse tree from a given "root" recursively.
*/

void	delete_tree(t_node *root)
{
	t_node	*child;
	t_node	*next_child;

	if (root)
	{
		child = root->first_child;
		while (child)
		{
			next_child = child->next_sibling;
			delete_tree(child);
			child = next_child;
		}
		if (root->data)
			free(root->data);
		free(root);
	}
	return ;
}
