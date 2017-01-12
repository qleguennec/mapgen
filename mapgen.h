/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapgen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 18:54:23 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/12 17:10:37 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPGEN_H
# define MAPGEN_H

# define T_U32_V2
# define T_I32_V2
# define T_U32_V4

# include "libfmt/libfmt.h"
# include "libft/libft.h"
# include "libvll/libvll.h"
# include <limits.h>
# include <math.h>
# include <stdlib.h>
# include <unistd.h>

# define MINW		5
# define MAXW		2000
# define MINH		5
# define MAXH		2000
# define MINSEED	1000
# define MAXSEED	INT_MAX

# define MAP_NONE	0
# define MAP_WALL	1
# define MAP_SPAWN	2
# define MAP_POINT	3
# define MAP_NL		4

# define XRANGE (bounds[0])
# define YRANGE (bounds[1])
# define WRANGE (bounds[2])
# define HRANGE (bounds[3])

# define MAP(a, b) (gen->map[b * XRANGE.y + a])
# define MAP2(a) (MAP((a).x, (a).y))
# define RAND2(min, max) mgen_rand(&gen->seed, min, max - 1)
# define BRAND2(b) mgen_rand(&gen->seed, (b).x, ((b).y - 1))

typedef struct		s_gen
{
	t_u32			nrooms;
	t_u32			seed;
	t_u8			*map;
	t_vll			rooms;
}					t_gen;

t_u32				mgen_rand(t_u32 *seed, t_u32 min, t_u32 max);
void				mgen_gen(t_gen *gen, t_u32_v2 *b, t_u8 *fill);
void				mgen_room_push(t_gen *gen, t_u32_v4 room, t_u32_v2 *bounds, t_u8 *fill);
void				mgen_room_rand(t_gen *gen, t_u32_v2 *b, t_u8 *fill);

#endif
