/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 20:39:46 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/14 19:37:16 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_ray	ray(t_point origin, t_vector direction)
{
	return ((t_ray){.origin = origin, .direction = direction});
}

t_point	position(t_ray r, double t)
{
	return (tuple_add(tuple_multiply(r.direction, t), r.origin));
}

t_ray	ray_transform(t_ray ray, t_matrix matrix)
{
	t_ray	new_ray;

	new_ray.origin = matrix_multiply_tuple(matrix, ray.origin);
	new_ray.direction = matrix_multiply_tuple(matrix, ray.direction);
	return (new_ray);
}
