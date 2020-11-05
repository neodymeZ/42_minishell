/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 00:41:24 by larosale          #+#    #+#             */
/*   Updated: 2020/11/06 00:20:21 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints error code based on error number "e" (see also errors.h).
*/

void	print_error(int e)
{
	e == ERR_SYS ? ft_putstr_fd("a system call error occured\n", 2) : 0;
	e == ERR_UNKNOWN ? ft_putstr_fd("unknown error occurred\n", 2) : 0;
	e == ERR_TOKEN ? ft_putstr_fd("syntax error near unexpected token\n", 2) : 0;
	e == ERR_NOCMD ? ft_putstr_fd("command not found\n", 2) : 0;
	return ;
}

/*
** Prints error message related to the error code "errnum".
** If "errno" was set by failed system calls or mlx, prints errno debug info.
** In case of successful exit, nothing is printed.
*/

int		errman(int errnum)
{
	if (errnum)
	{
		ft_putstr_fd("minishell : ", 2);
		print_error(errnum);
		if (errno && (errnum == ERR_SYS || errnum == ERR_UNKNOWN))
			perror("Additional debugging info (errno)");
		exit(errnum);
		return (1);
	}
	else
	{
		exit(EXIT_SUCCESS);
		return (0);
	}
}
