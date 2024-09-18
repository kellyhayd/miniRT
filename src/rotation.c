/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:38:22 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/18 17:38:47 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	matrix_rotation_x(double radians)
{
	t_matrix		result;
	const double	cos_radians = cos(radians);
	const double	sin_radians = sin(radians);

	result = matrix_identity();
	matrix_set(&result, 1, 1, cos_radians);
	matrix_set(&result, 2, 1, -sin_radians);
	matrix_set(&result, 1, 2, sin_radians);
	matrix_set(&result, 2, 2, cos_radians);
	return (result);
}

t_matrix	matrix_rotation_y(double radians)
{
	t_matrix		result;
	const double	cos_radians = cos(radians);
	const double	sin_radians = sin(radians);

	result = matrix_identity();
	matrix_set(&result, 0, 0, cos_radians);
	matrix_set(&result, 2, 0, sin_radians);
	matrix_set(&result, 0, 2, -sin_radians);
	matrix_set(&result, 2, 2, cos_radians);
	return (result);
}

t_matrix	matrix_rotation_z(double radians)
{
	t_matrix		result;
	const double	cos_radians = cos(radians);
	const double	sin_radians = sin(radians);

	result = matrix_identity();
	matrix_set(&result, 0, 0, cos_radians);
	matrix_set(&result, 1, 0, -sin_radians);
	matrix_set(&result, 0, 1, sin_radians);
	matrix_set(&result, 1, 1, cos_radians);
	return (result);
}
