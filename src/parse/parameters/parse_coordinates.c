/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_coordinates.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:33:07 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/29 21:33:08 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parses a string containing coordinates and stores the result in a
 * t_point structure.
 *
 * This function takes a string of coordinates, splits it, and converts the
 * values into a t_point structure representing a position in 3D space.
 *
 * @param str A string containing the coordinates to be parsed.
 * @param position A pointer to a t_point structure where the parsed coordinates
 * will be stored.
 * @return true if the coordinates were successfully parsed and stored, false
 * otherwise.
 */
bool	parse_coordinates(char *str, t_point *position)
{
	char	**splitted;

	splitted = ft_split(str, ',');
	if (!validate_count(splitted, 3)
		|| !parse_double(splitted[0], &position->x)
		|| !parse_double(splitted[1], &position->y)
		|| !parse_double(splitted[2], &position->z))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	position->w = 1;
	return (true);
}
