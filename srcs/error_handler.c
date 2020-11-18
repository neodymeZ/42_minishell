/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_handler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/26 00:41:24 by larosale          #+#    #+#             */
/*   Updated: 2020/11/18 18:22:45 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Helper function to set the "g_status" global variable value to the exit
** status, based on the error code.
*/

static void	set_status(int e)
{
	if (e == ERR_NUMARG)
		g_status = 255;
	else if (e == ERR_SYSCMD)
		g_status = 127;
	else if (e == ERR_TOKEN)
		g_status = 258;
	else
		g_status = 1;
	return ;
}

/*
** Helper function to write error message composed of three strings.
*/

static void	wr_msg(char *str1, char *str2, char *str3, char *str4)
{
	if (str1)
		ft_putstr_fd(str1, 2);
	if (str2)
		ft_putstr_fd(str2, 2);
	if (str3)
		ft_putstr_fd(str3, 2);
	if (str4)
		ft_putstr_fd(str4, 2);
	ft_putchar_fd('\n', 2);
	return ;
}

/*
** Prints error code based on error number "e" (see also errors.h).
*/

void		print_error(int e, char *var, char **args)
{
	if (e == ERR_TOKEN)
		wr_msg("syntax error near unexpected token `", var, "'", 0);
	else if (e == ERR_NOCMD && args)
		wr_msg(*args, ": command not found", 0, 0);
	else if (e == ERR_NOHOME && args)
		wr_msg(*args, ": HOME not set", 0, 0);
	else if (e == ERR_MNARGS && args)
		wr_msg(*args, ": too many arguments", 0, 0);
	else if (e == ERR_NUMARG && args)
		wr_msg(*args, ": ", *(args + 1), ": numeric argument required");
	else if (e == ERR_INVLID && args)
		wr_msg(var, ": `", *args, "': not a valid identifier");
	if (e == ERR_SYSCMD)
	{
		*args ? ft_putstr_fd(*args, 2) : 0;
		*args ? ft_putstr_fd(": ", 2) : 0;
		if (errno)
			perror(var);
		else
			ft_putstr_fd("unknown error occurred\n", 2);
	}
	return ;
}

/*
** Error handler function.
** If the error happened in a system call, or is unknown and not recoverable,
** the process exits (ERR_SYS and ERR_UNKNOWN codes).
** Otherwise, the respective error message is printed.
*/

int			errman(int errnum, char *var, char **args)
{
	if (!errnum)
		return (0);
	else
	{
		ft_putstr_fd("minishell: ", 2);
		if (errnum == ERR_SYS)
		{
			if (errno)
				perror("");
			else
				ft_putstr_fd("unknown error occurred\n", 2);
			g_status = 1;
			exit(g_status);
		}
		print_error(errnum, var, args);
		set_status(errnum);
	}
	return (1);
}
