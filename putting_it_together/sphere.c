#include "minirt.h"

void	create_sphere(mlx_image_t *image)
{
	// Forms and colors
	// t_color	red = color(1, 0, 0);
	t_shape	s = sphere();
	s.material = material();
	s.material.color = color(1, 0.2, 1);
	s.material.specular = 0.9;
	s.material.shininess = 30;

	// Light
	t_point	light_position = point(-10, 10, -10);
	t_color	light_color = color(1, 1, 1);
	t_light	light = point_light(light_position, light_color);

	// Ray
	t_tuple	ray_origin = point(0, 0, -5);
	t_ray	ray_to_wall;
	t_hit	*hit_list = NULL;

	// Canvas
	double	wall_position_z = 5;
	double	wall_size = 10;
	double	canvas_pixel_world_size = wall_size / 720;
	double	world_x;
	double	world_y;
	double	half = wall_size / 2;
	t_point	wall_point;

	// Utils
	t_point		hit_point;
	t_color		color;
	t_sight		sight;

	t_matrix	scale_matrix = scaling(2, 2, 2);
	set_transformation(&s, scale_matrix);

	for (int y = 0; y < 720; y++)
	{
		printf("Linha %i\n", y);
		for (int x = 0; x < 720; x++)
		{
			world_x = -half + x * canvas_pixel_world_size;
			world_y = half - y * canvas_pixel_world_size;

			wall_point = point(world_x, world_y, wall_position_z);
			ray_to_wall = ray(ray_origin, normalize(tuple_subtract(wall_point, ray_origin)));

			intersect(&hit_list, s, ray_to_wall);
			if (hit_list)
			{
				hit_point = position(ray_to_wall, hit_list->t);
				sight.normal = normal_at(hit_list->object, hit_point);
				sight.eye = normalize(tuple_negate(ray_to_wall.direction));
				color = lighting(hit_list->object.material, light, hit_point, sight);
				write_pixel(image, x, y, color);
			}
			hit_clear_list(&hit_list);
		}
	}
}

int main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(720, 720, "sphere", false);
	image = mlx_new_image(mlx, 720, 720);
	mlx_image_to_window(mlx, image, 0, 0);
	create_sphere(image);
	mlx_loop(mlx);
	return (0);
}
