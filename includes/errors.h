/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/25 19:27:02 by larosale          #+#    #+#             */
/*   Updated: 2020/10/12 20:11:29 by larosale         ###   ########.fr       */
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
*/

typedef enum	e_errors
{
	ERR_OK = 0,
	ERR_UNKNOWN = -1,
	ERR_SYS = -2
}				t_errors;

#endif
