/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtin.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/26 02:09:26 by larosale          #+#    #+#             */
/*   Updated: 2020/10/27 02:33:39 by larosale         ###   ########.fr       */
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
int			split_value(char *var, char **value);
void		prnt_env(void);

#endif
