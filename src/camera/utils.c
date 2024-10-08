/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:20:12 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/07 20:20:13 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_rendering_progress(int hsize, int vsize, int x, int y)
{
	int		i;
	double	progress;

	progress = ((double)(y * hsize + x)) / ((double)(hsize * vsize)) * 100;
	printf("\r[");
	i = 0;
	while (i < 50)
	{
		if (i < progress / 2)
			printf("=");
		else if (fabs(progress / 2 - i) < 1)
			printf(">");
		else if (i % 5 == 0)
			printf("o");
		else
			printf(" ");
		i++;
	}
	printf("] %.2f%%", progress);
	// fflush(stdout);
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

void	join_threads(pthread_t *threads, int thread_count)
{
	int	i;

	i = 0;
	while (i < thread_count)
	{
		pthread_join(threads[i], NULL);
		i++;
	}
}
