/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:09:01 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/11 23:49:45 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

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
	print_result(num_test, MATRIX, expected, result);
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
	print_result(num_test, FLOAT, (double)expected, (double)result);
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
	print_result(num_test, FLOAT, (double)expected, (double)result);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_matrix_create,
		test_matrix_compare_true,
		test_matrix_compare_false,
	};

	printf("\n%sTESTING MATRICES:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
