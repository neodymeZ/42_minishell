/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/05/18 15:23:03 by larosale          #+#    #+#             */
/*   Updated: 2020/06/01 02:56:15 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <sys/types.h>
#include <sys/uio.h>
#include <unistd.h>
#include <stdlib.h>
#include "libft.h"

/*
** Validates input and initializes variables.
** Memory allocation: BUFFER_SIZE + 2 bytes.
*/

static int		validate_input(char **line, char **buffer, size_t *line_len,
	int fd)
{
	if (!(*line = malloc(1)) || fd < 0 || !line || BUFFER_SIZE <= 0 ||
		!(*buffer = malloc(BUFFER_SIZE + 1)))
		return (0);
	*line_len = 0;
	**line = '\0';
	return (1);
}

/*
** Frees the allocated memory based on the "exit_code" and handles
** the appropriate return code to the "get_next_line" function.
*/

static int		free_memory(int exit_code, char **buffer, char **remainder)
{
	if ((exit_code == MEM_ERREAD) || (exit_code == MEM_EOF))
	{
		free(*buffer);
		if (*remainder)
		{
			free(*remainder);
			*remainder = NULL;
		}
		return (exit_code == MEM_EOF ? 0 : -1);
	}
	else if (exit_code == MEM_ERINIT)
		return (-1);
	else if (exit_code == MEM_REMCUT)
	{
		free(*buffer);
		return (1);
	}
	else if (exit_code == MEM_REMAPP)
	{
		free(*remainder);
		*remainder = NULL;
		return (1);
	}
	return (0);
}

/*
** Cuts buffer on '\n' symbol, located on "eol_position". The newline symbol
** is replaced by '\0' and the remainder string is returned.
** Memory allocation: remainder length + 1 bytes.
*/

static int		cut_remainder(int flag, char **line, char **buffer,
	char **remainder)
{
	size_t	remainder_len;
	char	*eol_position;

	eol_position = NULL;
	if (flag == REM_LINE)
		eol_position = ft_strchr(*line, '\n');
	else if (flag == REM_BUFF)
		eol_position = ft_strchr(*buffer, '\n');
	if (eol_position)
	{
		*eol_position++ = '\0';
		remainder_len = ft_strlen(eol_position);
		if (!(*remainder = malloc(remainder_len + 1)))
			return (0);
		ft_strlcpy(*remainder, eol_position, remainder_len + 1);
		return (1);
	}
	return (0);
}

/*
** Appends string "append" to the string, pointed to by pointer "line".
** Returns 1 on success, or 0 on error.
** Memory allocation: resulting line length + 1 bytes.
** Memory freeing: previous line length + 1 bytes.
*/

static int		append_to_line(char **line, char *append, size_t *line_len)
{
	size_t	new_len;
	char	*temp_line;

	new_len = *line_len + ft_strlen(append);
	if (!(temp_line = ft_realloc(*line, new_len + 1, *line_len + 1)))
		return (0);
	*line = temp_line;
	temp_line += *line_len;
	while (*append)
		*temp_line++ = *append++;
	*temp_line = '\0';
	*line_len = new_len;
	return (1);
}

/*
** Validates input and allocates memory for "buffer", then reinitializes
** "line".
** If the "remainder" pointer is not NULL (i.e. the remainder was
** left after previous function calls), appends it to "line" and frees.
** If, after appending remainder, the line has '\n' characters cuts a new
** remainder and returns.
** Reads the input at "fd" descriptor. If the buffer contains '\n' char,
** cuts the remainder and returns.
** Appends the read buffer to the line and returns.
** As the function get_next_line always allocates memory for the "*line",
** the caller must properly free it after calls.
*/

int				get_next_line(int fd, char **line)
{
	char		*buffer;
	static char	*remainder;
	ssize_t		bytes_read;
	size_t		line_len;

	if (!validate_input(line, &buffer, &line_len, fd))
		return (free_memory(MEM_ERINIT, &buffer, &remainder));
	if (remainder && append_to_line(line, remainder, &line_len))
	{
		free_memory(MEM_REMAPP, &buffer, &remainder);
		if (cut_remainder(REM_LINE, line, &buffer, &remainder))
			return (free_memory(MEM_REMCUT, &buffer, &remainder));
	}
	while ((bytes_read = read(fd, buffer, BUFFER_SIZE)))
	{
		if (bytes_read < 0)
			return (free_memory(MEM_ERREAD, &buffer, &remainder));
		*(buffer + bytes_read) = '\0';
		if (cut_remainder(REM_BUFF, line, &buffer, &remainder)
			&& append_to_line(line, buffer, &line_len))
			return (free_memory(MEM_REMCUT, &buffer, &remainder));
		append_to_line(line, buffer, &line_len);
	}
	return (free_memory(MEM_EOF, &buffer, &remainder));
}
