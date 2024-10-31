/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:51:06 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/31 08:55:29 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"
#include "minirt.h"

/**
 * @brief Creates a tuple with the given x, y, z, and w components.
 *
 * This function initializes a tuple structure with the specified
 * components. The tuple can represent a point, vector, or other
 * mathematical entity depending on the value of w.
 *
 * @param x The x component of the tuple.
 * @param y The y component of the tuple.
 * @param z The z component of the tuple.
 * @param w The w component of the tuple.
 * @return A t_tuple structure initialized with the given components.
 */
t_tuple	tuple(double x, double y, double z, double w)
{
	return ((t_tuple){.x = x, .y = y, .z = z, .w = w});
}

/**
 * @brief Compares two floating-point numbers for equality.
 *
 * This function compares two double precision floating-point numbers
 * to determine if they are equal within a certain tolerance.
 *
 * @param d1 The first double to compare.
 * @param d2 The second double to compare.
 * @return An integer indicating the result of the comparison:
 *         1 if the numbers are considered equal (minor than EPSILON),
 *         0 otherwise.
 */
int	float_compare(double d1, double d2)
{
	return (fabs(d1 - d2) < EPSILON);
}

/**
 * @brief Compares two tuples for equality. For tests use only.
 *
 * This function takes two tuples as input and compares them to determinez
 * if they are equal.
 *
 * @param tuple1 The first tuple to compare.
 * @param tuple2 The second tuple to compare.
 * @return An integer indicating the result of the comparison.
 *         Returns 1 if the tuples are equal, 0 otherwise.
 */
int	tuple_compare(t_tuple tuple1, t_tuple tuple2)
{
	return (float_compare(tuple1.x, tuple2.x)
		&& float_compare(tuple1.y, tuple2.y)
		&& float_compare(tuple1.z, tuple2.z)
		&& float_compare(tuple1.w, tuple2.w));
}
