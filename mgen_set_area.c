/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_set_area.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 17:53:07 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/10 16:14:14 by qle-guen         ###   ########.fr       */
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
	t_u32		i;
	t_u32_v2	lu;
	t_u32_v2	rd;

	dx = V4L(area) + V4R(area);
	lu = DIFF2(t_u32, V2(t_u32, V4L(area), V4U(area)), v2);
	rd = SUM2(t_u32, v2, V2(t_u32, V4R(area), V4D(area)));
	i = 0;
	while (!EQ2(lu, rd))
	{
		if (lu.x >= gen->xbound.x && lu.y <= gen->xbound.y)
			gen->map[lu.x * WIDTH(gen) + lu.y] = fill;
		SUM2(t_u32, lu, (i && !(i % dx) ? V2(t_u32, (- dx), 1) : V2(t_u32, 1, 0)));
		i++;
	}
}
