/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   render.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:07:48 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 14:34:54 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tuples.h"
#include "scene.h"

static t_color	render_pixel(t_camera c, t_world w, int x, int y)
{
	t_anti_aliasing	aa_data;
	t_color			color_average_result;
	t_ray			ray;
	t_color			*colors;

	colors = malloc(sizeof(t_color) * pow(w.scene.pixel_sampling, 2));
	aa_data.pixel_sampling = w.scene.pixel_sampling;
	aa_data.sample_y = 0;
	while (aa_data.sample_y < w.scene.pixel_sampling)
	{
		aa_data.sample_x = 0;
		while (aa_data.sample_x < w.scene.pixel_sampling)
		{
			ray = ray_for_pixel(c, x, y, aa_data);
			colors[(int) aa_data.sample_x + (int)(aa_data.sample_y
					* w.scene.pixel_sampling)] = color_at(w, ray, 4);
			aa_data.sample_x++;
		}
		aa_data.sample_y++;
	}
	color_average_result = color_average(colors, \
						pow(w.scene.pixel_sampling, 2));
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
	t_canvas	image;
	t_thread	threads_data[1];

	y = -1;
	image = create_canvas(c.hsize, c.vsize);
	print_rendering_progress(c.hsize, c.vsize, 0);
	while (++y < c.vsize)
	{
		threads_data[0] = (t_thread){.line = y, \
	.line_size = c.hsize, .canvas = &image, .world = w, .camera = c};
		render_line(&threads_data[0]);
		print_rendering_progress(c.hsize, c.vsize, y);
	}
	return (image);
}
