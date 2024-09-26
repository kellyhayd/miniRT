/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:18:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/25 22:33:57 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	color_to_int(t_color color)
{
	int	r = (int) (color.r * 255.999);
	int	g = (int) (color.g * 255.999);
	int	b = (int) (color.b * 255.999);

	return (r << 16 | g << 8 | b);
}

void	write_pixel(mlx_image_t *image, int x, int y, t_color color)
{
	if (x < 0 || x >= (int) image->width || y < 0 || y >= (int) image->height)
		return ;
	mlx_put_pixel(image, (unsigned int) x, (unsigned int) y, color_to_int(color));
}
