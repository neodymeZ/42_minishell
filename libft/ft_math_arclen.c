/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_math_arclen.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: larosale <larosale@42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/08/14 00:50:03 by larosale          #+#    #+#             */
/*   Updated: 2020/08/14 01:39:55 by larosale         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <math.h>
#define PI 3.14159265358979323846

/*
** Calculates length of an arc on a unit circle, from (1, 0) to (x, y) points.
*/

double ft_math_arclen(double x, double y)
{
	double	arclen;

	arclen = 0;
	if (x == 0.0 && y == 0.0)
		return (0.0);
	if (x >= 0 && y >= 0)
		arclen = acos(x);
	else if (x <= 0 && y >= 0)
		arclen = 0.5 * PI + asin(-x);
	else if (x <= 0 && y <= 0)
		arclen = 1.0 * PI + asin(-y);
	else if (x >= 0 && y <= 0)
		arclen = 1.5 * PI + asin(x);
	return (arclen);
}
