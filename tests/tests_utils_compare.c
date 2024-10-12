/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils_compare.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:18:05 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/12 08:40:31 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	float_compare_test(void *expected, void *result)
{
	double	*expected_double = expected;
	double	*result_double = result;

	return (float_compare(*expected_double, *result_double)
		|| (*expected_double == INFINITY && *result_double == INFINITY)
		|| (*expected_double == -INFINITY && *result_double == -INFINITY));
}

int	int_compare_test(void *expected, void *result)
{
	return (*(int *) expected == *(int *) result);
}

int	tuple_compare_test(void *expected, void *result)
{
	t_tuple	*expected_tuple = expected;
	t_tuple	*result_tuple = result;

	return (float_compare(expected_tuple->x, result_tuple->x)
		&& float_compare(expected_tuple->y, result_tuple->y)
		&& float_compare(expected_tuple->z, result_tuple->z)
		&& float_compare(expected_tuple->w, result_tuple->w));
}

int	color_compare_test(void *expected, void *result)
{
	t_color	*color1_color = expected;
	t_color	*color2_color = result;

	return (float_compare(color1_color->r, color2_color->r)
		&& float_compare(color1_color->g, color2_color->g)
		&& float_compare(color1_color->b, color2_color->b));
}

int	matrix_compare_test(void *expected, void *result)
{
	t_matrix	*matrix_expected = expected;
	t_matrix	*matrix_result = result;

	int	i;
	int	size_all;

	if (matrix_expected->rows != matrix_result->rows || matrix_expected->cols != matrix_result->cols)
		return (0);
	i = 0;
	size_all = matrix_expected->rows * matrix_expected->cols;
	while (i < size_all)
	{
		if (!float_compare(matrix_expected->tab[i], matrix_result->tab[i]))
			return (0);
		i++;
	}
	return (1);
}

int	ray_compare_test(void *expected, void *result)
{
	t_ray	*ray_expected = expected;
	t_ray	*ray_result = result;

	if (tuple_compare_test(&ray_expected->origin, &ray_result->origin)
		&& tuple_compare_test(&ray_expected->direction, &ray_result->direction))
		return (1);
	return (0);
}

static int	compare_shape(t_shape *shape_expected, t_shape *shape_result)
{
	if (shape_expected->shape_type == SPHERE)
	{
		if (tuple_compare_test(&shape_expected->sphere_shape.origin, &shape_result->sphere_shape.origin)
			&& float_compare_test(&shape_expected->sphere_shape.radius, &shape_result->sphere_shape.radius))
			return (1);
	}
	else if (shape_expected->shape_type == PLANE)
	{
		if (tuple_compare_test(&shape_expected->plane_shape.origin, &shape_result->plane_shape.origin))
			return (1);
	}
	else if (shape_expected->shape_type == CYLINDER)
	{
		if (tuple_compare_test(&shape_expected->cylinder_shape.origin, &shape_result->cylinder_shape.origin)
			&& float_compare_test(&shape_expected->cylinder_shape.radius, &shape_result->cylinder_shape.radius)
			&& float_compare_test(&shape_expected->cylinder_shape.minimum, &shape_result->cylinder_shape.minimum)
			&& float_compare_test(&shape_expected->cylinder_shape.maximum, &shape_result->cylinder_shape.maximum)
			&& int_compare_test(&shape_expected->cylinder_shape.closed, &shape_result->cylinder_shape.closed))
			return (1);
	}
	else if (shape_expected->shape_type == CONE)
	{
		if (tuple_compare_test(&shape_expected->cone_shape.origin, &shape_result->cone_shape.origin)
			&& float_compare_test(&shape_expected->cone_shape.radius, &shape_result->cone_shape.radius)
			&& float_compare_test(&shape_expected->cone_shape.minimum, &shape_result->cone_shape.minimum)
			&& float_compare_test(&shape_expected->cone_shape.maximum, &shape_result->cone_shape.maximum)
			&& int_compare_test(&shape_expected->cone_shape.closed, &shape_result->cone_shape.closed))
			return (1);
	}
	return (0);
}

int	shape_compare_test(void *expected, void *result)
{
	t_shape	*shape_expected = expected;
	t_shape	*shape_result = result;

	if (shape_expected->shape_type == shape_result->shape_type
		&& compare_shape(shape_expected, shape_result)
		&& matrix_compare_test(&shape_expected->transform, &shape_result->transform)
		&& matrix_compare_test(&shape_expected->inverse, &shape_result->inverse)
		&& matrix_compare_test(&shape_expected->transposed_inverse, &shape_result->transposed_inverse)
		&& material_compare_test(&shape_expected->material, &shape_result->material))
		return (1);
	return (0);
}

int	hit_compare_test(void *expected, void *result)
{
	t_hit	*hit_expected = expected;
	t_hit	*hit_result = result;

	if (!hit_expected || !hit_result)
		return (hit_expected == hit_result);

	if (float_compare_test(&hit_expected->t, &hit_result->t))
		return (1);
	return (0);
}

