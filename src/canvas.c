/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:18:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/05 08:47:55 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Converts a normalized color value to an 8-bit color value.
 *
 * This function takes a color value in the range [0, 1] and converts it to
 * an 8-bit color value in the range [0, 255]. If the input color value is
 * greater than 1, it returns 255. Otherwise, it scales the color value by 255.
 *
 * @param color_value The normalized color value to be converted.
 * @return The 8-bit color value.
 */
static int	convert(double color_value)
{
	if (color_value > 1)
		color_value = 1;
	color_value *= 255 + 0.5;
	return ((int) color_value & 0xFF);
}

/**
 * Converts a t_color structure to an integer representation.
 *
 * @param color The t_color structure containing the color components.
 * @return An integer representing the color.
 */
int	color_to_int(t_color color)
{
	int	color_int;

	color_int = convert(color.r) << 24
		| convert(color.g) << 16
		| convert(color.b) << 8
		| 0xFF;
	return (color_int);
}

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
