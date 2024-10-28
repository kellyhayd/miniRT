#include "minirt.h"

// #define WIDTH 1000
// #define HEIGHT 1000

t_matrix	get_mat(t_matrix scale, t_matrix rotate, t_matrix translate)
{
	t_matrix	result;

	result = mx_multiply(
		mx_multiply(
			scale,
			rotate
		),
		translate
	);
	return (result);
}

t_canvas	render_image(void)
{
	// WALLS
	// t_shape	floor = plane();
	// set_transformation(&floor, mx_multiply(rotation_x(90 * M_PI / 180), translation(0, 5, 0)));

	// OBJECTS
	t_shape	middle = cone();
	set_transformation(&middle, get_mat(scaling(1, 1, 1), rotation_y(90 * M_PI / 180), translation(1, 0, 0)));
	middle.material.color = color(1, 0, 0);
	middle.cone_shape.minimum = -5;
	middle.cone_shape.maximum = 5;
	middle.cone_shape.closed = true;
	middle.material.transparency = 1;

	t_shape	origin_y = cylinder();
	// origin_y.material.transparency = 1;
	origin_y.material.color = color(1, 1, 1);
	origin_y.cylinder_shape.maximum = 10;
	origin_y.cylinder_shape.minimum = -10;
	origin_y.cylinder_shape.closed = true;
	t_shape	origin_x = origin_y;
	t_shape	origin_z = origin_y;
	set_transformation(&origin_y, scaling(0.1, 1, 0.1));
	set_transformation(&origin_x, mx_multiply(scaling(1, 0.1, 0.1), rotation_z(90 * M_PI / 180)));
	set_transformation(&origin_z, mx_multiply(scaling(0.1, 0.1, 1), rotation_x(90 * M_PI / 180)));
	origin_x.material.color = color(0, 1, 0);

	// LIGHTS
	t_light	light1 = point_light(point(0, 20, -20), color(1, 1, 1));
	t_light	light2 = point_light(point(0, -20, -20), color(1, 1, 1));

	// CAMERA
	t_camera	camera_view = camera(WIDTH, HEIGH, M_PI / 3);
	camera_view.transform = view_transform(
		point(20, 10, -20),
		point(0, 0, 0),
		vector(0, 1, 0)
	);
	camera_view.inverse = inverse(camera_view.transform);

	t_world	world_to_render = world();

	// add_shape(&world_to_render.shape, floor);
	add_shape(&world_to_render.shape, middle);
	add_shape(&world_to_render.shape, origin_y);
	add_shape(&world_to_render.shape, origin_x);
	add_shape(&world_to_render.shape, origin_z);

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

	canvas_to_ppm(image, "teste_parse_rotation.ppm");
	free(image.pixels);

	(void)!write(STDOUT_FILENO, "\n", 1);

	return (0);
}
