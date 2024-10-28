#include "minirt.h"

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
					* w.scene.pixel_sampling)] = color_at(w, ray, 4); // color_at ganhou novo argumento (depth),
																// precisa verificar como preencher aqui
																// setei 4 por recomendação do livro (default)
																// Dá pra colocar em uma variável no t_world
			aa_data.sample_x++;
		}
		aa_data.sample_y++;
	}
	color_average_result = color_average(colors, pow(w.scene.pixel_sampling, 2));
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
	print_rendering_progress(c.hsize, c.vsize, 0);
	while (++y < c.vsize)
	{
		if (thread_count < NUM_THREADS)
		{
			threads_data[thread_count] = (t_thread){.line = y, \
		.line_size = c.hsize, .canvas = &image, .world = w, .camera = c};
			pthread_create(&threads[thread_count], NULL,
				render_line, &threads_data[thread_count]);
				// render_line(&threads_data[thread_count]);
			thread_count++;
		}
		thread_count = reset_threads(threads, thread_count);	// Uma pequena gambiarra
		print_rendering_progress(c.hsize, c.vsize, y);
		// thread_count = 0;
	}
	join_threads(threads, thread_count);
	return (image);
}
