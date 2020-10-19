/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 20:00:34 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/19 00:01:29 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtin "echo" implementation (with ONLY -n option)
** ATTENTION! It is possible to pass to the "echo" command
** multiple options which are the same.
** For example:
** echo -n -n -n -e -n
** Another interesting example is:
** echo -n -n 1234567 -n -n
*/

int				ft_echo(char **args)
{
	int		lf_flag;
	int		opts_end_flag;

	lf_flag = 0;
	opts_end_flag = 0;
	if (args != NULL && *args != NULL)
	{
		while (*args != NULL)
		{
			if ((ft_strncmp(*args, "-n", 2) != 0) || (ft_strlen(*args) != 2) \
				|| opts_end_flag == 1)
			{
				opts_end_flag = 1;
				ft_putstr_fd(*args++, 1);
				if (*args != NULL)
					ft_putstr_fd(" ", 1);
				continue ;
			}
			lf_flag = 1;
			args++;
		}
	}
	if (lf_flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}
