/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:03:09 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/11 18:12:06 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define PHI 1.618

#define BOUND (i == 0 || j == 0 || i == width - 1 || j == height - 1)
#define VALUE(m, i, j, x) (m)[j * width + i] = x
#define NROOMS(a) (t_u32)(sqrt(a) / PHI)

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
		write(1, map + i * height, width);
		write(1, &nl, 1);
		i++;
	}
}

static void
	gen
	(t_u32 width
	 , t_u32 height
	 , t_u32 seed)
{
	const static t_u8		fill[MAP_NL + 1] = "ows \n";
	size_t					i;
	t_gen					gen;

	gen.xbound.x = 0;
	gen.xbound.y = width;
	gen.ybound.x = 0;
	gen.ybound.y = height;
	gen.seed = seed;
	gen.area = width * height;
	MALLOC_N(gen.map, gen.area);
	ft_memset(gen.map, fill[MAP_NONE], gen.area);
	//gen.nrooms = NROOMS(gen.area);
	gen.nrooms = 1;
	gen.rooms = mgen_get_npoints(gen.nrooms, gen.xbound, gen.ybound, &gen.seed);
	i = -1;
	while (++i < gen.nrooms)
		mgen_grow(&gen, gen.rooms[i], V4(t_u32, 4, 4, 4, 4), fill);
	print((void *)gen.map, width, height, fill[MAP_NL]);
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
