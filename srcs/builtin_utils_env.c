/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils_env.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 01:25:11 by larosale          #+#    #+#             */
/*   Updated: 2020/10/27 19:48:40 by larosale         ###   ########.fr       */
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
** Prints environment variables similarly to the bash export command.
*/

void	prnt_env(void)
{
	char	**p;
	char	*var;

	p = g_env;
	while (*p != NULL)
	{
		ft_putstr_fd("declare -x ", 1);
		var = *p;
		while (*var != '=')
		{
			ft_putchar_fd(*var, 1);
			var++;
		}
		ft_putchar_fd('=', 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd(++var, 1);
		ft_putchar_fd('"', 1);
		ft_putstr_fd("\n", 1);
		p++;
	}
	return ;
}
