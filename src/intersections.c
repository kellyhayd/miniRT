/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:52:47 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/07 19:53:17 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	intersect(t_sphere s, t_ray r)
{
	t_vector	sphere_to_ray;
	double		discriminant;
	t_hit		x;
	double		a;
	double		b;
	double		c;

	sphere_to_ray = tuple_subtract(r.origin, s.origin);
	a = vector_dot_product(r.direction, r.direction);
	b = 2 * vector_dot_product(r.direction, sphere_to_ray);
	c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - 4 * a * c;
	if (discriminant < 0)
		return ((t_hit){0});
	x.t[0] = (-b - sqrt(discriminant)) / (2 * a);
	x.t[1] = (-b + sqrt(discriminant)) / (2 * a);
	x.count = 2;
	return (x);
}

t_hit	
