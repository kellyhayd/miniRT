/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:31:43 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/06 21:38:48 by danbarbo         ###   ########.fr       */
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
