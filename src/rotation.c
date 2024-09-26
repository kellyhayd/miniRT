/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:38:22 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 14:59:18 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Generates a rotation matrix for a rotation around the X-axis.
 *
 * This function creates a 4x4 matrix that represents a rotation by a given
 * angle in radians around the X-axis. The resulting matrix can be used to
 * transform coordinates in 3D space.
 *
 * @param radians The angle of rotation in radians.
 * @return A 4x4 matrix representing the rotation around the X-axis.
 */
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

/**
 * @brief Generates a rotation matrix for a rotation around the Y-axis.
 *
 * This function creates a 4x4 matrix that represents a rotation by a given
 * angle in radians around the Y-axis. The resulting matrix can be used to
 * transform 3D coordinates by rotating them around the Y-axis.
 *
 * @param radians The angle of rotation in radians.
 * @return A 4x4 matrix representing the rotation around the Y-axis.
 */
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

/**
 * @brief Generates a rotation matrix for a rotation around the Z-axis.
 *
 * This function creates a 3x3 rotation matrix that represents a rotation
 * by a specified angle in radians around the Z-axis. The resulting matrix
 * can be used to rotate points or vectors in 3D space.
 *
 * @param radians The angle of rotation in radians.
 * @return A 3x3 rotation matrix for the specified rotation around the Z-axis.
 */
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
