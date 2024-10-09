/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   camera.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/29 07:33:10 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/05 08:41:59 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

static t_color	render_pixel(t_camera c, t_world w, int x, int y)
{
	t_anti_aliasing	aa_data;
	t_color			color_average_result;
	t_ray			ray;
	t_color			*colors;

	colors = malloc(sizeof(t_color) * pow(w.pixel_sampling, 2));
	aa_data.pixel_sampling = w.pixel_sampling;
	aa_data.sample_y = 0;
	while (aa_data.sample_y < w.pixel_sampling)
	{
		aa_data.sample_x = 0;
		while (aa_data.sample_x < w.pixel_sampling)
		{
			ray = ray_for_pixel(c, x, y, aa_data);
			colors[(int) aa_data.sample_x + (int)(aa_data.sample_y
					* w.pixel_sampling)] = color_at(w, ray);
			aa_data.sample_x++;
		}
		aa_data.sample_y++;
	}
	color_average_result = color_average(colors, pow(w.pixel_sampling, 2));
	free(colors);
	return (color_average_result);
}

void	*render_line(void *param)
{
	int			x;
	t_color		coloring;
	t_thread	data;

	data = (*(t_thread *)param);
	x = 0;
	while (x < data.line_size)
	{
		coloring = render_pixel(data.camera, data.world, x, data.line);
		write_pixel_to_canvas(data.canvas, x, data.line, coloring);
		x++;
	}
	return (NULL);
}

t_canvas	render(t_camera c, t_world w)
{
	int			y;
	int			thread_count;
	t_canvas	image;
	t_thread	threads_data[NUM_THREADS];
	pthread_t	threads[NUM_THREADS];

	y = -1;
	thread_count = 0;
	image = create_canvas(c.hsize, c.vsize);
	print_rendering_progress(c.hsize, c.vsize, 0, 0);
	while (++y < c.vsize)
	{
		if (thread_count < NUM_THREADS)
		{
			threads_data[thread_count] = (t_thread){.line = y, \
		.line_size = c.hsize, .canvas = &image, .world = w, .camera = c};
			pthread_create(&threads[thread_count], NULL,
				render_line, &threads_data[thread_count]);
			thread_count++;
		}
		thread_count = reset_threads(threads, thread_count);	// Uma pequena gambiarra
		print_rendering_progress(c.hsize, c.vsize, 0, y);
	}
	join_threads(threads, thread_count);
	return (image);
}
