/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuple.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:51:06 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/05 21:28:13 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_tuple	tuple(double x, double y, double z, double w)
{
	return ((t_tuple){.x = x, .y = y, .z = z});
}

int	tuple_compair(tt)
