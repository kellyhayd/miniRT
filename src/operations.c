/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:45:35 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/26 15:08:42 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Adds two tuples together.
 *
 * This function takes two tuples as input and returns a new tuple that is the result
 * of adding the corresponding components of the input tuples.
 *
 * @param tuple1 The first tuple to be added.
 * @param tuple2 The second tuple to be added.
 * @return A new tuple that is the sum of the input tuples.
 */
t_tuple	tuple_add(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	result;

	result.x = tuple1.x + tuple2.x;
	result.y = tuple1.y + tuple2.y;
	result.z = tuple1.z + tuple2.z;
	result.w = tuple1.w + tuple2.w;
	return (result);
}

/**
 * Subtracts one tuple from another.
 *
 * @param tuple1 The first tuple.
 * @param tuple2 The second tuple to subtract from the first tuple.
 * @return The result of the subtraction as a new tuple.
 */
t_tuple	tuple_subtract(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	result;

	result.x = tuple1.x - tuple2.x;
	result.y = tuple1.y - tuple2.y;
	result.z = tuple1.z - tuple2.z;
	result.w = tuple1.w - tuple2.w;
	return (result);
}

/**
 * Negates the components of a given tuple.
 *
 * @param tuple The tuple to be negated.
 * @return A new tuple with each component negated.
 */
t_tuple	tuple_negate(t_tuple tuple)
{
	t_tuple	result;

	result.x = -tuple.x;
	result.y = -tuple.y;
	result.z = -tuple.z;
	result.w = -tuple.w;
	return (result);
}

/**
 * Multiplies each component of the given tuple by the specified scalar.
 *
 * @param tuple The tuple to be multiplied.
 * @param scalar The scalar value to multiply each component of the tuple by.
 * @return A new tuple where each component is the result of the original component
 *         multiplied by the scalar.
 */
t_tuple	tuple_multiply(t_tuple tuple, double scalar)
{
	t_tuple	result;

	result.x = tuple.x * scalar;
	result.y = tuple.y * scalar;
	result.z = tuple.z * scalar;
	result.w = tuple.w * scalar;
	return (result);
}

/**
 * @brief Divides each component of a tuple by a given fraction.
 *
 * This function takes a tuple and a fraction, and returns a new tuple
 * where each component of the original tuple is divided by the fraction.
 *
 * @param tuple The tuple to be divided.
 * @param fraction The fraction by which to divide each component of the tuple.
 * @return A new tuple with each component divided by the fraction.
 */
t_tuple	tuple_divide(t_tuple tuple, double fraction)
{
	t_tuple	result;

	result.x = tuple.x / fraction;
	result.y = tuple.y / fraction;
	result.z = tuple.z / fraction;
	result.w = tuple.w / fraction;
	return (result);
}
