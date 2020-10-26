/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin_functs.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:32:03 by larosale          #+#    #+#             */
/*   Updated: 2020/10/21 14:32:37 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	{
		path = env_get_var("HOME");
		if (path == NULL)
			return (0);
	}
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
** Exit function - quits minishell.
*/

void	ft_exit(void)
{
	ft_putstr_fd("exit\n", 1);
	exit(0);
}

/*
** builtin "echo" implementation (with ONLY -n option)
** ATTENTION! It is possible to pass to the "echo" command
** multiple options which are the same.
** For example:
** echo -n -n -n -e -n
** Another interesting example is:
** echo -n -n 1234567 -n -n
*/

int				ft_echo(char **args)
{
	int		lf_flag;
	int		opts_end_flag;

	lf_flag = 0;
	opts_end_flag = 0;
	if (args != NULL && *args != NULL)
	{
		args++;
		while (*args != NULL)
		{
			if ((ft_strncmp(*args, "-n", 2) != 0) || (ft_strlen(*args) != 2) \
				|| opts_end_flag == 1)
			{
				opts_end_flag = 1;
				ft_putstr_fd(*args++, 1);
				if (*args != NULL)
					ft_putstr_fd(" ", 1);
				continue ;
			}
			lf_flag = 1;
			args++;
		}
	}
	if (lf_flag == 0)
		ft_putstr_fd("\n", 1);
	return (0);
}