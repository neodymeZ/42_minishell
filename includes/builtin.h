/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:09:26 by larosale          #+#    #+#             */
/*   Updated: 2020/10/31 02:56:01 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTIN_H
# define BUILTIN_H

/*
** Builtin functions
*/

int			ft_cd(char **command);
int			ft_pwd(void);
void		ft_exit(void);
int			ft_env(void);
int			ft_echo(char **args);
int			ft_export(char **var);
int			ft_unset(char **var);
int			ft_env(void);

/*
** Utils for env var functions
*/

int			check_varname(char *str);
void		split_value(char *var, char **value);
void		sort_env(char **env, int low, int high);

#endif
