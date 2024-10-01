#include "minirt.h"

mlx_image_t	*render_image(mlx_t *mlx)
{
	// WALLS
	t_shape	floor = sphere();
	set_transformation(&floor, scaling(10, 0.01, 10));
	floor.material.color = color(1, 0.9, 0.9);
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
	right.material.color = color(0.5, 1, 0.1);
	right.material.diffuse = 0.7;
	right.material.specular = 0.3;

	t_shape	left = sphere();
	set_transformation(&left,
		mx_multiply(
			translation(-1.5, 0.33, -0.75),
			scaling(0.33, 0.33, 0.33)
		)
	);
	left.material.color = color(1, 0.8, 0.1);
	left.material.diffuse = 0.7;
	left.material.specular = 0.3;

	// LIGHTS
	t_light	light1 = point_light(point(-10, 10, -10), color(1, 1, 1));
	// t_light	light2 = point_light(point(10, 10, -10), color(1, 1, 1));
	// t_light	light3 = point_light(point(10, -10, 10), color(1, 1, 1));

	// CAMERA
	t_camera	camera_view = camera(720, 720, M_PI / 3);
	camera_view.transform = view_transform(
		point(0, 1.5, -5),
		point(0, 1, 0),
		vector(0, 1, 0)
	);

	t_world	world_to_render = world();

	add_shape(&world_to_render.shape, floor);
	add_shape(&world_to_render.shape, left_wall);
	add_shape(&world_to_render.shape, right_wall);
	add_shape(&world_to_render.shape, middle);
	add_shape(&world_to_render.shape, right);
	add_shape(&world_to_render.shape, left);

	add_light(&world_to_render.light, light1);
	// add_light(&world_to_render.light, light2);
	// add_light(&world_to_render.light, light3);

	world_to_render.mlx = mlx;

	t_canvas	canvas = render(camera_view, world_to_render);

	return (canvas_to_image(canvas, mlx));
}

int main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(720, 720, "sphere", false);

	image = render_image(mlx);
	mlx_image_to_window(mlx, image, 0, 0);

	mlx_loop(mlx);
	return (0);
}
