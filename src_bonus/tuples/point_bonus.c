/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   point_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 20:22:16 by danbarbo          #+#    #+#             */
/*   Updated: 2024/11/03 16:50:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples_bonus.h"

/**
 * @brief Creates a point with the given x, y, and z coordinates.
 *
 * This function initializes a t_point structure with the specified
 * coordinates and returns it.
 *
 * @param x The x-coordinate of the point.
 * @param y The y-coordinate of the point.
 * @param z The z-coordinate of the point.
 * @return A t_point structure initialized with the given coordinates.
 */
t_point	point(double x, double y, double z)
{
	return ((t_point){.x = x, .y = y, .z = z, .w = 1});
}
