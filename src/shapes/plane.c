/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   plane.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 08:54:35 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/05 08:54:54 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	plane(void)
{
	t_shape	new_plane;

	new_plane = new_shape();
	new_plane.shape_type = PLANE;
	new_plane.plane_shape.origin = point(0, 0, 0);
	return (new_plane);
}

void	intersect_plane(t_hit **hit_list, t_shape s, t_ray r)
{
	double	t;

	if (fabs(r.direction.y) < EPSILON)
		return ;
	t = -r.origin.y / r.direction.y;
	if (fabs(t) > EPSILON)
		add_intersection(hit_list, intersection(t, s));
}

t_vector	normal_at_plane(t_shape plane, t_point obj_point)
{
	(void) plane;
	(void) obj_point;
	return (vector(0, 1, 0));
}
