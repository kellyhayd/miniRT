/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:29:57 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:50:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples_bonus.h"

/**
 * @brief Converts a normalized color value to an 8-bit color value.
 *
 * This function takes a color value in the range [0, 1] and converts it to
 * an 8-bit color value in the range [0, 255]. If the input color value is
 * greater than 1, it returns 255. Otherwise, it scales the color value by 255.
 *
 * @param color_value The normalized color value to be converted.
 * @return The 8-bit color value.
 */
static int	convert(double color_value)
{
	if (color_value > 1)
		color_value = 1;
	color_value *= 255 + 0.5;
	return ((int) color_value & 0xFF);
}

/**
 * Converts a t_color structure to an integer representation.
 *
 * @param color The t_color structure containing the color components.
 * @return An integer representing the color.
 */
int	color_to_int(t_color color)
{
	int	color_int;

	color_int = convert(color.r) << 24
		| convert(color.g) << 16
		| convert(color.b) << 8
		| 0xFF;
	return (color_int);
}

t_color	convert_color(t_color color)
{
	return ((t_color){
		.r = color.r / 255,
		.g = color.g / 255,
		.b = color.b / 255,
	});
}
