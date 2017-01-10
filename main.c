/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:03:09 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/10 16:44:38 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define PHI 1.618

#define BOUND (i == 0 || j == 0 || i == width - 1 || j == height - 1)
#define VALUE(m, i, j, x) (m)[j * width + i] = x
#define NROOMS(a) (t_u32)(sqrt(a) * PHI)

static void
	init
	(t_u32 **map
	 , t_u32 width
	 , t_u32 height
	 , t_u64 area)
{
	size_t	i;
	size_t	j;

	MALLOC_N(*map, area);
	i = -1;
	while (++i < height)
	{
		j = -1;
		while (++j < width)
			VALUE(*map, i, j, BOUND ? MAP_WALL : MAP_NONE);
	}
}

static void
	gen
	(t_u32 width
	 , t_u32 height
	 , t_u32 seed)
{
	size_t	i;
	t_gen	gen;
	t_u32	nl;
	t_u32_v2	v2;

	gen.xbound.x = 1;
	gen.xbound.y = width - 2;
	gen.ybound.x = 1;
	gen.ybound.y = height - 2;
	gen.seed = seed;
	gen.area = width * height;
	init(&gen.map, width, height, gen.area + height);
	gen.nrooms = NROOMS(gen.area);
	gen.rooms = mgen_get_npoints(gen.nrooms, gen.xbound, gen.ybound, &gen.seed);
	i = -1;
	t_u32_v4 tmp;
	while (++i < gen.nrooms)
	{
		VALUE(gen.map, gen.rooms[i].x, gen.rooms[i].y, MAP_POINT);
		tmp = mgen_get_area(gen.map, width, height, gen.rooms[i]);
		v2 = gen.rooms[i];
		ECHO2_U32(v2);
		ECHO4_U32(tmp);
	}
	i = -1;
	nl = MAP_NL;
	while (++i < height)
	{
		PRINT("%c\t", i);
		write(1, gen.map + i * height, width * 4);
		write(1, &nl, 1);
	}
}

int
	main
	(int argc
	, char **argv)
{
	t_u64	height;
	t_u64	seed;
	t_u64	width;

	if (argc != 4)
		return (ERR("usage: mapgen width height seed", 1, 0));
	if (!(STRONLY(argv[1], DIGIT)
		&& STRONLY(argv[2], DIGIT) && STRONLY(argv[3], DIGIT)))
		return (ERR("arguments must contain only digits", 1, 0));
	width = 0;
	height = 0;
	seed = 0;
	STRTOB10(argv[1], width);
	STRTOB10(argv[2], height);
	STRTOB10(argv[3], seed);
	if (width < MINW || width > MAXW)
		return (ERR("width must be in the range [%a, %a]", 1, MINW, MAXW));
	if (height < MINW || height > MAXW)
		return (ERR("height must be in the range [%a, %a]", 1, MINH, MAXH));
	if (seed < MINSEED || seed > MAXSEED)
		return (ERR("seed must be in the range [%a, %a]", 1, MINSEED, MAXSEED));
	srand(seed);
	gen((t_u32)width, (t_u32)height, (t_u32)seed);
	return (0);
}
