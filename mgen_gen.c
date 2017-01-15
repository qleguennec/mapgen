/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:47:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/15 20:00:13 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define DEBUG 0

#define X V4X(*room)
#define Y V4Y(*room)
#define W V4W(*room)
#define H V4H(*room)

#define ARBRAND RAND(2, 256)

#define MAX_ATTEMPTS	100
#define MIN_ROOMS		(WIDTH.y / 40)

static void
	gen_room_push
	(t_gen *gen
	, t_u32_v4 *room
	, t_u32_v2 *bounds)
{
	t_u32_v2	rb;
	t_u32_v2	lu;

	rb = V4_V2(t_u32, *room, SUM2);
	lu = V2(t_u32, X, Y);
	while (NEQ2(lu, rb))
	{
		if (MAP2(lu) == MAP_NONE)
			MAP2(lu) = lu.x == X
				|| lu.y == Y
				|| lu.x == rb.x
				|| lu.y == rb.y
				? MAP_WALL : MAP_POINT;
		lu = SUM2(t_u32
			, lu
			, (lu.x == rb.x ? V2(t_i32, -W, 1) : V2(t_i32, 1, 0)));
	}
	if (MAP2(rb) == MAP_NONE)
		MAP2(rb) = MAP_WALL;
}

static bool
	gen_next_room
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

static void
	gen_exit
	(t_gen *gen
	, t_u32_v4 *prev
	, t_u32_v4 *room
	, t_u32_v2 *bounds)
{
	if (Y == V4Y(*prev) && X < V4X(*prev))
		MAP(V4X(*prev), RAND(Y + 1, MIN(Y + H, V4Y2(*prev)) - 1)) = MAP_DOOR;
	else if (X == V4X(*prev) && Y < V4Y2(*prev))
		MAP(RAND(X + 1, MIN(X + W, V4X2(*prev)) - 1), V4Y(*prev)) = MAP_DOOR;
	else if (Y == V4Y(*prev) && X > V4X(*prev))
		MAP(X, RAND(Y + 1, MIN(Y + H, V4Y2(*prev)) - 1)) = MAP_DOOR;
	else if (X == V4X(*prev) && Y > V4Y(*prev))
		MAP(RAND(X + 1, MIN(X + W, V4X2(*prev)) - 1), Y) = MAP_DOOR;
}

void
	mgen_gen
	(t_gen *gen
	, t_u32_v2 *bounds)
{
	t_u32		attempts;
	t_u32_v4	room;
	t_vll_node	*n;
	char		d;

	room = V4(t_u32, BRAND(XRAND), BRAND(YRAND), BRAND(WRAND), BRAND(HRAND));
	n = VLL_ADD(gen->rooms, room);
	attempts = 0;
	while (attempts < MAX_ATTEMPTS || gen->rooms->size < MIN_ROOMS)
	{
		if (!gen_next_room(gen, bounds, &room) && ++attempts)
			MEMCPY(room, VLL_DATA(n));
		else
			n = VLL_ADD_BACK(gen->rooms, n, room);
	}
	MAP((V4X(room) + 1), (V4Y(room) + 1)) = MAP_SPAWN;
	while (n)
	{
		gen_room_push(gen, VLL_DATA(n), bounds);
		if (n->next)
			gen_exit(gen, VLL_DATA(n->next), VLL_DATA(n), bounds);
		// TODO remove
		if (DEBUG)
		{
			print(gen->map, WIDTH.y, HEIGHT.y);
			read(0, &d, 1);
		}
		n = n->next;
	}
}
