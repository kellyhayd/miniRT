/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:14:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/29 18:19:15 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world	world(void)
{
	return ((t_world) {0});
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
		intersect(&hit_list, *aux, ray);
		aux = aux->next;
	}
	return (hit_list);
}

t_comps	prepare_computations(t_hit hit, t_ray ray)
{
	t_comps	comps;

	comps.t = hit.t;
	comps.object = hit.object;
	comps.point = position(ray, comps.t);
	comps.sight.eye = tuple_negate(ray.direction);
	comps.sight.normal = normal_at(comps.object, comps.point);
	comps.inside = false;
	if (dot(comps.sight.normal, comps.sight.eye) < 0)
	{
		comps.inside = true;
		comps.sight.normal = tuple_negate(comps.sight.normal);
	}
	comps.over_point = tuple_add(comps.point, \
			tuple_multiply(comps.sight.normal, EPSILON));
	return (comps);
}

t_color	shade_hit(t_world world, t_comps comps)
{
	t_color	color_shaded;
	t_light	*aux;

	color_shaded = color(0, 0, 0);
	aux = world.light;
	while (aux)
	{
		comps.sight.in_shadow = is_shadowed(world, comps.over_point);
		color_shaded = color_add(
			color_shaded,
			lighting(
				comps.object.material,
				*aux,
				comps.point,
				comps.sight
			)
		);
		aux = aux->next;
	}
	return (color_shaded);
}
