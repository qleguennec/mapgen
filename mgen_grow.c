/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_grow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:16:17 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/11 00:56:11 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

t_u32_v4
	mgen_grow
	(t_gen *gen
	, t_u32_v2 v2
	, t_u32_v4 area
	, t_u8 fill)
{
	t_u32_v4	a;

	a = mgen_get_area(gen->map, WIDTH(gen), HEIGHT(gen), v2);
	if (V4L(a) + V4L(area) + gen->xbound.x <= v2.x)
		V4L(a) += V4L(area);
	if (V4U(a) + V4U(area) + gen->ybound.x <= v2.y)
		V4U(a) += V4U(area);
	if (V4R(a) + V4R(area) + v2.x <= gen->xbound.y)
		V4R(a) += V4R(area);
	if (V4D(a) + V4D(area) + v2.y <= gen->ybound.y)
		V4D(a) += V4D(area);
	mgen_set_area(gen, v2, a, fill);
	return (a);
}
