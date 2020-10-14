/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:32:03 by larosale          #+#    #+#             */
/*   Updated: 2020/10/14 15:33:57 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

extern	char	**g_env;

/*
** Minishell implementation of the "cd" builtin bash function.
** Calls "chdir" function to the specified path ("path").
** Returns -1 on error, or 0 otherwise.
*/

int		ft_cd(char **command)
{
	char	*path;

	if (*(command + 1))
		path = *(command + 1);
	else
	// Implement $HOME env var usage to cd to home directory
		path = "/Users";
	return (chdir(path));
}

/*
** Minishell implementation of the "pwd" builtin bash function.
** Calls "getcwd" function with zero arguments (if no buffer is specified,
** getcwd allocates memory for the output with malloc).
** The path is printed and the string "pwd" is freed.
** Returns -1 on error, or 0 otherwise.
*/

int		ft_pwd(void)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	ft_putstr_fd(pwd, 1);
	free(pwd);
	return (0);
}

/*
** builtin "env" implementation
** simply prints all environment's variables
*/

int		ft_env(void)
{
	char	**env;

	env = g_env;
	while (*env != NULL)
	{
		ft_putstr_fd(*env, 1);
		ft_putstr_fd("\n", 1);
		env++;
	}
	return (0);
}

/*
** Exit function - quits minishell.
*/

void	ft_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}
