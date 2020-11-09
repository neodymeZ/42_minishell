/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:09:26 by larosale          #+#    #+#             */
/*   Updated: 2020/11/08 03:00:25 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*
** Builtin functions
*/

int			ft_cd(char **args);
int			ft_pwd(char **args);
int			ft_exit(char **args);
int			ft_env(char **args);
int			ft_echo(char **args);
int			ft_export(char **args);
int			ft_unset(char **args);
int			ft_env(char **args);
int			ft_test(char **args);

/*
** Utils for env var functions
*/

int			check_varname(char *str);
void		split_value(char *var, char **value);
void		sort_env(char **env, int low, int high);

/*
** Structure is used to enumerate all builtin functions in an struct array,
** used then to launch the respective builtin.
*/

typedef struct	s_builtin
{
	char	*cmd;
	int		(*builtin_f)(char **);
}				t_builtin;

#endif
