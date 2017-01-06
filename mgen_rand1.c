/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_rand1.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:45:57 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/06 19:41:03 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define MODULUS		2147483647
#define MULTIPLIER	48271

float
	mgen_rand1
	(t_u32 *seed)
{
	const static t_u32		q = MODULUS / MULTIPLIER;
	const static t_u32		r = MODULUS % MULTIPLIER;
	t_i32					t;

	t = MULTIPLIER * (*seed % q) - r * (*seed / q);
	*seed = t + ((t < 0) * MODULUS);
	return ((float)*seed / MODULUS);
}
