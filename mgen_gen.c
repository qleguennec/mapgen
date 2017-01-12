/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_gen.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/12 15:47:33 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/12 18:03:42 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define X V4X(room)
#define Y V4Y(room)
#define W V4W(room)
#define H V4H(room)

static t_u32_v2
	get_exit
	(t_gen *gen
	, t_u32_v4 room)
{
	t_u32	e;

	e = RAND2(0, 2 * (W + H));
	PUT("e\t");
	ECHO_U32(e);
	if (e >= X && e < X + W)
		return (V2(t_u32, e + X, Y));
	e -= W;
	if (e >= Y && e < Y + H)
		return (V2(t_u32, X, e + Y));
	e -= H;
	if (e >= X && e < X + W)
		return (V2(t_u32, e + X, Y));
	e -= W;
	return (V2(t_u32, X, e + Y));
}

void
	mgen_gen
	(t_gen *gen
	, t_u32_v2 *bounds
	, t_u8 *fill)
{
	t_u32_v4	room;

	X = 0;
	Y = 0;
	W = BRAND2(WRANGE);
	H = BRAND2(HRANGE);
	mgen_room_push(gen, room, bounds, fill);
	ECHO2_U32(get_exit(gen, room));
}
