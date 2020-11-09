/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 00:41:24 by larosale          #+#    #+#             */
/*   Updated: 2020/11/09 09:55:44 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Prints error code based on error number "e" (see also errors.h).
*/

void	print_error(int e, char *var)
{
	e == ERR_SYS ? ft_putstr_fd("a system call error occured\n", 2) : 0;
	e == ERR_UNKNOWN ? ft_putstr_fd("unknown error occurred\n", 2) : 0;
	e == ERR_TOKEN ? ft_putstr_fd("syntax error near unexpected token\n", 2) : 0;
	if (e == ERR_NOCMD)
	{
		ft_putstr_fd(var, 2);
		ft_putstr_fd(": command not found\n", 2);
	}
	e == ERR_NOFDIR ? perror(var) : 0;
}

/*
** Prints error code based on error number "e" (see also errors.h).
** There ara no difference from print_error(). Simply for passing the norme.
*/
void	print_warning(int e, char *var)
{
	if (e == WAR_UNSET)
	{
		ft_putstr_fd("unset: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (e == WAR_EXPORT)
	{
		ft_putstr_fd("export: `", 2);
		ft_putstr_fd(var, 2);
		ft_putstr_fd("': not a valid identifier\n", 2);
	}
	else if (e == WAR_CD)
	{
		ft_putstr_fd("cd: ", 2);
		perror(var);
	}
}

/*
** Prints error message related to the error code "errnum".
** If "errno" was set by failed system calls or mlx, prints errno debug info.
** In case of successful exit, nothing is printed.
*/

int		errman(int errnum, char *var)
{
	if (!errnum)
		exit(EXIT_SUCCESS);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		if (errnum < 0)
		{
			print_error(errnum, var);
			if (errno && (errnum == ERR_SYS || errnum == ERR_UNKNOWN))
				perror("Additional debugging info (errno)");
			exit(errnum);
		}
		print_warning(errnum, var);
	}
	return (errnum);
}
