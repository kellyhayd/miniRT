/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 07:33:10 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/29 11:16:30 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_camera camera(double hsize, double vsize, double field_of_view)
{
	t_camera c;
	double	half_view;
	double	aspect;

	c.hsize = hsize;
	c.vsize = vsize;
	c.field_of_view = field_of_view;
	c.transform = identity();
	half_view = tan(c.field_of_view / 2);
	aspect = c.hsize / c.vsize;
	c.half_width = half_view;
	c.half_height = half_view;
	if (aspect >= 1)
		c.half_height = half_view / aspect;
	else
		c.half_width = half_view * aspect;
	c.pixel_size = (c.half_width * 2) / c.hsize;
	return (c);
}

t_ray	ray_for_pixel(t_camera c, int x, int y)
{
	double		x_offset;
	double		y_offset;
	double		world_x;
	double		world_y;
	t_point		pixel;
	t_point		origin;
	t_vector	direction;

	x_offset = (x + 0.5) * c.pixel_size;
	y_offset = (y + 0.5) * c.pixel_size;
	world_x = c.half_width - x_offset;
	world_y = c.half_height - y_offset;
	pixel = mx_multiply_tuple(inverse(c.transform), point(world_x, world_y, -1));
	origin = mx_multiply_tuple(inverse(c.transform), point(0, 0, 0));
	direction = normalize(tuple_subtract(pixel, origin));
	return (ray(origin, direction));
}
