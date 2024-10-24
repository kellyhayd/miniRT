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
 * @param str The string containing the color information to be parsed.
 * @param new_color A pointer to the t_color structure where the parsed color
 *                  will be stored.
 * @return true if the color was successfully parsed and stored, false
 *         otherwise.
 */
bool	parse_color(char *str, t_color *new_color)
{
	int		color_r;
	int		color_g;
	int		color_b;
	char	**splitted;

	splitted = ft_split(str, ',');
	if (!validate_count(splitted, 3)
		|| !parse_int_color(splitted[0], &color_r)
		|| !parse_int_color(splitted[1], &color_g)
		|| !parse_int_color(splitted[2], &color_b))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	new_color->r = color_r;
	new_color->g = color_g;
	new_color->b = color_b;
	*new_color = convert_color(*new_color);
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
		|| !(*brightness >= 0 && *brightness <= 1))
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

bool	parse_direction(char *str, t_vector *direction)
{
	char	**splitted;

	splitted = ft_split(str, ',');
	if (!validate_count(splitted, 3)
		|| !parse_double(splitted[0], &direction->x)
		|| !parse_double(splitted[1], &direction->y)
		|| !parse_double(splitted[2], &direction->z)
		// || fabs(1 - magnitude(*direction)) >= EPSILON
		)
	{
		ft_free_split(splitted);
		return (false);
	}
	direction->w = 0;
	*direction = normalize(*direction);
	return (true);
}
