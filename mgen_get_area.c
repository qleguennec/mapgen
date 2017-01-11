/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_get_area.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:21:49 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/11 17:55:53 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define BOUND(a, b) (a < gen->xbound.y && b < gen->ybound.y)
#define SET(a, b) (BOUND(a, b) && MAP(a, b) == c)

t_u32_v4
	mgen_get_area
	(t_gen *gen
	 , t_u32_v2 v2
	 , t_u8 c)
{
	t_u32_v4	a;

	a = V4(t_u32, 0, 0, 0, 0);
	while (SET(v2.x - V4L(a) + 1, v2.y))
		V4L(a)++;
	while (SET(v2.x + V4R(a) + 1, v2.y))
		V4R(a)++;
	while (SET(v2.x, v2.y - V4U(a) + 1))
		V4U(a)++;
	while (SET(v2.x, v2.y + V4D(a) + 1))
		V4D(a)++;
	return (a);
}
