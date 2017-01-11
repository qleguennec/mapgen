/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_walls.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/11 16:41:35 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/11 18:00:13 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

void
	mgen_walls
	(t_gen *gen
	, t_u32_v2 v2
	, t_u32_v4 area
	, const t_u8 *fill)
{
	char		c;
	t_u32		dx;
	t_u32_v2	lu;
	t_u32_v2	rd;

	c = fill[MAP_WALL];
	dx = V4L(area) + V4R(area);
	PRINT("area\t", 0);
	ECHO4_U32(area);
	PRINT("v2\t", 0);
	ECHO2_U32(v2);
	lu = DIFF2(t_u32, v2, V2(t_u32, V4L(area), V4U(area)));
	rd = SUM2(t_u32, v2, V2(t_u32, V4R(area), V4D(area)));
	while (lu.x <= rd.x)
		MAP(lu.x++, lu.y) = c;
	while (lu.y <= rd.y)
		MAP(lu.x, lu.y++) = c;
	lu = DIFF2(t_u32, v2, V2(t_u32, V4L(area), V4U(area)));
	while (lu.y <= rd.y)
		MAP(lu.x, lu.y++) = c;
	while (lu.x <= rd.x)
		MAP(lu.x++, lu.y) = c;
}
