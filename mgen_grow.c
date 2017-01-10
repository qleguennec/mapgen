/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_grow.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/09 16:16:17 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/10 14:45:18 by qle-guen         ###   ########.fr       */
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
	t_u32_v4	new_area;

	new_area = SUM4(t_u32
		, area
		, mgen_get_area(gen->map
			, WIDTH(gen)
			, HEIGHT(gen)
			, v2));
	mgen_set_area(gen, v2, new_area, fill);
	return (new_area);
}
