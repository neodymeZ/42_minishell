/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdel.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/22 01:54:58 by larosale          #+#    #+#             */
/*   Updated: 2020/11/22 03:07:53 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

/*
** Deletes a char, located at "pos" from a null-terminated string.
*/

void	ft_strdel(char *pos)
{
	while (*pos)
	{
		*pos = *(pos + 1);
		pos++;
	}
	return ;
}
