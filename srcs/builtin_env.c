/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:57:33 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/27 19:58:25 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Minishell implementation of the bash builtin "env".
** Simply prints all environment's variables which have a value.
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
** Minishell implementation of the bash builtin "unset".
** Removes env variable (if it exists) from both local and global env contexts.
** Returns 0 if successful, or 1 on error.
*/

int				ft_unset(char **var)
{
	int		result;

	result = 0;
	if (!var || !(*++var))
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
		// add errman call
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
** Minishell implementation of the bash builtin "export".
** If the argument to export does not specify value, or the var name
** is not compliant with the var name rules, an error is returned.
** Otherwise, the variable is added to env (or modified, if exists).
*/

int				ft_export(char **var)
{
	char	*value;
	int		result;

	value = NULL;
	result = 0;
	if (*++var == NULL)
	{
		prnt_env();
		return (0);
	}
	while (*var)
	{
		// add errman call (not a valid identifier - no value was found)
		if (split_value(*var, &value))
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(*var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			result = 1;
			var++;
			continue ;
		}
		if (check_varname(*var) == 0)
			env_set_var(*var, value, &g_env);
		// add errman call
		else
		{
			ft_putstr_fd("minishell: export: `", 2);
			ft_putstr_fd(*var, 2);
			ft_putstr_fd("': not a valid identifier\n", 2);
			result = 1;
			var++;
			continue ;
		}
		var++;
	}
	return (result);
}
