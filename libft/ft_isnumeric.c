/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isnumeric.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/08 02:51:48 by larosale          #+#    #+#             */
/*   Updated: 2020/11/08 03:01:32 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Checks, whether the input string is numeric, i.e. starts with a sign symbol
** and then consists only of digits.
** Returns 1 if the string is numeric and 0 otherwise.
*/

int	ft_isnumeric(char *str)
{
	if (*str == '+' || *str == '-')
		str++;
	while (*str && ft_isdigit(*str))
		str++;
	if (*str)
		return (0);
	return (1);
}
