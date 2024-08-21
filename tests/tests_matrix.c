/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:09:01 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/20 21:13:12 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	test_matrix_compare(void *expected, void *result)
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

int	test_int_compare(void *expected, void *result)
{
	return (*(int *) expected == *(int *) result);
}

void	print_ko_matrix(int num_test, void *expected, void *result)
{
	t_matrix	*matrix_expected = expected;
	t_matrix	*matrix_result = result;

	int	size_matrix = matrix_expected->row * matrix_result->column;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET"\nExpected: ( ", num_test);
	for (int i = 0; i < size_matrix; i++)
		printf("%.2lf ", matrix_expected->tab[i]);
	printf(")\n");

	printf("Result:   ( ");
	for (int i = 0; i < size_matrix; i++)
		printf("%.2lf ", matrix_result->tab[i]);
	printf(")\n");
}

void	print_ko_int(int num_test, void *expected, void *result)
{
	int	*expected_int = expected;
	int	*result_int = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: (%d) "
		"Result: (%d)\n",
		num_test,
		*expected_int,
		*result_int
	);
}

void	test_matrix_create(int num_test)
{
	// ARRANGE
	double		matrix[] = {1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5};
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
	print_result(num_test, &expected, &result, test_matrix_compare, print_ko_matrix);
}

void	test_matrix_compare_true(int num_test)
{
	// ARRANGE
	double		tab1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
	double		tab2[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};

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
	print_result(num_test, &expected, &result, test_int_compare, print_ko_int);
}

void	test_matrix_compare_false(int num_test)
{
	// ARRANGE
	double		tab1[] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2};
	double		tab2[] = {2, 3, 4, 5, 6, 7, 8, 9, 8, 7, 6, 5, 4, 3, 2, 1};


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
	print_result(num_test, &expected, &result, test_int_compare, print_ko_int);
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
	print_result(num_test, &expected, &result, test_matrix_compare, print_ko_matrix);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_matrix_create,
		test_matrix_compare_true,
		test_matrix_compare_false,
		test_matrix_multiplying,
	};

	printf("\n%sTESTING MATRICES:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
