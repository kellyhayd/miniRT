/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:39:07 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/22 16:15:29 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	translation(double x, double y, double z)
{
	t_matrix	result;

	result = identity();
	mx_set(&result, 3, 0, x);
	mx_set(&result, 3, 1, y);
	mx_set(&result, 3, 2, z);
	return (result);
}

t_matrix	scaling(double x, double y, double z)
{
	t_matrix	result;

	result = identity();
	mx_set(&result, 0, 0, x);
	mx_set(&result, 1, 1, y);
	mx_set(&result, 2, 2, z);
	return (result);
}

t_matrix	shearing(double *prop_x, double *prop_y, double *prop_z)
{
	t_matrix		result;

	result = identity();
	mx_set(&result, 1, 0, prop_x[0]);
	mx_set(&result, 2, 0, prop_x[1]);
	mx_set(&result, 0, 1, prop_y[0]);
	mx_set(&result, 2, 1, prop_y[1]);
	mx_set(&result, 0, 2, prop_z[0]);
	mx_set(&result, 1, 2, prop_z[1]);
	return (result);
}
