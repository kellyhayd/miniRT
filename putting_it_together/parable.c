/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parable.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:10:47 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/11 20:16:24 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct projectile
{
	t_point		position;
	t_vector	velocity;
}	projectile;

typedef struct environment
{
	t_vector	gravity;
	t_vector	wind;
}	environment;

projectile	tick(environment env, projectile proj)
{
	projectile	new;

	new.position = tuple_add(proj.position, proj.velocity);
	new.velocity = tuple_add(tuple_add(proj.velocity, env.gravity), env.wind);
	return (new);
}

void	print_big_pixel(mlx_image_t *image, int x, int y, int color)
{
	int	pixel_size = 3;

	x *= pixel_size;
	y *= pixel_size;
	for (int i = x; i < x + pixel_size; i++)
		for (int j = y; j < y + pixel_size; j++)
			write_pixel(image, i, j, color);
}

void	create_parable(mlx_image_t *image)
{
	int			ticks = 0;
	projectile	proj;
	projectile	proj_emulation;
	environment	env;

	proj.position = point(0, 1, 0);
	proj.velocity = tuple_multiply(vector_normalize(vector(1, 1.8, 0)), 6.5);

	env.gravity = vector(0, -0.1, 0);
	env.wind = vector(-0.01, 0, 0);

	proj_emulation = proj;
	while (proj_emulation.position.y > 0)
	{
		proj_emulation = tick(env, proj_emulation);
		print_big_pixel(image, proj_emulation.position.x, proj_emulation.position.y, 0xFFFFFFFF);
		ticks++;
	}
}

int main(void)
{
	mlx_t		*mlx;
	mlx_image_t	*image;

	mlx = mlx_init(900, 500, "parable", false);
	image = mlx_new_image(mlx, 900, 500);
	mlx_image_to_window(mlx, image, 0, 0);
	create_parable(image);
	mlx_loop(mlx);
	return (0);
}
