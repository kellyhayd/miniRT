/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:18:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/31 08:43:21 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tuples.h"
#include "scene.h"

/**
 * @brief Writes a pixel to the specified coordinates in the given image.
 *
 * This function sets the color of the pixel at the (x, y) coordinates in the
 * provided image to the specified color.
 *
 * @param image Pointer to the mlx_image_t structure representing the image.
 * @param x The x-coordinate of the pixel to be written.
 * @param y The y-coordinate of the pixel to be written.
 * @param color The color to set the pixel to, represented as a t_color
 * structure.
 */
void	write_pixel(mlx_image_t *image, int x, int y, t_color color)
{
	if (x < 0 || x >= (int) image->width || y < 0 || y >= (int) image->height)
		return ;
	mlx_put_pixel(image, (unsigned int)x, (unsigned int)y, color_to_int(color));
}

t_canvas	create_canvas(int width, int height)
{
	t_canvas	canvas;

	canvas.width = width;
	canvas.height = height;
	canvas.pixels = (t_color *)malloc(sizeof(t_color) * width * height);
	ft_bzero(canvas.pixels, sizeof(t_color) * width * height);
	if (!canvas.pixels)
	{
		perror("Error allocating memory for canvas pixels");
		exit(EXIT_FAILURE);
	}
	return (canvas);
}

void	write_pixel_to_canvas(t_canvas *canvas, int x, int y, t_color color)
{
	if (x < 0 || x >= canvas->width || y < 0 || y >= canvas->height)
		return ;
	canvas->pixels[y * canvas->width + x] = color;
}

t_color	pixel_at(t_canvas canvas, int x, int y)
{
	if (x < 0 || x >= canvas.width || y < 0 || y >= canvas.height)
		return (color(0, 0, 0));
	return (canvas.pixels[y * canvas.width + x]);
}

mlx_image_t	*canvas_to_image(t_canvas canvas, mlx_t *mlx)
{
	mlx_image_t	*image;
	int			x;
	int			y;

	image = mlx_new_image(mlx, canvas.width, canvas.height);
	if (!image)
	{
		perror("Error creating image from canvas");
		exit(EXIT_FAILURE);
	}
	y = 0;
	while (y < canvas.height)
	{
		x = 0;
		while (x < canvas.width)
		{
			write_pixel(image, x, y, pixel_at(canvas, x, y));
			x++;
		}
		y++;
	}
	return (image);
}
