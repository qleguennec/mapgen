/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:47:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/14 18:58:45 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define X V4X(room)
#define Y V4Y(room)
#define W V4W(room)
#define H V4H(room)

#define MAX_ATTEMPTS 10

static t_u32_v4
	get_exit
	(t_gen *gen
	, t_u32_v2 *bounds
	, t_u32_v4 room
	, t_u32 direction)
{
	if (direction == 0)
		return (V4(t_u32, X + W, RAND(Y, Y + H - 2), BRAND(WRAND), BRAND(HRAND)));
	if (direction == 1)
		return (V4(t_u32, RAND(X, X + W - 2), Y + H, BRAND(WRAND), BRAND(HRAND)));
	return (V4(t_u32, -1, -1, -1, -1));
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
		if (X + W >= WIDTH.y && Y + H >= HEIGHT.y)
		{
			attempts++;
			MEMCPY(room, VLL_DATA(gen->rooms->head));
		}
		else
			mgen_room_push(gen, room, bounds, fill);
		room = get_exit(gen, bounds, room, RAND(0, 2));
	}
}
