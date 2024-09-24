/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   reflection.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:49:48 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/23 20:39:10 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	normal_at(t_shape s, t_point world_point)
{
	t_point		obj_point;
	t_point		obj_normal;
	t_vector	world_normal;

	obj_point = mx_multiply_tuple(inverse(s.transform), world_point);
	obj_normal = tuple_subtract(obj_point, point(0, 0, 0));
	world_normal = mx_multiply_tuple(transpose(inverse(s.transform)), obj_normal);
	world_normal.w = 0;
	return (normalize(world_normal));
}

t_vector	reflect(t_vector in, t_vector normal)
{
	return (tuple_subtract(in, tuple_multiply(normal, 2 * dot(in, normal))));
}
