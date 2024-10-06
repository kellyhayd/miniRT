#include "minirt.h"

#define WIDTH 1000
#define HEIGHT 1000

t_canvas	render_image(void)
{
	// WALLS
	t_shape	floor = plane();
	floor.material.pattern = gradient_pattern(color(1, 1, 0), color(0, 1, 1));
	set_pattern_transformation(&floor.material.pattern, mx_multiply(scaling(2, 2, 2), rotation_y(30 * M_PI / 180)));
	floor.material.color = color(0.3, 0.3, 0.3);

	// SPHERES
	t_shape	middle = sphere();
	middle.material.color = color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;
	middle.material.pattern = gradient_pattern(color(1, 1, 0), color(1, 0, 0));

	t_shape	spheres[5] = {
		middle,
		middle,
		middle,
		middle,
		middle
	};

	for (int i = 0; i < 5; i++)
	{
		set_transformation(&spheres[i], mx_multiply(translation(-2 + i, 1, 0), scaling(0.5, 0.5, 0.5)));
		set_pattern_transformation(&spheres[i].material.pattern, mx_multiply(translation(abs(i) * 0.1, 0, 0), scaling(1.5, 1.5, 1.5)));
	}

	// LIGHTS
	t_light	light1 = point_light(point(-10, 10, -10), color(1, 1, 1));

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

	for (int i = 0; i < 5; i++)
		add_shape(&world_to_render.shape, spheres[i]);

	add_light(&world_to_render.light, light1);

	t_canvas	canvas = render(camera_view, world_to_render);

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
}

int main(void)
{
	mlx_t		*mlx;
	t_canvas	image;
	mlx_image_t	*mlx_image;

	mlx = mlx_init(WIDTH, HEIGHT, "patterns", false);
	image = render_image();
	if (mlx)
	{
		mlx_image = canvas_to_image(image, mlx);
		mlx_image_to_window(mlx, mlx_image, 0, 0);
		mlx_loop(mlx);
	}

	canvas_to_ppm(image, "patterns.ppm");

	return (0);
}