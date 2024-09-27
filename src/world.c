/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:14:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 21:43:23 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world	world(void)
{
	t_world	w;

	ft_bzero(&w, sizeof(t_world));
	w.light = point_light(point(0, 0, 0), color(1, 1, 1));
	return (w);
}

t_world	default_world(void)
{
	t_world	w;

	w = world();
	w.shape = malloc(sizeof(t_shape) * 2);
	if (w.shape == NULL)
	{
		printf("Memory allocation failed\n");
		exit(EXIT_FAILURE);
	}
	w.shape_nb = 2;
	w.shape[0] = sphere();
	w.shape[0].material.color = color(0.8, 1.0, 0.6);
	w.shape[0].material.diffuse = 0.7;
	w.shape[0].material.shininess = 0.2;
	w.shape[1] = sphere();
	set_transformation(&w.shape[1], scaling(0.5, 0.5, 0.5));
	w.light = point_light(point(-10, 10, -10), color(1, 1, 1));
	return (w);
}

// t_hit	*intersect_world(t_world w, t_ray ray)
// {
// 	t_hit	*hit_list;
// 	int		i;

// 	hit_list = NULL;
// 	i = 0;
// 	while (i < w.shape_nb)
// 	{
// 		intersect(&hit_list, w.shape[i], ray);
// 		i++;
// 	}
// 	return (hit_list);
// }
