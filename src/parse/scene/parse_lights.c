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

bool	parse_brightness_range(char *str, double *brightness)
{
	if (!(*brightness >= 0 && *brightness <= 1))
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putstr_fd("Expected " GREEN "value between 0 and 1" RESET
			", received " GREEN, 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(RESET, 2);
		return (false);
	}
	return (true);
}

/**
 * @brief Parses the brightness value from a given string.
 *
 * This function takes a string representing the brightness value and parses
 * it into a double. The parsed brightness value is then stored in the
 * provided double pointer.
 *
 * @param splitted A string containing the brightness value to be parsed.
 * @param brightness A pointer to a double where the parsed brightness value
 *                   will be stored.
 * @return true if the parsing is successful, false otherwise.
 */
bool	parse_brightness(char *str, double *brightness)
{
	if (!parse_double(str, brightness)
		|| !parse_brightness_range(str, brightness))
		return (false);
	return (true);
}

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
	if (!validate_count(splitted, 4) \
		|| !parse_coordinates(splitted[1], &position) \
		|| !parse_brightness(splitted[2], &bright) \
		|| !parse_color(splitted[3], &new_color))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	add_light(&world->light, \
			point_light(position, color_multiply(new_color, bright)));
	return (true);
}
