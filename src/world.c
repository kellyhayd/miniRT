/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:14:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 15:31:50 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world	world(void)
{
	t_world	w;

	w.shape = NULL;
	w.light = point_light(point(0, 0, 0), color(1, 1, 1));
	return (w);
}

t_world	default_world(void)
{
	t_world	w;
	t_shape	s1;
	t_shape	s2;
	t_light	light;

	w.shape = malloc(sizeof(t_shape) * 2);
	s1 = sphere();
	s2 = sphere();
	s1.material.color = color(0.8, 1.0, 0.6);
	s1.material.diffuse = 0.7;
	s1.material.shininess = 0.2;
	s2.transform = scaling(0.5, 0.5, 0.5);
	light = point_light(point(-10, 10, -10), color(1, 1, 1));
	w.light = light;
	w.shape[0] = s1;
	w.shape[1] = s2;
	return (w);
}

// t_hit	*intersect_world(t_world world, t_ray ray)
// {

// }
