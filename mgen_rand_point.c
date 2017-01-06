/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_rand_point.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 18:48:42 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/06 19:46:48 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

t_u32_v2
	mgen_rand_point
	(t_u32_v2 xbound
	 , t_u32_v2 ybound
	 , t_u32 *seed)
{
	t_u32_v2	v2;

	v2.x = (t_u32)(mgen_rand1(seed) * xbound.y) + xbound.x;
	v2.y = (t_u32)(mgen_rand1(seed) * ybound.y) + ybound.x;
	ECHO("got %10 %10", v2.x, v2.y);
	return (v2);
}
