#include "minirt.h"

#define WIDTH 500
#define HEIGHT 500

t_canvas	render_image(void)
{
	// WALLS
	t_shape	floor = sphere();
	set_transformation(&floor, scaling(10, 0.01, 10));
	floor.material.color = color(0.3, 0.3, 0.3);
	floor.material.specular = 0;

	t_shape	left_wall = sphere();
	set_transformation(&left_wall,
		mx_multiply(
			mx_multiply(
				mx_multiply(
					translation(0, 0, 5),
					rotation_y(-M_PI_4)
				),
				rotation_x(M_PI_2)
			),
			scaling(10, 0.01, 10)
		)
	);
	left_wall.material = floor.material;

	t_shape	right_wall = sphere();
	set_transformation(&right_wall,
		mx_multiply(
			mx_multiply(
				mx_multiply(
					translation(0, 0, 5),
					rotation_y(M_PI_4)
				),
				rotation_x(M_PI_2)
			),
			scaling(10, 0.01, 10)
		)
	);
	right_wall.material = floor.material;

	// SPHERES
	t_shape	middle = sphere();
	set_transformation(&middle, translation(-0.5, 1, 0.5));
	middle.material.color = color(0.1, 1, 0.5);
	middle.material.diffuse = 0.7;
	middle.material.specular = 0.3;

	t_shape	right = sphere();
	set_transformation(&right,
		mx_multiply(
			translation(1.5, 0.5, -0.5),
			scaling(0.5, 0.5, 0.5)
		)
	);
	right.material.color = color(1, 1, 1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;

	t_shape	left = sphere();
	set_transformation(&left,
		mx_multiply(
			translation(-1.5, 0.33, -0.75),
			scaling(0.33, 0.33, 0.33)
		)
	);
	left.material.color = color(1, 1, 1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	// LIGHTS
	t_light	light1 = point_light(point(-10, 10, -10), color(1, 0, 0));

	t_point	light_point = mx_multiply_tuple(
		rotation_y(-(M_PI / 4)),
		point(-10, 10, -10)
	);
	t_light	light2 = point_light(light_point, color(0, 1, 0));

	light_point = mx_multiply_tuple(
		rotation_y(-(M_PI / 4)),
		light_point
	);
	t_light	light3 = point_light(light_point, color(0, 0, 1));

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
	add_shape(&world_to_render.shape, left_wall);
	add_shape(&world_to_render.shape, right_wall);
	add_shape(&world_to_render.shape, middle);
	add_shape(&world_to_render.shape, right);
	add_shape(&world_to_render.shape, left);

	add_light(&world_to_render.light, light1);
	add_light(&world_to_render.light, light2);
	add_light(&world_to_render.light, light3);

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

	mlx = mlx_init(WIDTH, HEIGHT, "sphere", false);
	image = render_image();
	if (mlx)
	{
		mlx_image = canvas_to_image(image, mlx);
		mlx_image_to_window(mlx, mlx_image, 0, 0);
		mlx_loop(mlx);
	}

	canvas_to_ppm(image, "many_spheres.ppm");

	return (0);
}
