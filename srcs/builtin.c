/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:32:03 by larosale          #+#    #+#             */
/*   Updated: 2020/11/09 09:38:36 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Minishell implementation of the "cd" builtin bash function.
** Calls "chdir" function to the specified path ("path").
** Returns -1 on error, or 0 otherwise.
*/

int		ft_cd(char **args)
{
	char	*path;
	int		res;

	if (*(args + 1))
		path = *(args + 1);
	else
	{
		path = env_get_var("HOME");
		if (path == NULL)
			return (0);
	}
	if ((res = chdir(path)) != 0)
		errman(WAR_CD, path);
	return (res);
}

/*
** Minishell implementation of the "pwd" builtin bash function.
** Calls "getcwd" function with zero arguments (if no buffer is specified,
** getcwd allocates memory for the output with malloc).
** The path is printed and the string "pwd" is freed.
** Returns -1 on error, or 0 otherwise.
*/

int		ft_pwd(char **args)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
		return (-1);
	ft_putstr_fd(pwd, 1);
	if (args)
		ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);
}

/*
** Exit function - quits minishell.
*/

// Set errman
int		ft_exit(char **args)
{
	if (!args || (*args && *(args + 1) == NULL))
	{
		ft_putstr_fd("exit\n", 2);
		exit(0);
	}
	else if (*args && *(args + 1) && *(args + 2) == NULL)
	{
		if (!(ft_isnumeric(*(args + 1))))
		{
			ft_putstr_fd("numeric argument required\n", 2);
			exit(255);
		}
		ft_putstr_fd("exit\n", 2);
		exit(ft_atoi(*(args + 1)));
	}
	else
	{
		ft_putstr_fd("too many arguments\n", 2);
		return (1);
	}
	return (0);
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

int		ft_echo(char **args)
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

/*
** Builtin test function - does nothing :)
*/

int		ft_test(char **args)
{
	if (args)
		;
	return (0);
}
