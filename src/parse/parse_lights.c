/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:15:43 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/19 10:35:20 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parses a light definition from a line of input and adds it to the
 * world.
 *
 * This function takes a line of input that defines a light and parses it to
 * extract the light's properties. The parsed light is then added to the world.
 *
 * @param line A string containing the light definition.
 * @param world A pointer to the world structure where the parsed light will be
 * added.
 * @return true if the light was successfully parsed and added to the world,
 * false otherwise.
 */
bool	parse_light(char *line, t_world *world)
{
	t_color	new_color;
	t_point	position;
	double	bright;
	char	**splitted;

	splitted = ft_split(line, ' ');
	bright = 0;
	if (!validate_count(splitted, 4) \
		|| !parse_coordinates(splitted[1], &position) \
		|| !parse_brightness(splitted[2], &bright) \
		|| !parse_color(splitted[3], &new_color))
	{
		ft_free_split(splitted);
		return (false);
	}
	add_light(&world->light, \
			point_light(position, color_multiply(new_color, bright)));
	ft_free_split(splitted);
	return (true);
}
