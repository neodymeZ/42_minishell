/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env_functs.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:57:33 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/17 02:59:12 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char	**g_env;
extern	char	**g_env_local;

static	int		check_varname(char *str)
{
	int		result;

	result = 0;
	if (ft_strlen(str) == 0)
		return (1);
	while (*str != '\0')
	{
		if (!ft_isalnum(*str) && (*str != '_'))
		{
			result = 1;
			break ;
		}
		str++;
	}
	return (result);
}

static	void	get_name_and_value(char *var, char **name, char **value)
{
	char	*p;

	p = ft_strchr(var, '=');
	if (p == NULL)
	{
		*value = NULL;
		*name = ft_strdup(var);
	}
	else
	{
		*value = p + 1;
		*name = malloc(p - var + 1);
		ft_memmove(*name, var, p - var);
		*(*name + (p - var)) = '\0';
	}
}

static	void	prnt_env(void)
{
	char	**p;
	char	*name;
	char	*value;

	p = g_env;
	while (*p != NULL)
	{
		get_name_and_value(*p, &name, &value);
		ft_putstr_fd("declare -x ", 1);
		ft_putstr_fd(name, 1);
		if (value != NULL)
		{
			ft_putstr_fd("=", 1);
			ft_putchar_fd('"', 1);
			ft_putstr_fd(value, 1);
			ft_putchar_fd('"', 1);
		}
		ft_putstr_fd("\n", 1);
		free(name);
		p++;
	}
}

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
		prnt_env();
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
