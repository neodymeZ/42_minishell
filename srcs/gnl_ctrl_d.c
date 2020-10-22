/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_ctrl_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:38:36 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/22 22:18:12 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static	void	clear_ctrl_d(void)
{
	ft_putstr_fd("  \b\b", 1);
}

int		gnl_ctrl_d(int fd, char **line)
{
	int			res;
	char		*tmp;
	char		*joined;
	char		*joined_tmp;

	joined = malloc(1);
	*joined = '\0';
	while (1)
	{
		res = get_next_line(fd, &tmp);
		joined_tmp = ft_strjoin(joined, tmp);
		free(joined);
		joined = joined_tmp;
		if (res != 0)
		{
			*line = joined;
			free(tmp);
			return (res);
		}
		else
		{
			if (*tmp == '\0')
			{
				clear_ctrl_d();
				if (*joined == '\0')
				{
					*line = joined;
					free(tmp);
					return (res);
				}
				free(tmp);
				continue ;
			}
			else
			{
				clear_ctrl_d();
			}
		}
	}
}
