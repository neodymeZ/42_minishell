/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_functs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:57:33 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/18 21:39:15 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** builtin "env" implementation
** simply prints all environment's variables which have a value
*/

int				ft_env(void)
{
	char	**env;

	env = g_env;
	while (*env != NULL)
	{
		if (ft_strchr(*env, '='))
		{
			ft_putstr_fd(*env, 1);
			ft_putstr_fd("\n", 1);
		}
		env++;
	}
	return (0);
}

/*
** builtin "unset"
** remove variables (if exists) from local AND global table
** returns completion code
*/

int				ft_unset(char **var)
{
	int		result;

	result = 0;
	if (var == NULL)
		return (0);
	while (*var != NULL)
	{
		if (check_varname(*var) == 0)
		{
			env_del_var(*var, g_env);
			env_del_var(*var, g_env_local);
		}
		else
		{
			ft_putstr_fd("minishell: unset: `", 2);
			ft_putstr_fd(*var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			result = 1;
		}
		var++;
	}
	return (result);
}

/*
** builtin "export"
** remove variables (if exists) from local env table (g_env_local)
** and add it (or update if exists) into global env table (g_env)
** returns completion code
*/

int				ft_export(char **var)
{
	int		result;
	char	*name;
	char	*value;

	result = 0;
	if (var == NULL || *var == NULL)
	{
		prnt_env();
		return (result);
	}
	while (*var != NULL)
	{
		get_name_and_value(*var, &name, &value);
		if (check_varname(name) == 0)
		{
			if (value == NULL)
				value = env_get_var(name);
			env_set_var(name, value, g_env);
			env_del_var(name, g_env_local);
		}
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(*var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			result = 1;
		}
		free(name);
		var++;
	}
	return (result);
}
