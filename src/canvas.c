/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:18:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 15:22:28 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * Converts a t_color structure to an integer representation.
 *
 * @param color The t_color structure containing the color components.
 * @return An integer representing the color.
 */
int	color_to_int(t_color color)
{
	int	r = (int) (color.r * 255.999);
	int	g = (int) (color.g * 255.999);
	int	b = (int) (color.b * 255.999);

	return (r << 16 | g << 8 | b);
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
 * @param color The color to set the pixel to, represented as a t_color structure.
 */
void	write_pixel(mlx_image_t *image, int x, int y, t_color color)
{
	if (x < 0 || x >= (int) image->width || y < 0 || y >= (int) image->height)
		return ;
	mlx_put_pixel(image, (unsigned int) x, (unsigned int) y, color_to_int(color));
}
