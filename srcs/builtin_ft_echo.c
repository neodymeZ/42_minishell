/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_ft_echo.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/18 20:00:34 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/18 22:53:56 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int				ft_echo(char **args)
{
	int		result;
	int		lf_flag;

	result = 0;
	lf_flag = 0;
	if (args != NULL && *args != NULL)
	{
		if ((ft_strncmp(*args, "-n", 2) == 0) && (ft_strlen(*args) == 2))
		{
			lf_flag = 1;
			args++;
			continue ;
		}
		ft_putstr_fd(args, 1);
		args++;
		while (*args != NULL)
		{
			ft_putstr_fd(" ", 1);
			ft_putstr_fd(args, 1);
			args++;
		}
	}
	if (lf_flag == 0)
		ft_putstr_fd("\n", 1);
	return (result);
}
