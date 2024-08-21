/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:09:01 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/20 22:49:07 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_matrix_create(int num_test)
{
	// ARRANGE
	double		matrix[] = {
		1,    2,    3,    4,
		5.5,  6.5,  7.5,  8.5,
		9,    10,   11,   12,
		13.5, 14.5, 15.5, 16.5
	};
	t_matrix	expected = {
							.tab = matrix,
							.row = 4, .column = 4
	};
	t_matrix	result;
	int			row_size = 4;
	int			column_size = 4;

	// ACT
	result = matrix_create(matrix, row_size, column_size);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_matrix_compare_true(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2
	};
	double		tab2[] = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2
	};

	t_matrix	matrix1 = {
							.tab = tab1,
							.row = 4, .column = 4
	};
	t_matrix	matrix2 = {
							.tab = tab2,
							.row = 4, .column = 4
	};
	int			result;
	int			expected = 1;

	// ACT
	result = matrix_compare(matrix1, matrix2);

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);
}

void	test_matrix_compare_false(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2
	};
	double		tab2[] = {
		2, 3, 4, 5,
		6, 7, 8, 9,
		8, 7, 6, 5,
		4, 3, 2, 1
	};

	t_matrix	matrix1 = {
							.tab = tab1,
							.row = 4, .column = 4
	};
	t_matrix	matrix2 = {
							.tab = tab2,
							.row = 4, .column = 4
	};
	int			result;
	int			expected = 0;

	// ACT
	result = matrix_compare(matrix1, matrix2);

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);
}

void	test_matrix_multiplying(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		1, 2, 3, 4,
		5, 6, 7, 8,
		9, 8, 7, 6,
		5, 4, 3, 2
	};
	double		tab2[] = {
		-2, 1, 2,  3,
		 3, 2, 1, -1,
		 4, 3, 6,  5,
		 1, 2, 7,  8
	};
	double		result_tab[] = {
		20,  22,  50,  48,
		44,  54, 114, 108,
		40,  58, 110, 102,
		16,  26,  46,  42
	};

	t_matrix	matrix1 = {
							.tab = tab1,
							.row = 4, .column = 4
	};
	t_matrix	matrix2 = {
							.tab = tab2,
							.row = 4, .column = 4
	};
	t_matrix	expected = {
							.tab = result_tab,
							.row = 4, .column = 4
	};
	t_matrix	result;

	// ACT
	result = matrix_multiply(matrix1, matrix2);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_matrix_multiplying_tuple(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		1, 2, 3, 4,
		2, 4, 4, 2,
		8, 6, 4, 1,
		0, 0, 0, 1
	};

	t_matrix	matrix1 = {
							.tab = tab1,
							.row = 4, .column = 4
	};
	t_tuple		tuple1 = {
		.x = 1, .y = 2, .z = 3, .w = 1
	};
	t_tuple		expected = {
		.x = 18, .y = 24, .z = 33, .w = 1
	};
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(matrix1, tuple1);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_matrix_multiplying_identity(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		0, 1,  2, 4,
		1, 2,  4, 8,
		2, 4,  8, 16,
		4, 8, 16, 32
	};

	double		identity[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	t_matrix	matrix1 = {
							.tab = tab1,
							.row = 4, .column = 4
	};
	t_matrix	matrix_identity = {
							.tab = identity,
							.row = 4, .column = 4
	};
	t_matrix	expected = matrix1;
	t_matrix	result;

	// ACT
	result = matrix_multiply(matrix1, matrix_identity);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_matrix_create,					// 01
		test_matrix_compare_true,			// 02
		test_matrix_compare_false,			// 03
		test_matrix_multiplying,			// 04
		test_matrix_multiplying_tuple,		// 05
		test_matrix_multiplying_identity,	// 06
	};

	printf("\n%sTESTING MATRICES:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
