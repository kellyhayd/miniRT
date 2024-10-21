#include "minirt.h"

#define WIDTH 1000
#define HEIGHT 1000

t_canvas	*render_image(void)
{
	// Camera
	t_camera	c_forward = camera(WIDTH, HEIGHT, 70);
	t_camera	c_left = camera(WIDTH, HEIGHT, 70);
	t_camera	c_right = camera(WIDTH, HEIGHT, 70);

	c_forward.transform = view_transform(point(0, 5, -5), point(0, 5, -4), vector(0, 0, 1));
	c_left.transform = view_transform(point(5, 5, 0), point(4, 5, 0), vector(0, 1, 0));
	c_right.transform = view_transform(point(-5, 5, 0), point(-4, 5, 0), vector(0, 1, 0));

	c_forward.inverse = inverse(c_forward.transform);
	c_left.inverse = inverse(c_left.transform);
	c_right.inverse = inverse(c_right.transform);

	// Light
	t_light	light1 = point_light(point(-10, 10, -10), color(1, 1, 1));
	t_light	light2 = point_light(point(10, 10, -10), color(1, 1, 1));
	t_light	light3 = point_light(point(0, 10, -10), color(1, 1, 1));

	// Sphere
	t_shape	sphere1 = sphere();
	set_transformation(&sphere1, translation(0, 5, 10));
	sphere1.material.color = color(1, 1, 1);

	// Planes
	t_shape	plane_floor = plane();
	t_shape	plane_right = plane();
	t_shape	plane_left = plane();
	t_shape	plane_back = plane();
	t_shape	plane_top = plane();

	set_transformation(&plane_floor, translation(0, 0, 0));
	set_transformation(&plane_right, mx_multiply(translation(10, 0, 0), rotation_z(M_PI / 2)));
	set_transformation(&plane_left, mx_multiply(translation(-10, 0, 0), rotation_z(M_PI / 2)));
	set_transformation(&plane_back, mx_multiply(translation(0, 0, 25), rotation_x(M_PI / 2)));
	set_transformation(&plane_top, mx_multiply(translation(0, 15, 0), rotation_x(M_PI)));

	plane_floor.material.pattern = checkers_pattern(color(0, 0, 0), color(1, 1, 1));
	plane_right.material.pattern = checkers_pattern(color(0, 0, 0), color(1, 0, 0));
	plane_left.material.pattern = checkers_pattern(color(0, 0, 0), color(0, 0, 1));
	plane_back.material.pattern = checkers_pattern(color(0, 0, 0), color(1, 1, 0));
	plane_top.material.pattern = checkers_pattern(color(0, 0, 0), color(0, 1, 1));


	// world
	t_world	world_to_render = world();

	// add_shape(&world_to_render.shape, sphere1);
	add_shape(&world_to_render.shape, plane_floor);
	add_shape(&world_to_render.shape, plane_right);
	add_shape(&world_to_render.shape, plane_left);
	add_shape(&world_to_render.shape, plane_back);
	add_shape(&world_to_render.shape, plane_top);

	add_light(&world_to_render.light, light1);
	add_light(&world_to_render.light, light2);
	add_light(&world_to_render.light, light3);

	world_to_render.pixel_sampling = 1;

	t_canvas	canvas_forward = render(c_forward, world_to_render);
	// t_canvas	canvas_left = render(c_left, world_to_render);
	// t_canvas	canvas_right = render(c_right, world_to_render);

	world_clear(&world_to_render);

	t_canvas	*canvas = malloc(sizeof(t_canvas) * 3);
	canvas[0] = canvas_forward;
	// canvas[1] = canvas_left;
	// canvas[2] = canvas_right;

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
	t_canvas	*images;
	mlx_image_t	*mlx_image;

	// t_vector	vec = {0, 1, 1, 1};
	// t_vector	norm = normalize(vec);
	// printf("%f %f %f\n", norm.x, norm.y, norm.z);

	// mlx = mlx_init(WIDTH, HEIGHT, "patterns", false);
	write(STDOUT_FILENO, "\033[s", 4);
	mlx = NULL;
	images = render_image();
	if (mlx)
	{
		mlx_image = canvas_to_image(images[0], mlx);
		mlx_image_to_window(mlx, mlx_image, 0, 0);
		mlx_loop(mlx);
	}

	canvas_to_ppm(images[0], "multi_camera_1.ppm");
	// canvas_to_ppm(images[0], "multi_camera_2.ppm");
	// canvas_to_ppm(images[0], "multi_camera_3.ppm");

	free(images[0].pixels);
	// free(images[1].pixels);
	// free(images[2].pixels);
	free(images);

	return (0);
}
