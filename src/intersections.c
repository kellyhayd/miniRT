/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:52:47 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/12 00:04:17 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_hit	intersection(double t, t_shape s)
{
	return ((t_hit){.t = t, .object = s, .next = NULL});
}



// TIRAR ESSA FUNÇÃO DAQUI
////////////////////////////////////////////////////////////////////////////////////////
void	add_intersection(t_hit **hit_list, t_hit isect)
{
	t_hit	*new;
	t_hit	*aux;
	t_hit	*prev;

	new = malloc(sizeof(t_hit));
	*new = isect;

	prev = NULL;
	aux = *hit_list;
	while (aux && aux->t < isect.t)
	{
		prev = aux;
		aux = aux->next;
	}

	if (prev == NULL)
	{
		new->next = *hit_list;
		*hit_list = new;
		return ;
	}

	prev->next = new;
	new->next = aux;
}

int	intersection_count(t_hit *hit_list)
{
	int		count;
	t_hit	*aux;

	count = 0;
	aux = hit_list;
	while (aux)
	{
		aux = aux->next;
		count++;
	}
	return (count);
}

////////////////////////////////////////////////////////////////////////////////////////


void	intersect_sphere(t_hit **hit_list, t_shape s, t_ray r)
{
	t_vector	sphere_to_ray;
	double		discriminant;
	double		a;
	double		b;
	double		c;

	sphere_to_ray = tuple_subtract(r.origin, s.sphere_shape.origin);
	a = vector_dot_product(r.direction, r.direction);
	b = 2 * vector_dot_product(r.direction, sphere_to_ray);
	c = vector_dot_product(sphere_to_ray, sphere_to_ray) - 1;
	discriminant = pow(b, 2) - 4 * a * c;

	if (discriminant < 0)
		return ;

	add_intersection(hit_list, intersection((-b - sqrt(discriminant)) / (2 * a), s));
	add_intersection(hit_list, intersection((-b + sqrt(discriminant)) / (2 * a), s));
}

t_hit	*intersect(t_shape s, t_ray r)
{
	t_hit		*x;

	x = NULL;
	intersect_sphere(&x, s, r);

	return (x);
}
