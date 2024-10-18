/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:28:43 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/05 08:46:17 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Creates and returns a new sphere shape.
 *
 * This function initializes a new sphere shape and returns it.
 *
 * @return A new sphere shape.
 */
t_shape	sphere(void)
{
	t_shape	new_sphere;

	new_sphere = new_shape();
	new_sphere.shape_type = SPHERE;
	new_sphere.sphere_shape.origin = point(0, 0, 0);
	new_sphere.sphere_shape.radius = 1;
	return (new_sphere);
}

/**
 * @brief Intersects a ray with a sphere and updates the hit list with
 * intersection points.
 *
 * This function calculates the intersection points between a given ray and a
 * sphere. If intersections are found, they are added to the hit list.
 *
 * @param hit_list A pointer to the list of hit points to be updated with
 * intersection points.
 * @param s The sphere shape to be intersected with the ray.
 * @param r The ray to be intersected with the sphere.
 */
void	intersect_sphere(t_hit **hit_list, t_shape s, t_ray r)
{
	t_vector	sphere_to_ray;
	double		discriminant;
	double		coefficient[3];
	double		two_times_a;
	double		square_root;

	sphere_to_ray = tuple_subtract(r.origin, s.sphere_shape.origin);
	coefficient[0] = dot(r.direction, r.direction);
	coefficient[1] = 2 * dot(r.direction, sphere_to_ray);
	coefficient[2] = dot(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(coefficient[1], 2)
		- 4 * coefficient[0]
		* coefficient[2];
	if (discriminant < 0)
		return ;
	two_times_a = 2 * coefficient[0];
	square_root = sqrt(discriminant);
	add_intersection(hit_list,
		intersection((-coefficient[1] - square_root) / (two_times_a), s)
		);
	add_intersection(hit_list,
		intersection((-coefficient[1] + square_root) / (two_times_a), s)
		);
}

t_vector	normal_at_sphere(t_shape sphere, t_point obj_point)
{
	(void) sphere;
	return (tuple_subtract(obj_point, point(0, 0, 0)));
}
