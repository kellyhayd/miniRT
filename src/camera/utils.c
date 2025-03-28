/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:20:12 by danbarbo          #+#    #+#             */
/*   Updated: 2024/11/03 14:39:54 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"
#include "minirt.h"

void	print_rendering_progress(int hsize, int vsize, int y)
{
	int	i;
	int	progress;

	progress = (((y + 1) * hsize * 100) / (hsize * vsize));
	printf("\033[uProgress: [");
	i = 0;
	while (i < 50)
	{
		if (i < progress / 2)
			printf("=");
		else if (abs((progress / 2) - i) < 1)
			printf(">");
		else if (i % 5 == 0)
			printf("o");
		else
			printf(" ");
		i++;
	}
	printf("] %d%%", progress);
}

t_color	color_average(t_color *colors, int size)
{
	int		i;
	double	r;
	double	g;
	double	b;
	t_color	average;

	r = 0;
	g = 0;
	b = 0;
	i = 0;
	while (i < size)
	{
		r += colors[i].r;
		g += colors[i].g;
		b += colors[i].b;
		i++;
	}
	average = color(r / size, g / size, b / size);
	return (average);
}
