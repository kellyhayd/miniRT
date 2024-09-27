/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   transformation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:39:07 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 22:27:56 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Creates a translation matrix.
 *
 * This function generates a translation matrix that can be used to translate
 * points or objects in 3D space by the specified amounts along the x, y, and z
 * axes.
 *
 * @param x The translation distance along the x-axis.
 * @param y The translation distance along the y-axis.
 * @param z The translation distance along the z-axis.
 * @return A translation matrix representing the specified translation.
 */
t_matrix	translation(double x, double y, double z)
{
	t_matrix	result;

	result = identity();
	mx_set(&result, 0, 3, x);
	mx_set(&result, 1, 3, y);
	mx_set(&result, 2, 3, z);
	return (result);
}

/**
 * @brief Creates a scaling transformation matrix.
 *
 * This function generates a scaling matrix that can be used to scale objects
 * in 3D space. The scaling factors for the x, y, and z axes are provided as
 * parameters.
 *
 * @param x The scaling factor for the x-axis.
 * @param y The scaling factor for the y-axis.
 * @param z The scaling factor for the z-axis.
 * @return A t_matrix representing the scaling transformation.
 */
t_matrix	scaling(double x, double y, double z)
{
	t_matrix	result;

	result = identity();
	mx_set(&result, 0, 0, x);
	mx_set(&result, 1, 1, y);
	mx_set(&result, 2, 2, z);
	return (result);
}

/**
 * @brief Creates a shearing transformation matrix.
 *
 * This function generates a shearing matrix that can be used to shear objects
 * in 3D space. The shearing factors for the x, y, and z axes are provided as
 * parameters.
 *
 * @param prop_x A pointer to an array of doubles representing the shearing
 * factors in the x direction.
 * @param prop_y A pointer to an array of doubles representing the shearing
 * factors in the y direction.
 * @param prop_z A pointer to an array of doubles representing the shearing
 * factors in the z direction.
 * @return A t_matrix structure representing the sheared matrix.
 */
t_matrix	shearing(double *prop_x, double *prop_y, double *prop_z)
{
	t_matrix		result;

	result = identity();
	mx_set(&result, 0, 1, prop_x[0]);
	mx_set(&result, 0, 2, prop_x[1]);
	mx_set(&result, 1, 0, prop_y[0]);
	mx_set(&result, 1, 2, prop_y[1]);
	mx_set(&result, 2, 0, prop_z[0]);
	mx_set(&result, 2, 1, prop_z[1]);
	return (result);
}

/**
 * @brief Sets the transformation matrix for a given shape.
 *
 * This function assigns a transformation matrix to the specified shape,
 * allowing for various geometric transformations such as translation,
 * rotation, scaling, and shearing to be applied to the shape.
 *
 * @param shape A pointer to the shape to which the transformation matrix
 * will be applied.
 * @param transformation The transformation matrix to be set for the shape.
 */
void	set_transformation(t_shape *shape, t_matrix tranformation)
{
	shape->transform = tranformation;
	shape->inverse = inverse(tranformation);
	shape->transpose = transpose(tranformation);
}
