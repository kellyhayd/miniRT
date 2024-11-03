/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 07:33:10 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:57:49 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_bonus.h"
#include "minirt_bonus.h"

t_camera	camera(double hsize, double vsize, double field_of_view)
{
	t_camera	c;
	double		half_view;
	double		aspect;

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

t_matrix	view_transform(t_point from, t_point to, t_vector up)
{
	t_vector	forward;
	t_vector	left;
	t_vector	true_up;
	t_matrix	orientation;
	t_matrix	view_matrix;

	forward = normalize(tuple_subtract(to, from));
	if (1 - fabs(dot(forward, up)) < EPSILON)
		left = vector(-1, 0, 0);
	else
		left = cross(forward, normalize(up));
	true_up = cross(left, forward);
	orientation = identity();
	mx_set(&orientation, 0, 0, left.x);
	mx_set(&orientation, 0, 1, left.y);
	mx_set(&orientation, 0, 2, left.z);
	mx_set(&orientation, 1, 0, true_up.x);
	mx_set(&orientation, 1, 1, true_up.y);
	mx_set(&orientation, 1, 2, true_up.z);
	mx_set(&orientation, 2, 0, -forward.x);
	mx_set(&orientation, 2, 1, -forward.y);
	mx_set(&orientation, 2, 2, -forward.z);
	view_matrix = mx_multiply(
			orientation, translation(-from.x, -from.y, -from.z));
	return (view_matrix);
}

t_ray	ray_for_pixel(t_camera c, int x, int y, t_anti_aliasing aa_data)
{
	double		x_offset;
	double		y_offset;
	double		world_x;
	double		world_y;
	t_point		origin;

	x_offset = (x + (1.0 / pow(aa_data.pixel_sampling, 2)) + aa_data.sample_x
			* (1.0 / aa_data.pixel_sampling)) * c.pixel_size;
	y_offset = (y + (1.0 / pow(aa_data.pixel_sampling, 2)) + aa_data.sample_y
			* (1.0 / aa_data.pixel_sampling)) * c.pixel_size;
	world_x = c.half_width - x_offset;
	world_y = c.half_height - y_offset;
	origin = mx_multiply_tuple(c.inverse, point(0, 0, 0));
	return (ray(origin, normalize(tuple_subtract(
					mx_multiply_tuple(c.inverse, point(world_x, world_y, -1)),
					origin
				)))
	);
}
