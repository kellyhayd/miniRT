/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:49:48 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/29 22:10:30 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	reflected_color(t_world world, t_comps comps, int depth)
{
	t_ray	reflective_ray;
	t_color	reflective_color;

	if (comps.object.material.reflective == 0 || depth < 1)
		return (color(0, 0, 0));
	reflective_ray = ray(comps.over_point, comps.reflectv);
	reflective_color = color_at(world, reflective_ray, depth - 1);
	return (color_multiply(reflective_color, comps.object.material.reflective));
}

t_vector	local_normal_at(t_shape s, t_point obj_point)
{
	t_vector	normal;

	if (s.shape_type == SPHERE)
		normal = normal_at_sphere(s, obj_point);
	else if (s.shape_type == PLANE)
		normal = normal_at_plane(s, obj_point);
	else if (s.shape_type == CYLINDER)
		normal = normal_at_cylinder(s, obj_point);
	else if (s.shape_type == CONE)
		normal = normal_at_cone(s, obj_point);
	else
		normal = (t_vector){0, 0, 0, 0};
	return (normal);
}

/**
 * Computes the normal vector at a given point on the surface of a shape.
 *
 * @param s The shape for which the normal is being calculated.
 * @param world_point The point on the shape's surface in world coordinates.
 * @return The normal vector at the specified point on the shape's surface.
 */
t_vector	normal_at(t_shape s, t_point world_point)
{
	t_point		obj_point;
	t_point		obj_normal;
	t_vector	world_normal;

	obj_point = mx_multiply_tuple(s.inverse, world_point);
	obj_normal = local_normal_at(s, obj_point);
	world_normal = mx_multiply_tuple(s.transposed_inverse, obj_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

/**
 * Reflects a vector around a given normal vector.
 *
 * @param in The input vector to be reflected.
 * @param normal The normal vector around which the input vector is reflected.
 * @return The reflected vector.
 */
t_vector	reflect(t_vector in, t_vector normal)
{
	return (tuple_subtract(in, tuple_multiply(normal, 2 * dot(in, normal))));
}
