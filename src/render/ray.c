/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:39:46 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/31 08:53:46 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "ray.h"

/**
 * @brief Creates a ray with a given origin and direction.
 *
 * This function initializes a ray structure with the specified origin point
 * and direction vector. The ray can be used for various ray tracing operations
 * such as intersection tests with objects in a scene.
 *
 * @param origin The starting point of the ray.
 * @param direction The direction vector of the ray.
 * @return A ray structure initialized with the given origin and direction.
 */
t_ray	ray(t_point origin, t_vector direction)
{
	return ((t_ray){.origin = origin, .direction = direction});
}

/**
 * Computes the position of a point along a ray at a given parameter t.
 *
 * @param r The ray for which the position is to be calculated.
 * @param t The parameter along the ray at which the position is to be computed.
 * @return The position of the point along the ray at parameter t.
 */
t_point	position(t_ray r, double t)
{
	return (tuple_add(tuple_multiply(r.direction, t), r.origin));
}

/**
 * @brief Transforms a given ray using a transformation matrix.
 *
 * This function applies a transformation matrix to a ray, modifying its
 * origin and direction according to the matrix.
 *
 * @param ray The ray to be transformed.
 * @param matrix The transformation matrix to apply to the ray.
 * @return The transformed ray.
 */
t_ray	ray_transform(t_ray ray, t_matrix matrix)
{
	t_ray	new_ray;

	new_ray.origin = mx_multiply_tuple(matrix, ray.origin);
	new_ray.direction = mx_multiply_tuple(matrix, ray.direction);
	return (new_ray);
}
