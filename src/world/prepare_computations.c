/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prepare_computations.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:41:59 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/29 21:42:00 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_comps	prepare_computations(t_hit hit, t_ray ray, t_hit *hit_list)
{
	t_comps	comps;

	comps.t = hit.t;
	comps.object = hit.object;
	comps.point = position(ray, comps.t);
	comps.inside = false;
	comps.sight.eye = tuple_negate(ray.direction);
	comps.sight.normal = normal_at(comps.object, comps.point);
	comps.sight.in_shadow = false;
	if (dot(comps.sight.normal, comps.sight.eye) < 0)
	{
		comps.inside = true;
		comps.sight.normal = tuple_negate(comps.sight.normal);
	}
	comps.reflectv = reflect(ray.direction, comps.sight.normal);
	comps.over_point = tuple_add(comps.point,
			tuple_multiply(comps.sight.normal, EPSILON));
	comps.under_point = tuple_subtract(comps.point,
			tuple_multiply(comps.sight.normal, EPSILON));
	calculate_refractive_indexes(&comps, hit_list);
	return (comps);
}
