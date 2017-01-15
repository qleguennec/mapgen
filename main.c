/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:03:09 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/15 23:31:35 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define BOUND (i == 0 || j == 0 || i == width - 1 || j == height - 1)
#define DEBUG 0
#define VALUE(m, i, j, x) (m)[j * width + i] = x

static void
	print
	(t_u8 *map
	, t_u32 width
	, t_u32 height)
{
	size_t		i;
	char		nl;

	nl = MAP_NL;
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
	(t_gen *gen
	, t_u8 *map)
{
	vll_free(gen->rooms);
	free(map);
}

static void
	gen
	(t_u32 width
	, t_u32 height
	, t_u32 seed)
{
	t_gen	gen;
	t_u64	area;
	t_u8	*map;

	gen.seed = seed;
	gen.width = width;
	gen.height = height;
	area = width * height;
	MALLOC_N(map, area);
	ft_memset(map, MAP_NONE, area);
	gen.rooms = vll_new();
	mgen_gen(&gen);
	mgen_map_draw(&gen, map);
	print(map, width, height);
	deinit(&gen, map);
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
	if (width < MAP_MINW || width > MAP_MAXW)
		return (ERR("width must be in the range [%a, %a]", 1, MAP_MINW, MAP_MAXW));
	if (height < MAP_MINH || height > MAP_MAXH)
		return (ERR("height must be in the range [%a, %a]", 1, MAP_MINH, MAP_MAXH));
	if (seed < MINSEED || seed > MAXSEED)
		return (ERR("seed must be in the range [%a, %a]", 1, MINSEED, MAXSEED));
	srand(seed);
	gen((t_u32)width, (t_u32)height, (t_u32)seed);
	return (0);
}
