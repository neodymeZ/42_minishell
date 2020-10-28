/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strsubst.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/28 18:12:47 by larosale          #+#    #+#             */
/*   Updated: 2020/10/29 00:33:04 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

/*
** Replaces the first occurence of substring "src" in string "str" to
** string "dst".
** If "str" or "src" are NULL, or an error occurred, NULL is returned.
** Otherwise, the resulting string is returned.
** If "dst" is NULL, the "src" is deleted from "str".
*/

char	*ft_strsubst(char *str, char *src, char *dst)
{
	size_t	str_len;
	size_t	new_len;
	char	*tmp;
	char	*result;
	char	*start_pos;

	if (!str || !src)
		return (NULL);
	str_len = ft_strlen(str);
	if (!(start_pos = ft_strnstr(str, src, str_len)))
		return (NULL);
	new_len = str_len - ft_strlen(src) + (dst ? ft_strlen(dst) : 0);
	if (!(result = ft_calloc(new_len + 1, 1)))
		return (NULL);
	tmp = result;
	while (*str && str != start_pos)
		*tmp++ = *str++;
	while (*str && *str == *src)
		*str++ = *src++;
	while (dst && *dst)
		*tmp++ = *dst++;
	while (*str)
		*tmp++ = *str++;
	return (result);
}
