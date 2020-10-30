/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 01:25:11 by larosale          #+#    #+#             */
/*   Updated: 2020/10/30 17:31:57 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Checks the environment variable name "str" for validity.
** Returns 0 if the name is valid, or 0 otherwise.
*/

int		check_varname(char *str)
{
	if (!ft_strlen(str))
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
** Pointer to the value is saved to *value.
** Returns 0 if successfull, or 1 if no value was found.
*/

int		split_value(char *var, char **value)
{
	char	*p;

	if (!(p = ft_strchr(var, '=')))
		return (1);
	*p = '\0';
	*value = p + 1;
	return (0);
}

/*
** It is a helper function for sort_env() via quicksort algo.
** There is no needs to implement a ft_strcmp() for compare any strings.
** 1000000 is enough.
*/

int		partition_for_quicksort(char **env, int l, int h)
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
** Sort (quicksort) env variables (we need this before printing the environment).
*/

void	sort_env(char **env, int low, int high)
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
** Prints environment variables similarly to the bash export command.
*/

void	prnt_env(void)
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
		{
			ft_putstr_fd("declare -x ", 1);
			while (*var != '=')
				ft_putchar_fd(*var++, 1);
			ft_putstr_fd("=\"", 1);
			ft_putstr_fd(++var, 1);
			ft_putstr_fd("\"\n", 1);
		}
	}
}
