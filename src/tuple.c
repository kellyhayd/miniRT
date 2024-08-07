/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:51:06 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/05 21:51:39 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	tuple(double x, double y, double z, double w)
{
	return ((t_tuple){.x = x, .y = y, .z = z, .w = w});
}

int	tuple_compare(t_tuple tuple1, t_tuple tuple2)
{
	return (float_compare(tuple1.x, tuple2.x)
		&& float_compare(tuple1.y, tuple2.y)
		&& float_compare(tuple1.z, tuple2.z)
		&& float_compare(tuple1.w, tuple2.w));
}
