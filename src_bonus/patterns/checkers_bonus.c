/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   checkers_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:19:53 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:57:18 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes_bonus.h"

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
	int		color_mod;
	int		sum_of_coordinates;
	t_color	new_color;

	sum_of_coordinates = (int)(pattern_point.x)
		+ (int)(pattern_point.y)
		+ (int)(pattern_point.z);
	if (sum_of_coordinates % 2 == 0)
		color_mod = 0;
	else
		color_mod = 1;
	if (pattern_point.z < 0)
		color_mod = !color_mod;
	if (pattern_point.x < 0)
		color_mod = !color_mod;
	if (color_mod)
		new_color = pattern.color_a;
	else
		new_color = pattern.color_b;
	return (new_color);
}
