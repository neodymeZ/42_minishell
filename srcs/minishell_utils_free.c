/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 03:55:24 by larosale          #+#    #+#             */
/*   Updated: 2020/11/17 16:48:00 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Frees memory used by "read_input" function on error.
*/

void	*free_read_input(char **input, char **temp)
{
	if (*input)
	{
		free(*input);
		*input = NULL;
	}
	if (*temp)
	{
		free(*temp);
		*temp = NULL;
	}
	return (NULL);
}

/*
** Frees memory used by "parse_input" function on error.
*/

void	*free_parse_input(t_token *token, t_node *tree)
{
	delete_token(token);
	delete_tree(tree);
	return (NULL);
}
