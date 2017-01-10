/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_get_area.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:21:49 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/10 16:45:03 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define SET(x)		(x == MAP_POINT)
#define LEFT(m)		(SET((m)[v2.y * width + (v2.x - 1)]))
#define UP(m)		(SET((m)[(v2.y - 1) * width + v2.x]))
#define RIGHT(m)	(SET((m)[v2.y * width + (v2.x + 1)]))
#define DOWN(m)		(SET((m)[(v2.y + 1) * width + v2.x]))

t_u32_v4
	mgen_get_area
	(t_u32 *map
	 , t_u32 width
	 , t_u32 height
	 , t_u32_v2 v2)
{
	t_u32_v4	a;

	a.a = 0;
	a.b = 0;
	a.c = 0;
	a.d = 0;
	while (v2.x - V4L(a) && LEFT(map))
		V4L(a)++;
	while (v2.y - V4U(a) && UP(map))
		V4U(a)++;
	while (v2.x + V4R(a) < width && RIGHT(map))
		V4R(a)++;
	while (v2.y + V4D(a) < height && DOWN(map))
		V4D(a)++;
	return (a);
}
