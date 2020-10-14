/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_functs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:57:33 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/15 00:01:47 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char	**g_env;

/*
** builtin "env" implementation
** simply prints all environment's variables
*/

int		ft_env(void)
{
	char	**env;

	env = g_env;
	while (*env != NULL)
	{
		ft_putstr_fd(*env, 1);
		ft_putstr_fd("\n", 1);
		env++;
	}
	return (0);
}

/*
** builtin "unset"
** remove variable
** TODO -- multiple args support
*/

int		ft_unset(char *var)
{
	if (var == NULL)
		return (0);
	return (env_del_var(var));
}

/*
** builtin "export"
** TODO -- multiple args support
*/

int		ft_export(char *var, char *value)
{
	if (value == NULL || var == NULL)
		return (0);
	if (!env_set_var(var, value))
		return (errman(ERR_UNKNOWN));
	if (!env_export_var(var))
		return (errman(ERR_UNKNOWN));
	return (0);
}
