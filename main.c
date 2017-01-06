/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:03:09 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/06 18:39:07 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define BOUND (i == 0 || j == o || i == width - 1 || j == height - 1 + o)
#define VALUE(m, x) (m)[i * width + j] = x

static void
	init
	(t_u32 **map
	 , t_u32 width
	 , t_u32 height
	 , t_u64 area)
{
	size_t	i;
	size_t	j;
	size_t	o;

	MALLOC_N(*map, area);
	i = -1;
	j = -1;
	o = 0;
	while (++i < height)
	{
		while (++j < width + o)
			VALUE(*map, BOUND ? MAP_WALL : MAP_NONE);
		VALUE(*map, MAP_NL);
		j = o++;
	}
	VALUE(*map, MAP_NL);
}

static void
	gen
	(t_u32 width
	 , t_u32 height
	 , t_u32 seed)
{
	size_t	area;
	t_u32	*map;

	(void)seed;
	area = (width + 1) * height;
	init(&map, width, height, area);
	write(1, map, area * 4);
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
		return (ERR("width must be in the range [%10, %10]", 1, MINW, MAXW));
	if (height < MINW || height > MAXW)
		return (ERR("height must be in the range [%10, %10]", 1, MINH, MAXH));
	if (seed < MINSEED || seed > MAXSEED)
		return (ERR("seed must be in the range [%10, %10]", 1, MINSEED, MAXSEED));
	srand(seed);
	gen((t_u32)width, (t_u32)height, (t_u32)seed);
	return (0);
}
