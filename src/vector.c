/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:31:43 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/21 20:14:25 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_vector	vector(double x, double y, double z)
{
	return ((t_vector){.x = x, .y = y, .z = z, .w = 0});
}

double	vector_magnitude(t_vector vector1)
{
	double	result;

	result = sqrt(pow(vector1.x, 2) + pow(vector1.y, 2) + pow(vector1.z, 2));
	return (result);
}

t_vector	vector_normalize(t_vector vector1)
{
	t_vector	new;
	double		magnitude;

	magnitude = vector_magnitude(vector1);
	new.x = vector1.x / magnitude;
	new.y = vector1.y / magnitude;
	new.z = vector1.z / magnitude;
	new.w = vector1.w / magnitude;
	return (new);
}

double	vector_dot_product(t_vector vector1, t_vector vector2)
{
	return (vector1.x * vector2.x
		+ vector1.y * vector2.y
		+ vector1.z * vector2.z
		+ vector1.w * vector2.w);
}

t_tuple	vector_cross_product(t_vector vector1, t_vector vector2)
{
	return (vector(vector1.y * vector2.z - vector1.z * vector2.y,
			vector1.z * vector2.x - vector1.x * vector2.z,
			vector1.x * vector2.y - vector1.y * vector2.x));
}
