/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   canvas.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 18:18:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/11 18:25:51 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	write_pixel(mlx_image_t *image, int x, int y, int color)
{
	if (x < 0 || x >= (int) image->width || y < 0 || y >= (int) image->height)
		return ;
	mlx_put_pixel(image, (unsigned int) x, (unsigned int) y, color);
}
