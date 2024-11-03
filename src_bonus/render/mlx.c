/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   mlx.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:32:17 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/31 08:53:35 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"

void	key_hook(mlx_key_data_t keydata, void *param)
{
	mlx_t	*mlx;

	mlx = param;
	if (keydata.key == MLX_KEY_ESCAPE)
		mlx_close_window(mlx);
}

void	start_render(t_world world, int save_to_file, char *file_name)
{
	t_canvas	canvas;
	mlx_t		*mlx;
	mlx_image_t	*image;

	(void)!write(STDOUT_FILENO, "\033[s", 4);
	canvas = render(world.scene.world_camera, world);
	(void)!write(STDOUT_FILENO, "\n", 1);
	mlx_set_setting(MLX_STRETCH_IMAGE, true);
	mlx = mlx_init(WIDTH, HEIGH, "miniRT", true);
	image = canvas_to_image(canvas, mlx);
	mlx_image_to_window(mlx, image, 0, 0);
	mlx_key_hook(mlx, key_hook, mlx);
	mlx_loop(mlx);
	mlx_delete_image(mlx, image);
	mlx_terminate(mlx);
	if (save_to_file)
	{
		(void)!write(STDOUT_FILENO, "Saving:\n\033[s", 12);
		canvas_to_ppm(canvas, file_name);
		(void)!write(STDOUT_FILENO, "\n", 1);
	}
	free(canvas.pixels);
	free(file_name);
}
