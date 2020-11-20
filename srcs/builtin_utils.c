/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/20 18:55:46 by gejeanet          #+#    #+#             */
/*   Updated: 2020/11/20 19:25:10 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	update_cd_var(char *var, char *value)
{
	if (find_var(var, g_env) != NULL)
		env_set_var(var, value, &g_env);
	else
		env_set_var(var, value, &g_env_local);
}

/*
** Updates the PWD and OLDPWD variables to the actual value.
** It depends from where this variables exist (global or local)
*/

void			maintain_cd_env_var(char *oldpwd)
{
	char	*pwd;

	update_cd_var("OLDPWD", oldpwd);
	pwd = getcwd(NULL, 0);
	update_cd_var("PWD", pwd);
	free(pwd);
}
