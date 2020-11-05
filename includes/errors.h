/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:27:02 by larosale          #+#    #+#             */
/*   Updated: 2020/11/05 22:26:32 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/*
** The "e_errors" enum and corresponding type determine the list of error
** codes used for error handling with the following meaning:
**   - ERR_SYS: system call error (file opening, memory allocation, etc);
**   - ERR_UNKNOWN: used in main to handle an error, not catched earlier
**     in helper functions;
**   - ERR_TOKEN: error when parsing tokens;
*/

typedef enum	e_errors
{
	ERR_OK = 0,
	ERR_UNKNOWN = -1,
	ERR_SYS = -2,
	ERR_TOKEN = -3,
	ERR_NOCMD = -4
}				t_errors;

void			print_error(int e);
int				errman(int errnum);

#endif
