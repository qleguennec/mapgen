/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_get_area.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:21:49 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/10 23:00:16 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define BOUND(x, y) (x > 0 && y > 0 && x < width - 1 && y < height - 1)
#define SET(x, y)(BOUND(x, y) && map[y * width + x] == MAP_POINT)

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
	while (SET((v2.x - (V4L(a) + 1)), v2.y))
		V4L(a)++;
	while (SET((v2.x + V4R(a) + 1), v2.y))
		V4R(a)++;
	while (SET(v2.x, (v2.y - (V4U(a) + 1))))
		V4U(a)++;
	while (SET(v2.x, (v2.y + V4D(a) + 1)))
		V4D(a)++;
	return (a);
}
