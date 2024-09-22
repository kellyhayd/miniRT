#include "minirt.h"

void	create_sphere(mlx_image_t *image)
{
	t_color	red = color(1, 0, 0);
	t_shape	red_sphere = sphere();

	t_tuple	ray_origin = point(0, 0, -5);
	double	wall_position_z = 5;
	double	wall_size = 10;

	double	canvas_pixel_world_size = wall_size / 720;
	double	world_x;
	double	world_y;
	double	half = wall_size / 2;
	t_point	wall_point;
	t_ray	ray_to_wall;
	t_hit	*hit_list = NULL;

	t_matrix	scale_matrix = scaling(2, 2, 2);
	// t_matrix	rotating_matrix = matrix_rotation_x(3.14159265358979323846 / 4);
	// t_matrix	result = matrix_multiply(scale_matrix, rotating_matrix);
	set_transformation(&red_sphere, scale_matrix);

	for (int y = 0; y < 720; y++)
	{
		printf("Linha %i\n", y);
		for (int x = 0; x < 720; x++)
		{
			world_x = -half + x * canvas_pixel_world_size;
			world_y = half - y * canvas_pixel_world_size;

			wall_point = point(world_x, world_y, wall_position_z);
			ray_to_wall = ray(ray_origin, normalize(tuple_subtract(wall_point, ray_origin)));

			intersect(&hit_list, red_sphere, ray_to_wall);

			if (hit_list)
			{
				if (world_x * world_x + world_y * world_y > 2)
					write_pixel(image, x, y, 0x00FF00FF);
			}
			hit_clear_list(&hit_list);
		}
	}
}

int main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(720, 720, "shadow", false);
	image = mlx_new_image(mlx, 720, 720);
	mlx_image_to_window(mlx, image, 0, 0);
	create_sphere(image);
	mlx_loop(mlx);
	return (0);
}
