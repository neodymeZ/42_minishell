/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:27:02 by larosale          #+#    #+#             */
/*   Updated: 2020/11/09 12:59:53 by gejeanet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef ERRORS_H
# define ERRORS_H

/*
** The "e_errors" enum and corresponding type determine the list of error
** codes used for error handling with the following meaning:
**   - WAR_*: some non-fatal error (warnings). We do not exit() at this.
**   - ERR_SYS: system call error (file opening, memory allocation, etc);
**   - ERR_UNKNOWN: used in main to handle an error, not catched earlier
**     in helper functions;
**   - ERR_TOKEN: error when parsing tokens;
*/

typedef enum	e_errors
{
	WAR_NUM_ARG = 5,
	WAR_MANY_ARGS = 4,
	WAR_CD = 3,
	WAR_EXPORT = 2,
	WAR_UNSET = 1,
	ERR_OK = 0,
	ERR_UNKNOWN = -1,
	ERR_SYS = -2,
	ERR_TOKEN = -3,
	ERR_NOCMD = -4,
	ERR_NOFDIR = -5
}				t_errors;

void			print_error(int e, char *var);
int				errman(int errnum, char *var);

#endif
