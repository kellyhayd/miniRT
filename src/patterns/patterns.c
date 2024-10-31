/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   patterns.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 18:19:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/31 06:35:06 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

t_pattern	default_pattern(void)
{
	return ((t_pattern){
		.pattern_type = STRIPE,
		.has_pattern = false,
		.color_a = color(0, 0, 0),
		.color_b = color(0, 0, 0),
		.transform = identity(),
		.inverse = identity()
	});
}

void	set_pattern_transform(t_pattern *pattern, t_matrix transformation)
{
	pattern->transform = transformation;
	pattern->inverse = inverse(transformation);
}

static t_color	checkers_shape(t_pattern pattern, t_shape object,
	t_point pattern_point)
{
	double	u;
	double	v;
	t_color	color_pattern;

	if (object.shape_type == SPHERE || object.shape_type == CONE
		|| object.shape_type == CYLINDER)
	{
		spherical_map(pattern_point, &u, &v);
		color_pattern = uv_pattern_at(pattern.map.checkers, u, v);
	}
	else
		color_pattern = checkers_at(pattern, pattern_point);
	return (color_pattern);
}

t_color	pattern_at_shape(t_pattern pattern, t_shape object, t_point world_point)
{
	t_point	object_point;
	t_point	pattern_point;
	t_color	color_pattern;

	object_point = mx_multiply_tuple(object.inverse, world_point);
	pattern_point = mx_multiply_tuple(pattern.inverse, object_point);
	if (pattern.pattern_type == STRIPE)
		color_pattern = stripe_at(pattern, pattern_point);
	else if (pattern.pattern_type == GRADIENT)
		color_pattern = gradient_at(pattern, pattern_point);
	else if (pattern.pattern_type == RING)
		color_pattern = ring_at(pattern, pattern_point);
	else if (pattern.pattern_type == CHECKERS)
		color_pattern = checkers_shape(pattern, object, pattern_point);
	else
		color_pattern = pattern.color_a;
	return (color_pattern);
}
