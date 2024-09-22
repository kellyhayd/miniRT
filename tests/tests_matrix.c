/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:09:01 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/22 16:03:26 by krocha-h         ###   ########.fr       */
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
							// .tab = matrix,
							.rows = 4, .cols = 4
	};
	t_matrix	result;
	int			row_size = 4;
	int			column_size = 4;

	ft_memcpy(expected.tab, matrix, sizeof(double) * row_size * column_size);

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
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_matrix	matrix2 = {
							// .tab = tab2,
							.rows = 4, .cols = 4
	};
	int			result;
	int			expected = 1;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);
	ft_memcpy(matrix2.tab, tab2, sizeof(double) * matrix2.rows * matrix2.cols);

	// ACT
	result = mx_compare(matrix1, matrix2);

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
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_matrix	matrix2 = {
							// .tab = tab2,
							.rows = 4, .cols = 4
	};
	int			result;
	int			expected = 0;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);
	ft_memcpy(matrix2.tab, tab2, sizeof(double) * matrix2.rows * matrix2.cols);

	// ACT
	result = mx_compare(matrix1, matrix2);

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
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_matrix	matrix2 = {
							// .tab = tab2,
							.rows = 4, .cols = 4
	};
	t_matrix	expected = {
							// .tab = result_tab,
							.rows = 4, .cols = 4
	};
	t_matrix	result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);
	ft_memcpy(matrix2.tab, tab2, sizeof(double) * matrix2.rows * matrix2.cols);
	ft_memcpy(expected.tab, result_tab, sizeof(double) * expected.rows * expected.cols);

	// ACT
	result = mx_multiply(matrix1, matrix2);

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
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_tuple		tuple1 = {
		.x = 1, .y = 2, .z = 3, .w = 1
	};
	t_tuple		expected = {
		.x = 18, .y = 24, .z = 33, .w = 1
	};
	t_tuple		result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);

	// ACT
	result = mx_multiply_tuple(matrix1, tuple1);

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
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_matrix	matrix_identity = {
							// .tab = identity,
							.rows = 4, .cols = 4
	};
	t_matrix	expected;
	t_matrix	result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);
	ft_memcpy(matrix_identity.tab, identity, sizeof(double) * matrix_identity.rows * matrix_identity.cols);

	expected = matrix1;

	// ACT
	result = mx_multiply(matrix1, matrix_identity);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_matrix_transpose(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		0, 9, 3, 0,
		9, 8, 0, 8,
		1, 8, 5, 3,
		0, 0, 5, 8
	};
	double		result_tab[] = {
		0, 9, 1, 0,
		9, 8, 8, 0,
		3, 0, 5, 5,
		0, 8, 3, 8
	};

	t_matrix	matrix1 = {
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_matrix	expected = {
							// .tab = result_tab,
							.rows = 4, .cols = 4
	};
	t_matrix	result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);
	ft_memcpy(expected.tab, result_tab, sizeof(double) * expected.rows * expected.cols);

	// ACT
	result = transposing(matrix1);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_matrix_transpose_identity(int num_test)
{
	// ARRANGE
	double		identity[] = {
		1, 0, 0, 0,
		0, 1, 0, 0,
		0, 0, 1, 0,
		0, 0, 0, 1
	};

	t_matrix	matrix_identity = {
							// .tab = identity,
							.rows = 4, .cols = 4
	};
	t_matrix	expected;
	t_matrix	result;

	ft_memcpy(matrix_identity.tab, identity, sizeof(double) * matrix_identity.rows * matrix_identity.cols);

	expected = matrix_identity;

	// ACT
	result = transposing(matrix_identity);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_matrix_determinant_2x2(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		1, 5,
		-3, 2
	};

	t_matrix	matrix1 = {
							// .tab = tab1,
							.rows = 2, .cols = 2
	};
	double		expected = 17;
	double		result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);

	// ACT
	result = determinant(matrix1);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_matrix_determinant_3x3(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		 1,  2,  6,
		-5,  8, -4,
		 2,  6,  4
	};

	t_matrix	matrix1 = {
							// .tab = tab1,
							.rows = 3, .cols = 3
	};
	double		expected = -196;
	double		result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);

	// ACT
	result = determinant(matrix1);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_matrix_determinant_4x4(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		-2, -8,  3,  5,
		-3,  1,  7,  3,
		 1,  2, -9,  6,
		-6,  7,  7, -9
	};

	t_matrix	matrix1 = {
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	double		expected = -4071;
	double		result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);

	// ACT
	result = determinant(matrix1);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_matrix_submatrix_3x3(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		 1,  5,  0,
		-3,  2,  7,
		 0,  6, -3
	};
	double		result_tab[] = {
		-3, 2,
		0,  6
	};

	t_matrix	matrix1 = {
							// .tab = tab1,
							.rows = 3, .cols = 3
	};
	t_matrix	expected = {
							// .tab = result_tab,
							.rows = 2, .cols = 2
	};
	t_matrix	result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);
	ft_memcpy(expected.tab, result_tab, sizeof(double) * expected.rows * expected.cols);

	// ACT
	result = submatrix(matrix1, 0, 2);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_matrix_submatrix_4x4(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		-6,  1,  1,  6,
		-8,  5,  8,  6,
		-1,  0,  8,  2,
		-7,  1, -1,  1
	};
	double		result_tab[] = {
		-6,  1,  6,
		-8,  8,  6,
		-7, -1,  1
	};

	t_matrix	matrix1 = {
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_matrix	expected = {
							// .tab = result_tab,
							.rows = 3, .cols = 3
	};
	t_matrix	result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);
	ft_memcpy(expected.tab, result_tab, sizeof(double) * expected.rows * expected.cols);

	// ACT
	result = submatrix(matrix1, 2, 1);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_matrix_minor(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		3,  5,  0,
		2, -1, -7,
		6,  -1,  5,
	};
	t_matrix	matrix1 = {
							// .tab = tab1,
							.rows = 3, .cols = 3
	};
	double		expected = 25;
	double		result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);

	// ACT
	result = minor(matrix1, 1, 0);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_matrix_cofactor_not_negate(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		3,  5,  0,
		2, -1, -7,
		6,  -1,  5,
	};
	t_matrix	matrix1 = {
							// .tab = tab1,
							.rows = 3, .cols = 3
	};
	double		expected = -12;
	double		result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);

	// ACT
	result = cofactor(matrix1, 0, 0);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_matrix_cofactor_negate(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		3,  5,  0,
		2, -1, -7,
		6,  -1,  5,
	};
	t_matrix	matrix1 = {
							// .tab = tab1,
							.rows = 3, .cols = 3
	};
	double		expected = -25;
	double		result;

	ft_memcpy(matrix1.tab, tab1, sizeof(double) * matrix1.rows * matrix1.cols);

	// ACT
	result = cofactor(matrix1, 1, 0);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_calculating_the_inverse_of_a_matrix(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		-5,  2,  6, -8,
		 1, -5,  1,  8,
		 7,  7, -6, -7,
		 1, -3,  7,  4
	};
	double		result_tab[] = {
		 0.21805,  0.45113,  0.24060, -0.04511,
		-0.80827, -1.45677, -0.44361,  0.52068,
		-0.07895, -0.22368, -0.05263,  0.19737,
		-0.52256, -0.81391, -0.30075,  0.30639
	};

	t_matrix	matrix = {
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_matrix	expected = {
							// .tab = result_tab,
							.rows = 4, .cols = 4
	};
	t_matrix	result;

	ft_memcpy(matrix.tab, tab1, sizeof(double) * matrix.rows * matrix.cols);
	ft_memcpy(expected.tab, result_tab, sizeof(double) * expected.rows * expected.cols);

	// ACT
	result = inverse(matrix);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_calculating_the_inverse_of_another_matrix(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		 8, -5,  9,  2,
		 7,  5,  6,  1,
		-6,  0,  9,  6,
		-3,  0, -9, -4
	};
	double		result_tab[] = {
		-0.15385, -0.15385, -0.28205, -0.53846,
		-0.07692,  0.12308,  0.02564,  0.03077,
		 0.35897,  0.35897,  0.43590,  0.92308,
		-0.69231, -0.69231, -0.76923, -1.92308
	};

	t_matrix	matrix = {
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_matrix	expected = {
							// .tab = result_tab,
							.rows = 4, .cols = 4
	};
	t_matrix	result;

	ft_memcpy(matrix.tab, tab1, sizeof(double) * matrix.rows * matrix.cols);
	ft_memcpy(expected.tab, result_tab, sizeof(double) * expected.rows * expected.cols);

	// ACT
	result = inverse(matrix);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_calculating_the_inverse_of_a_third_matrix(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		 9,  3,  0,  9,
		-5, -2, -6, -3,
		-4,  9,  6,  4,
		-7,  6,  6,  2
	};
	double		result_tab[] = {
		-0.04074, -0.07778,  0.14444, -0.22222,
		-0.07778,  0.03333,  0.36667, -0.33333,
		-0.02901, -0.14630, -0.10926,  0.12963,
		 0.17778,  0.06667, -0.26667,  0.33333
	};

	t_matrix	matrix = {
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_matrix	expected = {
							// .tab = result_tab,
							.rows = 4, .cols = 4
	};
	t_matrix	result;

	ft_memcpy(matrix.tab, tab1, sizeof(double) * matrix.rows * matrix.cols);
	ft_memcpy(expected.tab, result_tab, sizeof(double) * expected.rows * expected.cols);

	// ACT
	result = inverse(matrix);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_multiplying_a_product_by_its_inverse(int num_test)
{
	// ARRANGE
	double		tab1[] = {
		 3, -9,  7,  3,
		 3, -8,  2, -9,
		-4,  4,  4,  1,
		-6,  5, -1,  1
	};
	double		tab2[] = {
		 8,  2,  2,  2,
		 3, -1,  7,  0,
		 7,  0,  5,  4,
		 6, -2,  0,  5
	};

	t_matrix	matrix1 = {
							// .tab = tab1,
							.rows = 4, .cols = 4
	};
	t_matrix	matrix2 = {
							// .tab = tab2,
							.rows = 4, .cols = 4
	};
	t_matrix	matrix3;
	t_matrix	inverse_matrix2;
	t_matrix	result;
	t_matrix	expected = matrix1;

	matrix3 = mx_multiply(matrix1, matrix2);
	inverse_matrix2 = inverse(matrix2);

	// ACT
	result = mx_multiply(matrix3, inverse_matrix2);

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_matrix_create,								// 01
		test_matrix_compare_true,						// 02
		test_matrix_compare_false,						// 03
		test_matrix_multiplying,						// 04
		test_matrix_multiplying_tuple,					// 05
		test_matrix_multiplying_identity,				// 06
		test_matrix_transpose,							// 07
		test_matrix_transpose_identity,					// 08
		test_matrix_determinant_2x2,					// 09
		test_matrix_determinant_3x3,					// 10
		test_matrix_determinant_4x4,					// 11
		test_matrix_submatrix_3x3,						// 12
		test_matrix_submatrix_4x4,						// 13
		test_matrix_minor,								// 14
		test_matrix_cofactor_not_negate,				// 15
		test_matrix_cofactor_negate,					// 16
		test_calculating_the_inverse_of_a_matrix,		// 17
		test_calculating_the_inverse_of_another_matrix,	// 18
		test_calculating_the_inverse_of_a_third_matrix,	// 19
		test_multiplying_a_product_by_its_inverse,		// 20
	};

	printf("\n%sTESTING MATRICES:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
