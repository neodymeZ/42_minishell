/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gnl_ctrl_d.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gejeanet <gejeanet@student.21-school.ru>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/10/22 11:38:36 by gejeanet          #+#    #+#             */
/*   Updated: 2020/10/22 16:42:19 by gejeanet         ###   ########.fr       */
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
				clear_ctrl_d();
			return (res);
		}
		else
		{
			if (*tmp == '\0')
			{
				if (*joined == '\0')
				{
					*line = joined;
					free(tmp);
				clear_ctrl_d();
					return (res);
				}
				free(tmp);
				clear_ctrl_d();
				continue ;
			}
			else
			{
				joined_tmp = ft_strjoin(joined, tmp);
				free(tmp);
				free(joined);
				joined = joined_tmp;
				clear_ctrl_d();
			}
		}
	}
}
