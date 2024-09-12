/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:18:05 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/11 23:59:55 by danbarbo         ###   ########.fr       */
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

int	hit_compare_test(void *expected, void *result)
{
	t_hit	*hit_expected = expected;
	t_hit	*hit_result = result;
	t_hit	*aux_expected;
	t_hit	*aux_result;

	if (!hit_expected || hit_result)
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
