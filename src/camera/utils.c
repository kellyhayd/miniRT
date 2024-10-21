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

t_matrix	view_transform(t_point from, t_point to, t_vector up)
{
	t_vector	forward;
	t_vector	left;
	t_vector	true_up;
	t_matrix	orientation;
	t_matrix	view_matrix;

	forward = normalize(tuple_subtract(to, from));
	if (fmod(fabs(dot(forward, up)), 1) < EPSILON)
		left = vector(-1, 0, 0);
	else
		left = cross(forward, normalize(up));
	true_up = cross(left, forward);
	orientation = identity();
	mx_set(&orientation, 0, 0, left.x);
	mx_set(&orientation, 0, 1, left.y);
	mx_set(&orientation, 0, 2, left.z);
	mx_set(&orientation, 1, 0, true_up.x);
	mx_set(&orientation, 1, 1, true_up.y);
	mx_set(&orientation, 1, 2, true_up.z);
	mx_set(&orientation, 2, 0, -forward.x);
	mx_set(&orientation, 2, 1, -forward.y);
	mx_set(&orientation, 2, 2, -forward.z);
	view_matrix = mx_multiply(
			orientation, translation(-from.x, -from.y, -from.z));
	return (view_matrix);
}
