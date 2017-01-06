/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mapgen.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/30 18:54:23 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/06 19:46:16 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MAPGEN_H
# define MAPGEN_H

# include "libfmt/libfmt.h"
# include "libft/libft.h"
# include <limits.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>
# include <stdio.h>

# define MINW		0
# define MAXW		2000
# define MINH		0
# define MAXH		2000
# define MINSEED	1000
# define MAXSEED	INT_MAX

# define MAP_NONE	'x'
# define MAP_WALL	'w'
# define MAP_POINT	'o'
# define MAP_NL		'\n'

typedef struct		s_u32_v2
{
	t_u32			x;
	t_u32			y;
}					t_u32_v2;

typedef struct		s_gen
{
	size_t			area;
	t_u32			*map;
	t_u32			height;
	t_u32			nrooms;
	t_u32			seed;
	t_u32_v2		xbound;
	t_u32_v2		ybound;
	t_u32_v2		*rooms;
}					t_gen;

float				mgen_rand1(t_u32 *seed);
t_u32_v2			*mgen_get_npoints(t_u32 n, t_u32_v2 xbound, t_u32_v2 ybound, t_u32 *seed);
t_u32_v2			mgen_rand_point(t_u32_v2 xbound, t_u32_v2 ybound, t_u32 *seed);

#endif
