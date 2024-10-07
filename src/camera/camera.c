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

t_camera camera(double hsize, double vsize, double field_of_view)
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

t_ray	ray_for_pixel(t_camera c, int x, int y, int pixel_sampling, int sample_x, int sample_y)
{
	double		x_offset;
	double		y_offset;
	double		world_x;
	double		world_y;
	t_point		origin;

	x_offset = (x + (1.0 / (pixel_sampling * pixel_sampling))
			+ sample_x * (1.0 / pixel_sampling)) * c.pixel_size;
	y_offset = (y + (1.0 / (pixel_sampling * pixel_sampling))
			+ sample_y * (1.0 / pixel_sampling)) * c.pixel_size;
	world_x = c.half_width - x_offset;
	world_y = c.half_height - y_offset;
	origin = mx_multiply_tuple(c.inverse, point(0, 0, 0));
	return (
		ray(
			origin,
			normalize(
					tuple_subtract(
						mx_multiply_tuple(c.inverse, point(world_x, world_y, -1)),
						origin
				)
			)
		)
	);
}

void	print_rendering_progress(int hsize, int vsize, int x, int y)
{
	double	progress;

	progress = (double)(y * hsize + x) / (double)(hsize * vsize) * 100;
	printf("\r[");
	for (int i = 0; i < 50; i++)
	{
		if (i < progress / 2)
			printf("=");
		else if (fabs(progress / 2 - i) < 1)
			printf(">");
		else if (i % 5 == 0)
			printf("o");
		else
			printf(" ");
	}
	printf("] %.2f%%", progress);
	// fflush(stdout);
}

t_color	color_average(t_color *colors, int size)
{
	int		i;
	double	r;
	double	g;
	double	b;
	t_color	average;

	r = 0;
	g = 0;
	b = 0;
	i = 0;
	while (i < size)
	{
		r += colors[i].r;
		g += colors[i].g;
		b += colors[i].b;
		i++;
	}
	average = color(r / size, g / size, b / size);
	return (average);
}

static t_color	render_pixel(t_camera c, t_world w, int x, int y)
{
	int			sub_pixel_x;
	int			sub_pixel_y;
	t_color		color_average_result;
	t_ray		ray;
	t_color		*colors;

	colors = malloc(sizeof(t_color) * pow(w.pixel_sampling, 2));

	sub_pixel_y = 0;
	while (sub_pixel_y < w.pixel_sampling)
	{
		sub_pixel_x = 0;
		while (sub_pixel_x < w.pixel_sampling)
		{
			ray = ray_for_pixel(c, x, y, w.pixel_sampling, sub_pixel_x, sub_pixel_y);
			colors[sub_pixel_x + sub_pixel_y * w.pixel_sampling] = color_at(w, ray);
			sub_pixel_x++;
		}
		sub_pixel_y++;
	}
	color_average_result = color_average(colors, pow(w.pixel_sampling, 2));

	free(colors);

	return (color_average_result);
}

t_canvas	render(t_camera c, t_world w)
{
	t_canvas	image;
	t_color		coloring;
	int			x;
	int			y;

	image = create_canvas(c.hsize, c.vsize);
	y = 0;
	print_rendering_progress(c.hsize, c.vsize, 0, 0);
	while (y < c.vsize)
	{
		x = 0;
		while (x < c.hsize)
		{
			coloring = render_pixel(c, w, x, y);
			write_pixel_to_canvas(&image, x, y, coloring);
			x++;
		}
		y++;
		print_rendering_progress(c.hsize, c.vsize, x, y);
	}

	return (image);
}
