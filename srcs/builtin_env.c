/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_env.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:57:33 by gejeanet          #+#    #+#             */
/*   Updated: 2020/11/09 09:46:55 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Minishell implementation of the bash builtin "env".
** Simply prints all environment's variables which have a value.
*/

int				ft_env(char **args)
{
	char	**env;

	if (args)
		;
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

int				ft_unset(char **args)
{
	int		result;

	result = 0;
	if (!args || !(*++args))
		return (0);
	while (*args != NULL)
	{
		if (check_varname(*args) == 0)
		{
			env_del_var(*args, g_env);
			env_del_var(*args, g_env_local);
		}
		else
		{
			errman(WAR_UNSET, *args);
			result = 1;
		}
		args++;
	}
	return (result);
}

/*
**
*/

static	void	prnt_var(char *var)
{
	ft_putstr_fd("declare -x ", 1);
	while (*var != '=' && *var != '\0')
		ft_putchar_fd(*var++, 1);
	if (*var == '\0')
	{
		ft_putstr_fd("\n", 1);
		return ;
	}
	ft_putstr_fd("=\"", 1);
	ft_putstr_fd(++var, 1);
	ft_putstr_fd("\"\n", 1);
}

/*
** Prints environment variables similarly to the bash export command.
*/

static	void	prnt_env(void)
{
	char	**p;
	char	*var;
	int		i;

	if (g_env == NULL || *g_env == NULL)
		return ;
	i = 0;
	p = g_env;
	while (*p++ != NULL)
		i++;
	sort_env(g_env, 0, i - 1);
	p = g_env;
	while (*p != NULL)
	{
		var = *p++;
		if (*var != '_' || *(var + 1) != '=')
			prnt_var(var);
	}
}

/*
** Minishell implementation of the bash builtin "export".
** If the argument to export does not specify value, or the var name
** is not compliant with the var name rules, an error is returned.
** Otherwise, the variable is added to env (or modified, if exists).
*/

int				ft_export(char **args)
{
	char	*value;
	int		result;

	result = 0;
	if (*++args == NULL)
	{
		prnt_env();
		return (0);
	}
	while (*args)
	{
		split_value(*args, &value);
		if (check_varname(*args) == 0)
			env_set_var(*args, value, &g_env);
		else
		{
			errman(WAR_EXPORT, *args);
			result = 1;
		}
		args++;
	}
	return (result);
}
