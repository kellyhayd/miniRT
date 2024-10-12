/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:14:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/12 11:03:55 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world	world(void)
{
	return ((t_world){
		.light = NULL,
		.shape = NULL,
		.pixel_sampling = 1
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
	comps.inside = false;
	comps.sight.eye = tuple_negate(ray.direction);
	comps.sight.normal = normal_at(comps.object, comps.point);
	comps.sight.in_shadow = false;
	if (dot(comps.sight.normal, comps.sight.eye) < 0)
	{
		comps.inside = true;
		comps.sight.normal = tuple_negate(comps.sight.normal);
	}
	comps.reflectv = reflect(ray.direction, comps.sight.normal);
	comps.over_point = tuple_add(comps.point,
			tuple_multiply(comps.sight.normal, EPSILON)
			);
	return (comps);
}

t_color	shade_hit(t_world world, t_comps comps)
{
	t_color	color_shaded;
	t_light	*aux;
	t_color	color_reflected;

	color_shaded = color(0, 0, 0);
	aux = world.light;
	while (aux)
	{
		comps.sight.in_shadow = is_shadowed(world, comps.over_point, aux);
		color_shaded = color_add(
			color_shaded,
			lighting(
				comps.object,
				*aux,
				comps.point,
				comps.sight
			)
		);
		aux = aux->next;
	}
	color_reflected = reflected_color(world, comps);
	return (color_add(color_shaded, color_reflected));
}

t_color	color_at(t_world w, t_ray r)
{
	t_color	color_at_hit;
	t_comps	comps;
	t_hit	*nearest_hit;
	t_hit	*hits;

	color_at_hit = color(0, 0, 0);
	hits = intersect_world(w, r);
	nearest_hit = hit(hits);
	if (nearest_hit)
	{
		comps = prepare_computations(*nearest_hit, r);
		color_at_hit = shade_hit(w, comps);
	}
	hit_clear_list(&hits);
	return (color_at_hit);
}

t_matrix	view_transform(t_point from, t_point to, t_vector up)
{
	t_vector	forward;
	t_vector	left;
	t_vector	true_up;
	t_matrix	orientation;
	t_matrix	view_matrix;

	forward = normalize(tuple_subtract(to, from));
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
			orientation,
			translation(-from.x, -from.y, -from.z)
			);
	return (view_matrix);
}
