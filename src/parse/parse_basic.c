/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:02:47 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/19 11:04:24 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_normal(char *splitted, t_vector *normal)
{
	char	**values;

	*normal = vector(0, 0, 0);
	values = ft_split(splitted, ',');
	if (!validate_count(values, 3) || !is_all_numbers(values)
		|| !validate_normal_range(values))
	{
		ft_free_split(values);
		return (false);
	}
	ft_free_split(values);
	return (true);
}

/**
 * @brief Parses a color from a string and stores it in a t_color structure.
 *
 * This function takes a string representing a color and parses it into a
 * t_color structure. The string should be in a format that can be correctly
 * interpreted as a color.
 *
 * @param splitted The string containing the color information to be parsed.
 * @param new_color A pointer to the t_color structure where the parsed color
 *                  will be stored.
 * @return true if the color was successfully parsed and stored, false
 *         otherwise.
 */
bool	parse_color(char *splitted, t_color *new_color)
{
	char	**colors;

	*new_color = color(0, 0, 0);
	colors = ft_split(splitted, ',');
	if (!validate_count(colors, 3) || !is_all_numbers(colors)
		|| !validate_color_range(colors))
	{
		ft_free_split(colors);
		return (false);
	}
	*new_color = color(ft_atoi(colors[0]), \
					ft_atoi(colors[1]), \
					ft_atoi(colors[2]));
	ft_free_split(colors);
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
bool	parse_brightness(char *splitted, double *brightness)
{
	*brightness = ft_atof(splitted);
	if (*brightness < 0 || *brightness > 1)
		return (false);
	return (true);
}

/**
 * @brief Parses a string containing coordinates and stores the result in a
 * t_point structure.
 *
 * This function takes a string of coordinates, splits it, and converts the
 * values into a t_point structure representing a position in 3D space.
 *
 * @param splitted A string containing the coordinates to be parsed.
 * @param position A pointer to a t_point structure where the parsed coordinates
 * will be stored.
 * @return true if the coordinates were successfully parsed and stored, false
 * otherwise.
 */
bool	parse_coordinates(char *splitted, t_point *position)
{
	char	**coordinates;

	*position = point(0, 0, 0);
	coordinates = ft_split(splitted, ',');
	if (!validate_count(coordinates, 3) || !is_all_numbers(coordinates))
	{
		ft_free_split(coordinates);
		return (false);
	}
	position->x = ft_atof(coordinates[0]);
	position->y = ft_atof(coordinates[1]);
	position->z = ft_atof(coordinates[2]);
	ft_free_split(coordinates);
	return (true);
}
