/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:49:48 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 14:59:49 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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
	obj_normal = tuple_subtract(obj_point, point(0, 0, 0));
	world_normal = mx_multiply_tuple(transpose(s.inverse), obj_normal);
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
