/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:31:43 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/26 14:55:53 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Creates a vector with the given x, y, and z components.
 *
 * This function initializes a vector structure with the specified
 * x, y, and z values, and returns the resulting vector.
 *
 * @param x The x component of the vector.
 * @param y The y component of the vector.
 * @param z The z component of the vector.
 * @return A t_vector structure initialized with the given components.
 */
t_vector	vector(double x, double y, double z)
{
	return ((t_vector){.x = x, .y = y, .z = z, .w = 0});
}

/**
 * @brief Calculates the magnitude (length) of a given vector.
 *
 * This function takes a vector as input and returns its magnitude,
 * which is the Euclidean norm of the vector.
 *
 * @param vector1 The vector for which the magnitude is to be calculated.
 * @return The magnitude of the vector.
 */
double	magnitude(t_vector vector1)
{
	double	result;

	result = sqrt(pow(vector1.x, 2) + pow(vector1.y, 2) + pow(vector1.z, 2));
	return (result);
}

/**
 * @brief Normalizes the given vector.
 *
 * This function takes a vector as input and returns a normalized version of it.
 * A normalized vector has a magnitude of 1 and points in the same direction as
 * the original vector.
 *
 * @param vector1 The vector to be normalized.
 * @return A normalized vector with the same direction as the input vector.
 */
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
/**
 * Calculates the dot product of two vectors.
 *
 * @param vector1 The first vector.
 * @param vector2 The second vector.
 * @return The cross product of t * @return The dot product of vector1 and vector2.ector2)
 */
double	dot(t_vector vector1, t_vector vector2)
{
	return (vector1.x * vector2.x
		+ vector1.y * vector2.y
		+ vector1.z * vector2.z
		+ vector1.w * vector2.w);
}

/**
 * @brief Computes the cross product of two vectors.
 *
 * This function takes two vectors as input and returns their cross product.
 *
 * @param vector1 The first vector.
 * @param vector2 The second vector.
 * @return The cross product of the two vectors as a t_tuple.
 */
t_tuple	cross(t_vector vector1, t_vector vector2)
{
	return (vector(vector1.y * vector2.z - vector1.z * vector2.y,
			vector1.z * vector2.x - vector1.x * vector2.z,
			vector1.x * vector2.y - vector1.y * vector2.x));
}
