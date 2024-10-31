/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_matrix.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:22:32 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/31 08:50:04 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"
#include "minirt.h"
#include "shapes.h"

static int	sign(int number)
{
	if (number > 0)
		return (1);
	else if (number < 0)
		return (-1);
	else
		return (0);
}

static void	calculate_rotation_angles(t_vector vec, double *x, double *z)
{
	if (fabs(vec.y) == 1)
	{
		*x = 0;
		*z = 0;
	}
	else if (fabs(vec.z) == 1)
	{
		*x = sign(vec.z) * (90 * M_PI / 180);
		*z = 0;
	}
	else if (fabs(vec.x) == 1)
	{
		*x = 0;
		*z = sign(vec.x) * (90 * M_PI / 180);
	}
	else
	{
		if (!almost_zero(vec.x))
			*x = acos(vec.x);
		if (!almost_zero(vec.z))
			*z = acos(vec.z);
	}
}

t_matrix	get_matrix(t_matrix scale, t_matrix rotate, t_matrix translate)
{
	t_matrix	result;

	result = mx_multiply(mx_multiply(scale, rotate), translate);
	return (result);
}

t_matrix	get_rot_matrix(double x, double z)
{
	t_matrix	result;

	result = mx_multiply(rotation_x(x), rotation_z(z));
	return (result);
}

t_matrix	rotation_matrix(t_point position, t_vector direction, t_shape shape)
{
	double	radius;
	double	x_angle;
	double	z_angle;

	x_angle = 0;
	z_angle = 0;
	calculate_rotation_angles(direction, &x_angle, &z_angle);
	radius = 1;
	if (shape.shape_type == SPHERE)
		radius = shape.sphere_shape.radius;
	else if (shape.shape_type == CYLINDER)
		radius = shape.cylinder_shape.radius;
	else if (shape.shape_type == CONE)
		radius = shape.cylinder_shape.radius;
	return (
		get_matrix(
			translation(position.x, position.y, position.z),
			get_rot_matrix(x_angle, z_angle),
			scaling(radius, radius, radius)
		)
	);
}
