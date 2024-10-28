#include "minirt.h"

// #define WIDTH 1000
// #define HEIGHT 1000

t_canvas	render_image(void)
{
	// WALLS
	t_shape	floor = plane();
	// set_transformation(&floor, mx_multiply(rotation_x(90 * M_PI / 180), translation(0, 0, 5)));
	floor.material.pattern = checkers_pattern(color(0.5, 0.5, 0.5), color(0.75, 0.75, 0.75));
	set_pattern_transformation(&floor.material.pattern, scaling(0.05, 0.05, 0.05));
	floor.material.reflective = 1;

	// SPHERES
	t_shape	middle = sphere();
	set_transformation(&middle, mx_multiply(scaling(2, 2, 2), translation(0, 1, 0)));
	middle.material.pattern = checkers_pattern(color(0.5, 0.5, 0.5), color(0.75, 0.75, 0.75));
	middle.material.pattern.map = texture_map(uv_checkers(16, 8, color(0.5, 0.5, 0.5), color(0.75, 0.75, 0.75)), spherical_map);
	middle.material.transparency = 1;

	// LIGHTS
	t_light	light1 = point_light(point(0, 20, -10), color(1, 1, 1));

	// CAMERA
	t_camera	camera_view = camera(WIDTH, HEIGH, M_PI / 3);
	camera_view.transform = view_transform(
		point(0, 1, -7),
		point(0, 2, 0),
		vector(0, 1, 0)
	);
	camera_view.inverse = inverse(camera_view.transform);

	t_world	world_to_render = world();

	add_shape(&world_to_render.shape, floor);
	add_shape(&world_to_render.shape, middle);

	add_light(&world_to_render.light, light1);

	world_to_render.scene.pixel_sampling = 1;

	t_canvas	canvas = render(camera_view, world_to_render);

	world_clear(&world_to_render);

	return (canvas);
}

void	canvas_to_ppm(t_canvas canvas, char *filename)
{
	FILE	*file = fopen(filename, "w");

	if (!file)
	{
		perror(filename);
		return ;
	}

	fprintf(file, "P3\n%d %d\n255\n", canvas.width, canvas.height);
	for (int y = 0; y < canvas.height; y++)
	{
		for (int x = 0; x < canvas.width; x++)
		{
			t_color	pixel = pixel_at(canvas, x, y);
			int		r = (int)(pixel.r * 255);
			int		g = (int)(pixel.g * 255);
			int		b = (int)(pixel.b * 255);

			fprintf(file, "%d %d %d\n", r, g, b);
		}
	}
	fclose(file);
}

int main(void)
{
	mlx_t		*mlx;
	t_canvas	image;
	mlx_image_t	*mlx_image;

	(void)!write(STDOUT_FILENO, "\033[s", 4);

	// mlx = mlx_init(WIDTH, HEIGHT, "patterns", false);
	mlx = NULL;
	image = render_image();
	if (mlx)
	{
		mlx_image = canvas_to_image(image, mlx);
		mlx_image_to_window(mlx, mlx_image, 0, 0);
		mlx_loop(mlx);
	}

	canvas_to_ppm(image, "checker_sphere.ppm");
	free(image.pixels);

	(void)!write(STDOUT_FILENO, "\n", 1);

	return (0);
}
