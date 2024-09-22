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
	double		a;
	double		b;
	double		c;

	sphere_to_ray = tuple_subtract(r.origin, s.sphere_shape.origin);
	a = dot(r.direction, r.direction);
	b = 2 * dot(r.direction, sphere_to_ray);
	c = dot(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return ;
	add_intersection(hit_list,
		intersection((-b - sqrt(discriminant)) / (2 * a), s));
	add_intersection(hit_list,
		intersection((-b + sqrt(discriminant)) / (2 * a), s));
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
