/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:18:05 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/20 21:51:38 by danbarbo         ###   ########.fr       */
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

	if (matrix_expected->row != matrix_result->row || matrix_expected->column != matrix_result->column)
		return (0);
	i = 0;
	size_all = matrix_expected->row * matrix_expected->column;
	while (i < size_all)
	{
		if (matrix_expected->tab[i] != matrix_result->tab[i])
			return (0);
		i++;
	}
	return (1);
}
