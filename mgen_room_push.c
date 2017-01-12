/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_room_push.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 11:19:49 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/12 17:04:52 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

void
	mgen_room_push
	(t_gen *gen
	, t_u32_v4 room
	, t_u32_v2 *bounds
	, t_u8 *fill)
{
	t_u32_v2	rb;
	t_u32_v2	lu;

	rb = V4_V2(t_u32, room, SUM2);
	lu = V2(t_u32, room.a, room.b);
	while (NEQ2(lu, rb))
	{
		MAP2(lu) = fill[lu.x == V4X(room)
			|| lu.y == V4Y(room)
			|| lu.x == rb.x
			|| lu.y == rb.y
			? MAP_WALL : MAP_POINT];
		lu = SUM2(t_u32
			, lu
			, (lu.x == rb.x ? V2(t_i32, (- V4W(room)), 1) : V2(t_i32, 1, 0)));
	}
	MAP2(rb) = fill[MAP_WALL];
}