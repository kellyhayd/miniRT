/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_transformation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:31:05 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/31 14:04:34 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_transformation_translation(int num_test)
{
	// ARRANGE
	t_matrix	translation = matrix_translation(5, -3, 2);
	t_tuple		p = point(-3, 4, 5);
	t_tuple		expected = point(2, 1, 7);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(translation, p);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_scaling_point(int num_test)
{
	// ARRANGE
	t_matrix	scaling = matrix_scaling(2, 3, 4);
	t_tuple		p = point(-4, 6, 8);
	t_tuple		expected = point(-8, 18, 32);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(scaling, p);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_scaling_vector(int num_test)
{
	// ARRANGE
	t_matrix	scaling = matrix_scaling(2, 3, 4);
	t_tuple		v = vector(-4, 6, 8);
	t_tuple		expected = vector(-8, 18, 32);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(scaling, v);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_scaling_vector_inverse(int num_test)
{
	// ARRANGE
	t_matrix	scaling = matrix_scaling(2, 3, 4);
	t_matrix	inverse = matrix_inverse(scaling);
	t_tuple		v = vector(-4, 6, 8);
	t_tuple		expected = vector(-2, 2, 2);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(inverse, v);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_scaling_negative(int num_test)
{
	// ARRANGE
	t_matrix	scaling = matrix_scaling(-1, -1, -1);
	t_tuple		v = vector(-4, 6, 8);
	t_tuple		expected = vector(4, -6, -8);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(scaling, v);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_transformation_translation,			// 01
		test_transformation_scaling_point,			// 02
		test_transformation_scaling_vector,			// 03
		test_transformation_scaling_vector_inverse,	// 04
		test_transformation_scaling_negative,		// 05
	};

	printf("\n%sTESTING TRANFORMATION:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
