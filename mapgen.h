/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapgen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 18:54:23 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/11 18:09:37 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPGEN_H
# define MAPGEN_H

# define T_U32_V2
# define T_I32_V2
# define T_U32_V4

# include "libfmt/libfmt.h"
# include "libft/libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

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

# define MAP(a, b) (gen->map[b * gen->xbound.y + a])
# define MAP2(a) (MAP((a).x, (a).y))

# define RAND2(s, b1, b2) V2(t_u32, mgen_rand(s, b1), mgen_rand(s, b2))

typedef struct		s_gen
{
	size_t			area;
	t_u8			*map;
	t_u32			nrooms;
	t_u32			seed;
	t_u32_v2		xbound;
	t_u32_v2		ybound;
	t_u32_v2		*rooms;
}					t_gen;

t_u32				mgen_rand(t_u32 *seed, t_u32_v2 bound);
t_u32_v2			*mgen_get_npoints(t_u32 n, t_u32_v2 xbound, t_u32_v2 ybound, t_u32 *seed);
t_u32_v4			mgen_get_area(t_gen *gen, t_u32_v2 v2, t_u8 c);
t_u32_v4			mgen_grow(t_gen *gen, t_u32_v2 v2, t_u32_v4 area, const t_u8 *fill);
void				mgen_set_area(t_gen *gen, t_u32_v2 v2, t_u32_v4 area, const t_u8 *fill);
void				mgen_walls(t_gen *gen, t_u32_v2 v2, t_u32_v4 area, const t_u8 *fill);

#endif
