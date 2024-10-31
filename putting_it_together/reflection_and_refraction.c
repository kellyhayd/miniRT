#include "minirt.h"

#define WIDTH 1000
#define HEIGHT 1000

t_canvas	render_image(void)
{
	// WALLS
	t_shape	floor = plane();
	set_pattern_transform(&floor.material.pattern, mx_multiply(scaling(2, 2, 2), rotation_y(30 * M_PI / 180)));
	floor.material.color = color(1, 1, 1);
	// floor.material.reflective = 1;
	floor.material.transparency = 0.1;
	// floor.material.refractive_index = 10;

	// SPHERES
	t_shape	middle = sphere();
	middle.material.color = color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	middle.material.pattern = ring_pattern(color(1, 1, 0), color(1, 0, 0));
	// set_transformation(&middle, translation(0, 1, 1));
	// set_pattern_transform(&middle.material.pattern, scaling(0.2, 0.2, 0.2));

	t_shape	spheres[5] = {
		middle,
		middle,
		middle,
		middle,
		middle
	};

	double	factor = 0.05;
	for (int i = 0; i < 5; i++)
	{
		// set_transformation(&spheres[i], mx_multiply(translation(-2 + i, 1, 0), scaling(0.5, 0.5, 0.5)));
		set_transformation(&spheres[i], mx_multiply(translation(-2 + i, -1, 0), scaling(0.5, 0.5, 0.5)));
		set_pattern_transform(
			&spheres[i].material.pattern,
			mx_multiply(
				scaling(factor + factor * i, factor + factor * i, factor + factor * i),
				rotation_x(-60 * M_PI / 180)
			)
		);
	}

	set_transformation(&middle, translation(0, 3, 1));
	middle.material.pattern = checkers_pattern(color(0.5, 0.5, 0.5), color(0.75, 0.75, 0.75));
	middle.material.pattern.map = texture_map(uv_checkers(16, 8, color(0.5, 0.5, 0.5), color(0.75, 0.75, 0.75)), spherical_map);
	// middle.material.transparency = 1;

	t_shape	cyl = cylinder();
	cyl.cylinder_shape.maximum = 2;
	cyl.cylinder_shape.minimum = -2;
	cyl.material.color = color(0.1, 1, 0.5);
	set_transformation(&cyl, mx_multiply(translation(0, 0, 2), rotation_z(M_PI / 2)));

	// LIGHTS
	t_light	light1 = point_light(point(0, 10, -10), color(1, 1, 1));
	t_light	light2 = point_light(point(0, -10, -10), color(0.7, 0.7, 0.7));

	// CAMERA
	t_camera	camera_view = camera(WIDTH, HEIGHT, M_PI / 3);
	camera_view.transform = view_transform(
		point(0, 1.5, -5),
		point(0, 1, 0),
		vector(0, 1, 0)
	);
	camera_view.inverse = inverse(camera_view.transform);

	t_world	world_to_render = world();

	add_shape(&world_to_render.shape, floor);
	add_shape(&world_to_render.shape, middle);
	// add_shape(&world_to_render.shape, cyl);

	for (int i = 0; i < 5; i++)
		add_shape(&world_to_render.shape, spheres[i]);

	add_light(&world_to_render.light, light1);
	add_light(&world_to_render.light, light2);

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

	int a = write(STDOUT_FILENO, "\033[s", 4);
	(void)a;
	// mlx = mlx_init(WIDTH, HEIGHT, "patterns", false);
	mlx = NULL;
	image = render_image();
	if (mlx)
	{
		mlx_image = canvas_to_image(image, mlx);
		mlx_image_to_window(mlx, mlx_image, 0, 0);
		mlx_loop(mlx);
	}

	canvas_to_ppm(image, "reflection_and_refraction.ppm");
	free(image.pixels);

	a = write(STDOUT_FILENO, "\n", 1);
	(void)a;

	return (0);
}
