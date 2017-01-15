/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mgen_v4_util.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: qle-guen <qle-guen@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2017/01/14 23:05:51 by qle-guen          #+#    #+#             */
/*   Updated: 2017/01/15 00:34:14 by qle-guen         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "mapgen.h"

bool
	mgen_v4_is_free
	(t_vll *l
	, t_u32_v4 v4)
/*
** checks if square v4 is free for writing
** returns false if v4 intersects with somme vector in l
** returns true otherwise
*/
{
	t_u32_v4	w;
	t_vll_node	*n;

	n = l->head;
	while (n)
	{
		MEMCPY(w, VLL_DATA(n));
		if (V4X(w) >= V4X(v4)
			&& V4X(w) < V4X(v4) + V4W(v4)
			&& V4Y(w) >= V4X(v4)
			&& V4Y(w) < V4Y(v4) + V4H(v4))
			return (false);
		if (V4X(v4) >= V4X(w)
			&& V4X(v4) < V4X(w) + V4W(w)
			&& V4Y(v4) >= V4X(w)
			&& V4Y(v4) < V4Y(w) + V4H(w))
			return (false);
		n = n->next;
	}
	return (true);
}

t_u32
	mgen_v4_max
	(t_u32_v4 v4)
/*
** determines the maximum value of the vector
*/
{
	if (v4.a > v4.b && v4.a > v4.c && v4.a > v4.d)
		return (1);
	if (v4.b > v4.a && v4.b > v4.c && v4.b > v4.d)
		return (2);
	if (v4.c > v4.a && v4.c > v4.b && v4.c > v4.d)
		return (4);
	if (v4.d > v4.a && v4.d > v4.b && v4.d > v4.c)
		return (8);
	return (0);
}
