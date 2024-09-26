/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:52:47 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/22 12:56:00 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	intersection(double t, t_shape s)
{
	return ((t_hit){.t = t, .object = s, .next = NULL});
}

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
		intersection((-coefficient[1] - square_root) / (two_times_a),s)
	);
	add_intersection(hit_list,
		intersection((-coefficient[1] + square_root) / (two_times_a), s)
	);
}

void	intersect(t_hit **hit_list, t_shape s, t_ray r)
{
	t_ray	new_ray;

	new_ray = ray_transform(r, s.inverse);
	intersect_sphere(hit_list, s, new_ray);
}

t_hit	*hit(t_hit *hit_list)
{
	t_hit	*aux;

	aux = hit_list;
	while (aux && aux->t < 0)
		aux = aux->next;
	return (aux);
}
