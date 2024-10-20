/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:19:53 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/20 18:20:20 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	checkers_pattern(t_color color_a, t_color color_b)
{
	return ((t_pattern){
		.pattern_type = CHECKERS,
		.has_pattern = true,
		.color_a = color_a,
		.color_b = color_b,
		.transform = identity(),
		.inverse = identity()
	});
}

t_color	checkers_at(t_pattern pattern, t_point pattern_point)
{
	double	sum_of_coordinates;
	t_color	new_color;

	sum_of_coordinates = floor(pattern_point.x) + floor(pattern_point.y) \
		+ floor(pattern_point.z);
	if (almost_zero(fmod(sum_of_coordinates, 2)))
		new_color = pattern.color_a;
	else
		new_color = pattern.color_b;
	return (new_color);
}
