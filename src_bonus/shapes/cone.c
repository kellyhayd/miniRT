/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:56:37 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/31 08:54:45 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "shapes.h"
#include "ray.h"

t_shape	cone(void)
{
	t_shape	new_cone;

	new_cone = new_shape();
	new_cone.shape_type = CONE;
	new_cone.cone_shape.origin = point(0, 0, 0);
	new_cone.cone_shape.radius = 1;
	new_cone.cone_shape.minimum = -INFINITY;
	new_cone.cone_shape.maximum = INFINITY;
	new_cone.cone_shape.closed = false;
	return (new_cone);
}

t_vector	normal_at_cone(t_shape s, t_point obj_point)
{
	double		y;
	double		dist;
	double		max_radius;
	double		min_radius;
	t_vector	normal;

	dist = pow(obj_point.x, 2) + pow(obj_point.z, 2);
	max_radius = pow(s.cone_shape.maximum, 2);
	min_radius = pow(s.cone_shape.minimum, 2);
	if (dist < max_radius
		&& obj_point.y >= s.cylinder_shape.maximum - EPSILON)
		normal = vector(0, 1, 0);
	else if (dist < min_radius
		&& obj_point.y <= s.cylinder_shape.minimum + EPSILON)
		normal = vector(0, -1, 0);
	else
	{
		y = sqrt(dist);
		if (obj_point.y > 0)
			y = -y;
		normal = vector(obj_point.x, y, obj_point.z);
	}
	return (normal);
}
