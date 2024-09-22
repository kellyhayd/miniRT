/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:31:43 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/22 12:58:29 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vector(double x, double y, double z)
{
	return ((t_vector){.x = x, .y = y, .z = z, .w = 0});
}

double	magnitude(t_vector vector1)
{
	double	result;

	result = sqrt(pow(vector1.x, 2) + pow(vector1.y, 2) + pow(vector1.z, 2));
	return (result);
}

t_vector	normalize(t_vector vector1)
{
	t_vector	new;
	double		v_magnitude;

	v_magnitude = magnitude(vector1);
	new.x = vector1.x / v_magnitude;
	new.y = vector1.y / v_magnitude;
	new.z = vector1.z / v_magnitude;
	new.w = vector1.w / v_magnitude;
	return (new);
}

double	dot(t_vector vector1, t_vector vector2)
{
	return (vector1.x * vector2.x
		+ vector1.y * vector2.y
		+ vector1.z * vector2.z
		+ vector1.w * vector2.w);
}

t_tuple	cross(t_vector vector1, t_vector vector2)
{
	return (vector(vector1.y * vector2.z - vector1.z * vector2.y,
			vector1.z * vector2.x - vector1.x * vector2.z,
			vector1.x * vector2.y - vector1.y * vector2.x));
}
