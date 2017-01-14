/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:03:09 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/14 18:42:15 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define PHI 1.618

#define BOUND (i == 0 || j == 0 || i == width - 1 || j == height - 1)
#define DEBUG 1
#define ROOM_GROW_FACTOR 3
#define VALUE(m, i, j, x) (m)[j * width + i] = x
#define XMAX (width / 3)
#define YMAX (height / 3)
#define XMIN (width / 10)
#define YMIN (height / 10)

static void
	print
	(t_u8 *map
	, t_u32 width
	, t_u32 height
	, t_u8 nl)
{
	size_t		i;

	i = 0;
	while (i < height)
	{
		if (DEBUG)
			PRINT("%c\t", i);
		write(1, map + i * width, width);
		write(1, &nl, 1);
		i++;
	}
}

static void
	deinit
	(t_gen *gen)
{
	vll_free(gen->rooms);
	free(gen->map);
}

static void
	gen
	(t_u32 width
	, t_u32 height
	, t_u32 seed)
{
	static t_u8		fill[MAP_NL + 1] = "ows -\n";
	t_gen			gen;
	t_u32_v2		bounds[6];
	t_u64			area;

	bounds[0] = V2(t_u32, 0, width);
	bounds[1] = V2(t_u32, 0, height);
	bounds[2] = V2(t_u32, 0, width - XMAX);
	bounds[3] = V2(t_u32, 0, height - YMAX);
	bounds[4] = V2(t_u32, YMIN, XMAX);
	bounds[5] = V2(t_u32, YMIN, YMAX);
	gen.seed = seed;
	area = width * height;
	MALLOC_N(gen.map, area);
	ft_memset(gen.map, fill[MAP_NONE], area);
	gen.rooms = vll_new();
	mgen_gen(&gen, bounds, fill);
	print(gen.map, width, height, fill[MAP_NL]);
	deinit(&gen);
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
