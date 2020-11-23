/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils_free.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/17 03:55:24 by larosale          #+#    #+#             */
/*   Updated: 2020/11/23 20:00:37 by larosale         ###   ########.fr       */
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

void	*free_parse_input(t_token *token, t_node *sc, t_node *pipe, t_node *sem)
{
	delete_token(token);
	if (sc)
		delete_tree(sc);
	if (pipe)
		delete_tree(pipe);
	if (sem)
		delete_tree(sem);
	return (NULL);
}