int	hit_list_compare_test(void *expected, void *result)
{
	t_hit	*hit_expected = expected;
	t_hit	*hit_result = result;
	t_hit	*aux_expected;
	t_hit	*aux_result;

	if (!hit_expected || !hit_result)
		return (hit_expected == hit_result);

	aux_expected = hit_expected;
	aux_result = hit_result;
	while (aux_expected && aux_result && hit_compare_test(&aux_expected, &aux_result))
	{
		aux_expected = aux_expected->next;
		aux_result = aux_result->next;
	}

	return (!aux_expected && !aux_result);
}

int	light_compare_test(void *expected, void *result)
{
	t_light	*light_expected = expected;
	t_light	*light_result = result;

	if (tuple_compare_test(&light_expected->position, &light_result->position)
		&& color_compare_test(&light_expected->intensity, &light_result->intensity))
		return (1);
	return (0);
}

int	material_compare_test(void *expected, void *result)
{
	t_material	*material_expected = expected;
	t_material	*material_result = result;

	if (float_compare_test(&material_expected->ambient, &material_result->ambient)
		&& float_compare_test(&material_expected->diffuse, &material_result->diffuse)
		&& float_compare_test(&material_expected->specular, &material_result->specular)
		&& float_compare_test(&material_expected->shininess, &material_result->shininess)
		&& float_compare_test(&material_expected->reflective, &material_result->reflective)
		&& color_compare_test(&material_expected->color, &material_result->color)
		&& pattern_compare_test(&material_expected->pattern, &material_result->pattern))
		return (1);
	return (0);
}

int	shape_list_compare_test(void *expected, void *result)
{
	t_shape	*shape_expected = expected;
	t_shape	*shape_result = result;
	t_shape	*aux_expected;
	t_shape	*aux_result;

	if (!shape_expected || !shape_result)
		return (shape_expected == shape_result);

	aux_expected = shape_expected;
	aux_result = shape_result;
	while (aux_expected && aux_result && shape_compare_test(aux_expected, aux_result))
	{
		aux_expected = aux_expected->next;
		aux_result = aux_result->next;
	}

	return (!aux_expected && !aux_result);
}

int	light_list_compare_test(void *expected, void *result)
{
	t_light	*light_expected = expected;
	t_light	*light_result = result;
	t_light	*aux_expected;
	t_light	*aux_result;

	if (!light_expected || !light_result)
		return (light_expected == light_result);

	aux_expected = light_expected;
	aux_result = light_result;
	while (aux_expected && aux_result && light_compare_test(aux_expected, aux_result))
	{
		aux_expected = aux_expected->next;
		aux_result = aux_result->next;
	}

	return (!aux_expected && !aux_result);
}

int	world_compare_test(void *expected, void *result)
{
	t_world	*w_expected = expected;
	t_world	*w_result = result;

	if (shape_list_compare_test(w_expected->shape, w_result->shape)
		&& light_list_compare_test(w_result->light, w_expected->light))
		return (1);
	return (0);
}

int	camera_compare_test(void *expected, void *result)
{
	t_camera	*camera_expected = expected;
	t_camera	*camera_result = result;

	if (int_compare_test(&camera_expected->hsize, &camera_result->hsize)
		&& int_compare_test(&camera_expected->vsize, &camera_result->vsize)
		&& float_compare_test(&camera_expected->field_of_view, &camera_result->field_of_view)
		&& float_compare_test(&camera_expected->half_width, &camera_result->half_width)
		&& float_compare_test(&camera_expected->half_height, &camera_result->half_height)
		&& float_compare_test(&camera_expected->pixel_size, &camera_result->pixel_size)
		&& matrix_compare_test(&camera_expected->transform, &camera_result->transform)
		&& matrix_compare_test(&camera_expected->inverse, &camera_result->inverse))
		return (1);
	return (0);
}

int	comps_compare_test(void *expected, void *result)
{
	t_comps	*comps_expected = expected;
	t_comps	*comps_result = result;

	if (float_compare_test(&comps_expected->t, &comps_result->t)
		&& shape_compare_test(&comps_expected->object, &comps_result->object)
		&& tuple_compare_test(&comps_expected->point, &comps_result->point)
		&& tuple_compare_test(&comps_expected->over_point, &comps_result->over_point)
		&& tuple_compare_test(&comps_expected->sight.eye, &comps_result->sight.eye)
		&& tuple_compare_test(&comps_expected->sight.normal, &comps_result->sight.normal)
		&& comps_expected->sight.in_shadow == comps_result->sight.in_shadow
		&& tuple_compare_test(&comps_expected->reflectv, &comps_result->reflectv)
		&& int_compare_test(&comps_expected->inside, &comps_result->inside))
		return (1);
	return (0);
}

int	pattern_compare_test(void *expected, void *result)
{
	t_pattern	*pattern_expected = expected;
	t_pattern	*pattern_result = result;

	if (pattern_expected->pattern_type == pattern_result->pattern_type
		&& pattern_expected->has_pattern == pattern_result->has_pattern
		&& color_compare_test(&pattern_expected->color_a, &pattern_result->color_a)
		&& color_compare_test(&pattern_expected->color_b, &pattern_result->color_b)
		&& matrix_compare_test(&pattern_expected->transform, &pattern_result->transform)
		&& matrix_compare_test(&pattern_expected->inverse, &pattern_result->inverse))
		return (1);
	return (0);
}
