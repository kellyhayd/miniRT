/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersections.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/07 19:52:47 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/14 12:12:36 by danbarbo         ###   ########.fr       */
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

void	hit_clear_list(t_hit **hit_list)
{
	if (hit_list && *hit_list)
	{
		hit_clear_list(&((*hit_list)->next));
		free(*hit_list);
		*hit_list = NULL;
	}
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

void	intersect(t_hit **hit_list, t_shape s, t_ray r)
{
	t_ray	new_ray;

	new_ray = ray_transform(r, matrix_inverse(s.transform));
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
