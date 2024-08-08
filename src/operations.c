/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:45:35 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/07 20:48:10 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	tuple_adding(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	result;

	result.x = tuple1.x + tuple2.x;
	result.y = tuple1.y + tuple2.y;
	result.z = tuple1.z + tuple2.z;
	result.w = tuple1.w + tuple2.w;
	return (result);
}

t_tuple	tuple_subtracting(t_tuple tuple1, t_tuple tuple2)
{
	t_tuple	result;

	result.x = tuple1.x - tuple2.x;
	result.y = tuple1.y - tuple2.y;
	result.z = tuple1.z - tuple2.z;
	result.w = tuple1.w - tuple2.w;
	return (result);
}

t_tuple	tuple_negating(t_tuple tuple)
{
	t_tuple	result;

	result.x = -tuple.x;
	result.y = -tuple.y;
	result.z = -tuple.z;
	result.w = -tuple.w;
	return (result);
}

t_tuple	tuple_multiplying(t_tuple tuple, double scalar)
{
	t_tuple	result;

	result.x = tuple.x * scalar;
	result.y = tuple.y * scalar;
	result.z = tuple.z * scalar;
	result.w = tuple.w * scalar;
	return (result);
}

t_tuple	tuple_dividing(t_tuple tuple, double fraction)
{
	t_tuple	result;

	result.x = tuple.x / fraction;
	result.y = tuple.y / fraction;
	result.z = tuple.z / fraction;
	result.w = tuple.w / fraction;
	return (result);
}
