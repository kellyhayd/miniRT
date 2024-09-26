/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:05:08 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 15:21:44 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Creates a color structure with the specified red, green, and blue values.
 *
 * This function initializes a t_color structure with the given red (r), green (g),
 * and blue (b) components. Each component should be a double value representing
 * the intensity of the color channel.
 *
 * @param r The red component of the color.
 * @param g The green component of the color.
 * @param b The blue component of the color.
 * @return A t_color structure with the specified color components.
 */
t_color	color(double r, double g, double b)
{
	return ((t_color){.r = r, .g = g, .b = b});
}

/**
 * Adds two colors together.
 *
 * @param color1 The first color to add.
 * @param color2 The second color to add.
 * @return The resulting color after adding color1 and color2.
 */
t_color	color_add(t_color color1, t_color color2)
{
	t_color	result;

	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	return (result);
}

/**
 * Subtracts the second color from the first color.
 *
 * @param color1 The first color.
 * @param color2 The second color to subtract from the first color.
 * @return The resulting color after subtraction.
 */
t_color	color_subtract(t_color color1, t_color color2)
{
	t_color	result;

	result.r = color1.r - color2.r;
	result.g = color1.g - color2.g;
	result.b = color1.b - color2.b;
	return (result);
}

/**
 * Multiplies a color by a scalar value.
 *
 * @param color1 The original color to be multiplied.
 * @param scalar The scalar value to multiply the color by.
 * @return The resulting color after multiplication.
 */
t_color	color_multiply(t_color color1, double scalar)
{
	t_color	result;

	result.r = color1.r * scalar;
	result.g = color1.g * scalar;
	result.b = color1.b * scalar;
	return (result);
}

/**
 * @brief Performs the Hadamard product (element-wise multiplication) of two colors.
 *
 * This function takes two colors as input and returns a new color where each
 * component (red, green, blue) is the product of the corresponding components
 * of the input colors.
 *
 * @param color1 The first color.
 * @param color2 The second color.
 * @return A new color resulting from the Hadamard product of the input colors.
 */
t_color	color_hadamard(t_color color1, t_color color2)
{
	t_color	result;

	result.r = color1.r * color2.r;
	result.g = color1.g * color2.g;
	result.b = color1.b * color2.b;
	return (result);
}
