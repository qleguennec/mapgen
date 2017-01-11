/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_set_area.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:53:07 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/11 18:11:15 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

void
	mgen_set_area
	(t_gen *gen
	, t_u32_v2 v2
	, t_u32_v4 area
	, const t_u8 *fill)
{
	t_u32		dx;
	t_u32_v2	i;
	t_u32_v2	lu;
	t_u32_v2	rd;

	dx = V4L(area) + V4R(area);
	i = DIFF2(t_u32, v2, V2(t_u32, V4L(area), V4U(area)));
	lu = CPY2(t_u32, i);
	rd = SUM2(t_u32, v2, V2(t_u32, V4R(area), V4D(area)));
	while (!EQ2(i, rd))
	{
		MAP2(i) = fill[i.x == lu.x || i.x == rd.x || i.y == lu.y || i.y == rd.y
			? MAP_WALL : MAP_POINT];
		i = SUM2(t_u32
			, i
			, (i.x == rd.x ? V2(t_i32, (- dx), 1) : V2(t_i32, 1, 0)));
	}
	MAP2(i) = fill[MAP_POINT];
}
