/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_set_area.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:53:07 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/11 00:45:28 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

void
	mgen_set_area
	(t_gen *gen
	, t_u32_v2 v2
	, t_u32_v4 area
	, t_u8 fill)
{
	t_u32		dx;
	t_u32_v2	lu;
	t_u32_v2	rd;

	dx = V4L(area) + V4R(area);
	lu = DIFF2(t_u32, v2, V2(t_u32, V4L(area), V4U(area)));
	rd = SUM2(t_u32, v2, V2(t_u32, V4R(area), V4D(area)));
	while (!EQ2(lu, rd))
	{
		gen->map[lu.y * WIDTH(gen) + lu.x] = fill;
		lu = SUM2(t_u32
			, lu
			, (lu.x == rd.x ? V2(t_i32, (- dx), 1) : V2(t_i32, 1, 0)));
	}
	gen->map[lu.y * WIDTH(gen) + lu.x] = fill;
}
