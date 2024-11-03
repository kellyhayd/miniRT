/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:58:17 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:54:53 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "shapes_bonus.h"
#include "ray_bonus.h"

t_shape	cylinder(void)
{
	t_shape	new_cylinder;

	new_cylinder = new_shape();
	new_cylinder.shape_type = CYLINDER;
	new_cylinder.cylinder_shape.origin = point(0, 0, 0);
	new_cylinder.cylinder_shape.radius = 1;
	new_cylinder.cylinder_shape.closed = false;
	new_cylinder.cylinder_shape.minimum = -INFINITY;
	new_cylinder.cylinder_shape.maximum = INFINITY;
	return (new_cylinder);
}

t_vector	normal_at_cylinder(t_shape s, t_point obj_point)
{
	double		dist;
	t_vector	normal;

	dist = pow(obj_point.x, 2) + pow(obj_point.z, 2);
	if (dist < 1 && obj_point.y >= s.cylinder_shape.maximum - EPSILON)
		normal = vector(0, 1, 0);
	else if (dist < 1 && obj_point.y <= s.cylinder_shape.minimum + EPSILON)
		normal = vector(0, -1, 0);
	else
		normal = vector(obj_point.x, 0, obj_point.z);
	return (normal);
}
