/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world_bonus.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:14:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:56:12 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_bonus.h"

t_world	world(void)
{
	return ((t_world){
		.light = NULL,
		.shape = NULL,
		.scene = {
			.ambient_color = color(1, 1, 1),
			.ambient_ratio = 0.1,
			.world_camera = {0},
			.pixel_sampling = PIXEL_SAMPLING,
			.has_ambient_color = 0,
			.has_camera = 0,
			.pattern_list = NULL,
			.material_list = NULL
		}
	});
}

void	world_clear(t_world *world_to_clear)
{
	shape_clear_list(&world_to_clear->shape);
	light_clear_list(&world_to_clear->light);
}

t_world	default_world(void)
{
	t_world	dfl_world;
	t_shape	sphere1;
	t_shape	sphere2;
	t_light	light1;

	dfl_world = world();
	light1 = point_light(point(-10, 10, -10), color(1, 1, 1));
	add_light(&dfl_world.light, light1);
	sphere1 = sphere();
	sphere2 = sphere();
	sphere1.material.color = color(0.8, 1.0, 0.6);
	sphere1.material.diffuse = 0.7;
	sphere1.material.specular = 0.2;
	set_transformation(&sphere2, scaling(0.5, 0.5, 0.5));
	add_shape(&dfl_world.shape, sphere1);
	add_shape(&dfl_world.shape, sphere2);
	return (dfl_world);
}

t_hit	*intersect_world(t_world w, t_ray ray)
{
	t_hit	*hit_list;
	t_shape	*aux;

	hit_list = NULL;
	aux = w.shape;
	while (aux)
	{
		intersect(&hit_list,
			*aux,
			ray);
		aux = aux->next;
	}
	return (hit_list);
}
