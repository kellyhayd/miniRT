/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:52:47 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 22:22:38 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Represents an intersection between a ray and a shape.
 *
 * This function creates an intersection record given a time `t` and a shape `s`
 *
 * @param t The time at which the intersection occurs.
 * @param s The shape that is intersected.
 * @return A `t_hit` structure representing the intersection.
 */
t_hit	intersection(double t, t_shape s)
{
	return ((t_hit){.t = t, .object = s, .next = NULL});
}

void	local_intersect(t_hit **hit_list, t_shape s, t_ray r)
{
	if (s.shape_type == SPHERE)
		intersect_sphere(hit_list, s, r);
	else if (s.shape_type == PLANE)
		intersect_plane(hit_list, s, r);
}

/**
 * @brief Intersects a ray with a shape and updates the hit list with
 * intersection points.
 *
 * This function calculates the intersection points between a given ray and a
 * shape, and updates the provided hit list with the results.
 *
 * @param hit_list A pointer to the list of hit points to be updated.
 * @param s The shape to be intersected with the ray.
 * @param r The ray to be intersected with the shape.
 */
void	intersect(t_hit **hit_list, t_shape s, t_ray r)
{
	t_ray	new_ray;

	new_ray = ray_transform(r, s.inverse);
	local_intersect(hit_list, s, new_ray);
	// intersect_sphere(hit_list, s, new_ray);
}

/**
 * @brief Processes a list of hit records and returns the most relevant hit.
 *
 * This function takes a list of hit records and determines the most relevant
 * hit based on the criteria defined within the function. The returned hit
 * record can be used for further processing in ray tracing or collision
 * detection algorithms.
 *
 * @param hit_list A pointer to the list of hit records to be processed.
 * @return A pointer to the most relevant hit record from the list.
 */
t_hit	*hit(t_hit *hit_list)
{
	t_hit	*aux;

	aux = hit_list;
	while (aux && aux->t < 0)
		aux = aux->next;
	return (aux);
}
