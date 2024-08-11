/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   colors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:05:08 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/11 20:15:46 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	color(double r, double g, double b)
{
	return ((t_color){.r = r, .g = g, .b = b});
}

t_color	color_add(t_color color1, t_color color2)
{
	t_color	result;

	result.r = color1.r + color2.r;
	result.g = color1.g + color2.g;
	result.b = color1.b + color2.b;
	return (result);
}

t_color color_subtract(t_color color1, t_color color2)
{
	t_color	result;

	result.r = color1.r - color2.r;
	result.g = color1.g - color2.g;
	result.b = color1.b - color2.b;
	return (result);
}

t_color color_multiply(t_color color1, double scalar)
{
	t_color	result;

	result.r = color1.r * scalar;
	result.g = color1.g * scalar;
	result.b = color1.b * scalar;
	return (result);
}

t_color	hadamard_product(t_color color1, t_color color2)
{
	t_color	result;

	result.r = color1.r * color2.r;
	result.g = color1.g * color2.g;
	result.b = color1.b * color2.b;
	return (result);
}
