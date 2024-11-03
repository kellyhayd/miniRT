/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shadows_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 13:04:14 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:50:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_bonus.h"

bool	is_shadowed(t_world w, t_point position, t_light *light)
{
	t_vector	v;
	t_hit		*hit_list;
	t_hit		*h;
	double		distance;
	int			result;

	v = tuple_subtract(light->position, position);
	distance = magnitude(v);
	hit_list = intersect_world(w, ray(position, normalize(v)));
	h = hit(hit_list);
	if (h && (int)(h->t * 100000) < (int)(distance * 100000))
		result = true;
	else
		result = false;
	hit_clear_list(&hit_list);
	return (result);
}
