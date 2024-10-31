/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/07 20:20:12 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/30 18:35:38 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

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
	fflush(stdout);
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

int	reset_threads(pthread_t *threads, int thread_count)
{
	if (thread_count >= NUM_THREADS)
	{
		join_threads(threads, NUM_THREADS);
		return (0);
	}
	return (thread_count);
}
