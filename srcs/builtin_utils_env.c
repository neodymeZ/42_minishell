/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 01:25:11 by larosale          #+#    #+#             */
/*   Updated: 2020/10/26 01:25:13 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		check_varname(char *str)
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

void	get_name_and_value(char *var, char **name, char **value)
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

void	prnt_env(void)
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
