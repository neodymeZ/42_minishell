/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_utils.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/14 20:14:39 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/14 21:35:08 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char	**g_env;
extern	char	**g_env_local;

/*
** return a pointer to variable value
** it MUST NOT be passed to free() !!!
** NULL if variable does not exist
*/

char			*env_get_var(char *var)
{
}

int				env_set_var(char *var, char *value)
{
}

int				env_del_var(char *var)
{
}

int				env_export_var(char *var)
{
}
