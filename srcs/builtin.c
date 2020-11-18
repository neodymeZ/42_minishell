/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/12 20:32:03 by larosale          #+#    #+#             */
/*   Updated: 2020/11/18 19:28:25 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
** Minishell implementation of the "cd" builtin bash function.
** Calls "chdir" function to the specified path ("path").
** Returns 1 on error, or 0 otherwise.
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
		{
			errman(ERR_NOHOME, NULL, args);
			return (1);
		}
	}
	if ((res = chdir(path)) != 0)
	{
		errman(ERR_SYSCMD, path, args);
		return (1);
	}
	return (0);
}

/*
** Minishell implementation of the "pwd" builtin bash function.
** Calls "getcwd" function with zero arguments (if no buffer is specified,
** getcwd allocates memory for the output with malloc).
** The path is printed and the string "pwd" is freed.
** Returns 1 on error, or 0 otherwise.
*/

int		ft_pwd(char **args)
{
	char	*pwd;

	pwd = NULL;
	pwd = getcwd(NULL, 0);
	if (!pwd)
	{
		errman(ERR_SYSCMD, NULL, args);
		return (1);
	}
	ft_putstr_fd(pwd, 1);
	if (args)
		ft_putchar_fd('\n', 1);
	free(pwd);
	return (0);
}

/*
** Exit function - quits minishell.
** While in pipe, exit does not print "exit" to stderr.
*/

int		ft_exit_pipe(char **args)
{
	if (!args || (*args && *(args + 1) == NULL))
		exit(g_status);
	else if ((ft_isnumeric(*(args + 1))))
	{
		if (*args && *(args + 1) && *(args + 2))
		{
			errman(ERR_MNARGS, NULL, args);
			return (1);
		}
		exit(ft_atoi(*(args + 1)));
	}
	else
	{
		errman(ERR_NUMARG, NULL, args);
		exit(g_status);
	}
	return (0);
}

/*
** Wrapper function to "ft_exit_pipe" - prints "exit" to stderr,
** if not in pipe.
*/

int		ft_exit(char **args)
{
	ft_putstr_fd("exit\n", 2);
	return (ft_exit_pipe(args));
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
				(*args != NULL) ? ft_putstr_fd(" ", 1) : 0;
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
