/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:47:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/15 01:21:27 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define X V4X(*room)
#define Y V4Y(*room)
#define W V4W(*room)
#define H V4H(*room)

#define ARBRAND RAND(2, 256)

#define MAX_ATTEMPTS 100

static bool
	get_exit
	(t_gen *gen
	, t_u32_v2 *bounds
	, t_u32_v4 *room)
{
	t_u32		dx;
	t_u32		dy;
	t_u32		max;
	t_u32_v4	direction;

	dx = BRAND(WRAND);
	dy = BRAND(HRAND);
	direction.a = (X >= dx && Y + dy < HEIGHT.y) ? ARBRAND : 0;
	direction.b = (Y >= dy && X + dx < WIDTH.y) ? ARBRAND : 0;
	direction.c = (Y + dy < HEIGHT.y && X + W + dx < WIDTH.y) ? ARBRAND : 0;
	direction.d = (Y + H + dy < HEIGHT.y && X + dx < WIDTH.y) ? ARBRAND : 0;
	max = mgen_v4_max(direction);
	if (!max)
		return (false);
	if (max == 1)
		*room = V4(t_u32, X - dx, Y, dx, dy);
	else if (max == 2)
		*room = V4(t_u32, X, Y - dy, dx, dy);
	else if (max == 4)
		*room = V4(t_u32, X + W, Y, dx, dy);
	else if (max == 8)
		*room = V4(t_u32, X, Y + H, dx, dy);
	return (mgen_v4_is_free(gen->rooms, *room));
}

void
	mgen_gen
	(t_gen *gen
	, t_u32_v2 *bounds
	, t_u8 *fill)
{
	t_u32		attempts;
	t_u32_v4	room;

	room = V4(t_u32, 0, 0, BRAND(WRAND), BRAND(HRAND));
	mgen_room_push(gen, room, bounds, fill);
	attempts = 0;
	while (attempts < MAX_ATTEMPTS)
	{
		if (!get_exit(gen, bounds, &room))
		{
			attempts++;
			MEMCPY(room, VLL_DATA(gen->rooms->head));
		}
		else
			mgen_room_push(gen, room, bounds, fill);
	}
}
