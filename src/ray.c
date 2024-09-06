/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:39:46 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/05 22:23:18 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray(t_point origin, t_vector direction)
{
	return ((t_ray) {.origin = origin, .direction = direction});
}

t_point	position(t_ray r, double t)
{
	return (tuple_add(tuple_multiply(r.direction, t), r.origin));
}

t_hit	intersect(t_sphere s, t_ray r)
{
	
}

// int intersect(Sphere sphere, Ray ray, float *t1, float *t2) {
//     Vector sphere_to_ray;
//     sphere_to_ray.x = ray.origin.x - sphere.origin.x;
//     sphere_to_ray.y = ray.origin.y - sphere.origin.y;
//     sphere_to_ray.z = ray.origin.z - sphere.origin.z;
// 
//     float a = ray.direction.x * ray.direction.x + 
//               ray.direction.y * ray.direction.y + 
//               ray.direction.z * ray.direction.z;
//     float b = 2 * (ray.direction.x * sphere_to_ray.x + 
//                    ray.direction.y * sphere_to_ray.y + 
//                    ray.direction.z * sphere_to_ray.z);
//     float c = (sphere_to_ray.x * sphere_to_ray.x + 
//                sphere_to_ray.y * sphere_to_ray.y + 
//                sphere_to_ray.z * sphere_to_ray.z) - 
//                sphere.radius * sphere.radius;
// 
//     float discriminant = b * b - 4 * a * c;
// 
//     if (discriminant < 0) {
//         return 0;  // Sem interseção
//     }
// 
//     *t1 = (-b - sqrt(discriminant)) / (2 * a);
//     *t2 = (-b + sqrt(discriminant)) / (2 * a);
//     return 1;  // Há interseções
// }
