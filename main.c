/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/27 16:03:09 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/06 16:26:48 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

int		main(int argc, char **argv)
{
	t_u32	height;
	t_u32	seed;
	t_u32	width;

	if (argc != 4)
		return (ERR("usage: mapgen width height seed", 1, 0));
	if (!(STRONLY(argv[1], DIGIT)
		&& STRONLY(argv[2], DIGIT)
		&& STRONLY(argv[3], DIGIT)))
		return (ERR("arguments must contain only digits", 1, 0));
	STRTOB10(argv[1], width);
	STRTOB10(argv[2], height);
	STRTOB10(argv[3], seed);
	if (width < MINW || width > MAXW)
		return (ERR("width must be in the range [%10, %10]", 1, MINW, MAXW));
	if (height < MINW || height > MAXW)
		return (ERR("height must be in the range [%10, %10]", 1, MINH, MAXH));
	if (seed < MINSEED || seed > MAXSEED)
		return (ERR("seed must be in the range [%10, %10]", 1, MINSEED, MAXSEED));
	return (0);
}
