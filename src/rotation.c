/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:38:22 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/22 23:03:03 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	rotation_x(double radians)
{
	t_matrix		result;
	const double	cos_radians = cos(radians);
	const double	sin_radians = sin(radians);

	result = identity();
	mx_set(&result, 1, 1, cos_radians);
	mx_set(&result, 1, 2, -sin_radians);
	mx_set(&result, 2, 1, sin_radians);
	mx_set(&result, 2, 2, cos_radians);
	return (result);
}

t_matrix	rotation_y(double radians)
{
	t_matrix		result;
	const double	cos_radians = cos(radians);
	const double	sin_radians = sin(radians);

	result = identity();
	mx_set(&result, 0, 0, cos_radians);
	mx_set(&result, 0, 2, sin_radians);
	mx_set(&result, 2, 0, -sin_radians);
	mx_set(&result, 2, 2, cos_radians);
	return (result);
}

t_matrix	rotation_z(double radians)
{
	t_matrix		result;
	const double	cos_radians = cos(radians);
	const double	sin_radians = sin(radians);

	result = identity();
	mx_set(&result, 0, 0, cos_radians);
	mx_set(&result, 0, 1, -sin_radians);
	mx_set(&result, 1, 0, sin_radians);
	mx_set(&result, 1, 1, cos_radians);
	return (result);
}
