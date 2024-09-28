/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils_compare.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:18:05 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 21:45:51 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	float_compare_test(void *expected, void *result)
{
	double	*expected_double = expected;
	double	*result_double = result;

	return (float_compare(*expected_double, *result_double));
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

int	shape_compare_test(void *expected, void *result)
{
	t_shape	*shape_expected = expected;
	t_shape	*shape_result = result;

	if (float_compare_test(&shape_expected->sphere_shape.origin.x, &shape_result->sphere_shape.origin.x)
		&& float_compare_test(&shape_expected->sphere_shape.origin.y, &shape_result->sphere_shape.origin.y)
		&& float_compare_test(&shape_expected->sphere_shape.origin.z, &shape_result->sphere_shape.origin.z)
		&& float_compare_test(&shape_expected->sphere_shape.radius, &shape_result->sphere_shape.radius)
		&& matrix_compare_test(&shape_expected->transform, &shape_result->transform)
		&& material_compare_test(&shape_expected->material, &shape_result->material))
		// if (shape_expected->shape_type == SPHERE)
			// return (sphere_compare_test(shape_expected, shape_result));
		return (1);
	return (0);
}

int	hit_compare_test(void *expected, void *result)
{
	t_hit	*hit_expected = expected;
	t_hit	*hit_result = result;

	if (!hit_expected || !hit_result)
		return (hit_expected == hit_result);

	if (float_compare_test(&hit_expected->t, &hit_result->t)
		&& shape_compare_test(&hit_expected->object, &hit_result->object))
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
	while (aux_expected && aux_result && float_compare_test(&aux_expected->t, &aux_result->t))
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
		&& color_compare_test(&material_expected->color, &material_result->color))
		return (1);
	return (0);
}

int	world_compare_test(void *expected, void *result)
{
	t_world	*w_expected = expected;
	t_world	*w_result = result;
	int		i = 0;

	if (tuple_compare_test(&w_expected->light.position, &w_result->light.position)
		&& color_compare_test(&w_expected->light.intensity, &w_result->light.intensity)
		&& int_compare_test(&w_expected->shape_nb, &w_result->shape_nb))
	{
		while (i < w_expected->shape_nb)
		{
			if (!shape_compare_test(&w_expected->shape[i], &w_result->shape[i]))
				return (0);
			i++;
		}
		return (1);
	}
	return (0);
}
