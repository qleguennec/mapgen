/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_get_npoints.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/06 19:07:19 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/11 01:02:03 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

t_u32_v2
	*mgen_get_npoints
	(t_u32 n
	 , t_u32_v2 xbound
	 , t_u32_v2 ybound
	 , t_u32 *seed)
{
	t_u32		i;
	t_u32_v2	*points;

	i = 0;
	MALLOC_N(points, n);
	while (i < n)
		points[i++] = RAND2(seed, xbound, ybound);
	return (points);
}
