/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ring.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:19:42 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/20 18:19:43 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	ring_pattern(t_color color_a, t_color color_b)
{
	return ((t_pattern){
		.pattern_type = RING,
		.has_pattern = true,
		.color_a = color_a,
		.color_b = color_b,
		.transform = identity(),
		.inverse = identity()
	});
}

t_color	ring_at(t_pattern pattern, t_point point)
{
	double	point_discriminant;
	t_color	new_color;

	point_discriminant = floor(sqrt(pow(point.x, 2) + pow(point.z, 2)));
	if (almost_zero(fmod(point_discriminant, 2)))
		new_color = pattern.color_a;
	else
		new_color = pattern.color_b;
	return (new_color);
}
