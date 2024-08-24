/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:41:13 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/24 17:43:15 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	print_ok(int num_test)
{
	printf(PURPLE "%2d" RESET " - " GREEN "[ ✓ ]\n" RESET, num_test);
	// printf("%s%d%s - %s[ ✓ ]%s\n", PURPLE, num_test, RESET, GREEN, RESET);
}

void	print_result(int num_test, void *expected, void *result,
						int (*compare)(void *, void *),
						void (*print_ko)(int, void *, void *))
{
	if (compare(expected, result))
		print_ok(num_test);
	else
		print_ko(num_test, expected, result);
}

void	print_ko_float(int num_test, void *expected, void *result)
{
	double	*expected_double = expected;
	double	*result_double = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: (%.2lf) "
		"Result: (%.2lf)\n",
		num_test,
		*expected_double,
		*result_double
	);
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

void	print_ko_tuple(int num_test, void *expected, void *result)
{
	t_tuple	*expected_tuple = expected;
	t_tuple	*result_tuple = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: (%.2lf, %.2lf, %.2lf, %.2lf) "
		"Result: (%.2lf, %.2lf, %.2lf, %.2lf)\n",
		num_test,
		expected_tuple->x, expected_tuple->y, expected_tuple->z, expected_tuple->w,
		result_tuple->x, result_tuple->y, result_tuple->z, result_tuple->w
	);
}

void	print_ko_color(int num_test, void *expected, void *result)
{
	t_color	*expected_color = expected;
	t_color	*result_color = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: (%.2lf, %.2lf, %.2lf) "
		"Result: (%.2lf, %.2lf, %.2lf)\n",
		num_test,
		expected_color->r, expected_color->g, expected_color->b,
		result_color->r, result_color->g, result_color->b
	);
}

void	print_ko_matrix(int num_test, void *expected, void *result)
{
	t_matrix	*matrix_expected = expected;
	t_matrix	*matrix_result = result;

	int	size_matrix = matrix_expected->rows * matrix_result->cols;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET"\nExpected: ( ", num_test);
	for (int i = 0; i < size_matrix; i++)
		printf("%.2lf ", matrix_expected->tab[i]);
	printf(")\n");

	printf("Result:   ( ");
	for (int i = 0; i < size_matrix; i++)
		printf("%.2lf ", matrix_result->tab[i]);
	printf(")\n");
}
