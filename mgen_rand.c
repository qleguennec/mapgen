/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_rand.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/12/07 15:45:57 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/11 01:00:14 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

#define MODULUS		2147483647
#define MULTIPLIER	48271

t_u32
	mgen_rand
	(t_u32 *seed
	 , t_u32_v2 bound)
{
	const static t_u32		q = MODULUS / MULTIPLIER;
	const static t_u32		r = MODULUS % MULTIPLIER;
	t_i32					t;

	t = MULTIPLIER * (*seed % q) - r * (*seed / q);
	*seed = t + ((t < 0) * MODULUS);
	return (((float)*seed / MODULUS) * bound.y + bound.x);
}
