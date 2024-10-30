/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   uv_checkers.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:30:26 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/29 21:30:27 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_checkers	uv_checkers(int width, int heigh, t_color color_a, t_color color_b)
{
	return ((t_checkers){
		.width = width,
		.heigh = heigh,
		.color_a = color_a,
		.color_b = color_b
	});
}

t_color	uv_pattern_at(t_checkers checkers, double u, double v)
{
	double	u2;
	double	v2;

	u2 = floor(u * checkers.width);
	v2 = floor(v * checkers.heigh);
	if (almost_zero(fmod(u2 + v2, 2)))
		return (checkers.color_a);
	return (checkers.color_b);
}

void	spherical_map(t_point point, double *u, double *v)
{
	*u = atan2(point.x, point.z) / (2 * M_PI);
	*v = acos(point.y / magnitude(vector(point.x, point.y, point.z))) / M_PI;
	*u = 1 - (*u + 0.5);
	*v = 1 - *v;
}

t_map	texture_map(t_checkers checkers,
	void (*map_fn)(t_point, double *, double *))
{
	return ((t_map){
		.checkers = checkers,
		.map_fn = map_fn
	});
}

void	cylindrical_map(t_point point, double *u, double *v)
{
	*v = fmod(point.y, 1);
	*u = 1 - (atan2(point.x, point.z) / (2 * M_PI) + 0.5);
}
