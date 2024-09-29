/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:04:14 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/29 17:31:39 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_shadowed(t_world w, t_point position)
{
	t_vector	v;
	t_hit		*hit_list;
	t_hit		*h;
	double		distance;

	v = tuple_subtract(w.light->position, position);
	distance = magnitude(v);
	hit_list = intersect_world(w, ray(position, normalize(v)));
	h = hit(hit_list);
	if (h && h->t < distance)
		return (true);
	return (false);
}
