/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/13 00:03:42 by larosale          #+#    #+#             */
/*   Updated: 2020/10/21 01:25:22 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	print_prompt(void)
{
	ft_putstr_fd("minishell: ", 1);
	ft_pwd();
	ft_putstr_fd(" $ ", 1);
	return ;
}

void	print_prompt2(void)
{
	ft_putstr_fd("> ", 2);
	return ;
}
