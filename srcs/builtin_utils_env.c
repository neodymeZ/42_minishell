/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 01:25:11 by larosale          #+#    #+#             */
/*   Updated: 2020/11/20 18:43:14 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks the environment variable name "str" for validity.
** Returns 0 if the name is valid, or 0 otherwise.
*/

int				check_varname(char *str)
{
	if (!ft_strlen(str))
		return (1);
	if (!ft_isalpha(*str))
		return (1);
	while (*str)
	{
		if (!ft_isalnum(*str) && (*str != '_'))
			return (1);
		str++;
	}
	return (0);
}

/*
** Splits the full env var string "var" on the "=" char.
** Cut var (replace '=' to '\0')
** Pointer to the value (if present) is saved to *value.
*/

void			split_value(char *var, char **value)
{
	char	*p;

	if (!(p = ft_strchr(var, '=')))
	{
		*value = NULL;
		return ;
	}
	*p = '\0';
	*value = p + 1;
}

/*
** It is a helper function for sort_env() via quicksort algo.
** There is no needs to implement a ft_strcmp() for compare any strings.
** 1000000 is enough.
*/

static	int		partition_for_quicksort(char **env, int l, int h)
{
	char	*v;
	char	*tmp;
	int		i;
	int		j;

	i = l;
	j = h;
	v = env[(l + h) / 2];
	while (i <= j)
	{
		while (ft_strncmp(env[i], v, 1000000) < 0)
			i++;
		while (ft_strncmp(env[j], v, 1000000) > 0)
			j--;
		if (i >= j)
			break ;
		tmp = env[i];
		env[i] = env[j];
		env[j] = tmp;
		i++;
		j--;
	}
	return (j);
}

/*
** Sort (quicksort) env variables (we need this before printing the
** environment).
*/

void			sort_env(char **env, int low, int high)
{
	int		base;

	if (low < high)
	{
		base = partition_for_quicksort(env, low, high);
		sort_env(env, low, base);
		sort_env(env, base + 1, high);
	}
}

/*
** Export variable.
** It create/update var if var does NOT exist in any (global or local) table
** OR value is NOT NULL.
** If var exists in local env table AND value is NULL,
** it create var in global env table with a value from local env table.
*/

void			env_export_var(char *var, char *value)
{
	char	*local_value;

	if (env_get_var(var) == NULL || value != NULL)
		env_set_var(var, value, &g_env);
	else if (find_var(var, g_env) != NULL)
		return;
	else
	{
		local_value = find_var(var, g_env_local);
		env_set_var(var, local_value, &g_env);
	}
}
