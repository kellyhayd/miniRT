/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:18:05 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/12 00:36:12 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

int	color_compare(t_color color1, t_color color2)
{
	return (float_compare(color1.r, color2.r)
		&& float_compare(color1.g, color2.g)
		&& float_compare(color1.b, color2.b));
}

void	print_ok(int num_test)
{
	printf(PURPLE "%d" RESET " - " GREEN "[ ✓ ]\n" RESET, num_test);
	// printf("%s%d%s - %s[ ✓ ]%s\n", PURPLE, num_test, RESET, GREEN, RESET);
}

int	float_compare_test(void *expected, void *result)
{
	double	*expected_double = (double *)expected;
	double	*result_double = (double *)result;

	return (float_compare(*expected_double, *result_double));
}

void	print_ko_float(int num_test, void *expected, void *result)
{
	double	*expected_double = (double *)expected;
	double	*result_double = (double *)result;

	printf(PURPLE "%d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: (%.2lf) "
		"Result: (%.2lf)\n", num_test, *expected_double, *result_double
	);
}

// void	print_ko_tuple(int num_test, t_tuple expected, t_tuple result)
// {
// 	printf(PURPLE "%d" RESET " - " RED "[ ✗ ]" RESET
// 		" Expected: (%.2lf, %.2lf, %.2lf, %.2lf) \
// 		RESULT: (%.2lf, %.2lf, %.2lf, %.2lf)\n", \
// 		num_test, expected.x, expected.y, expected.z, expected.w, result.x, result.y, result.z, result.w
// 	);
// }

// void	print_ko_color(int num_test, t_color expected, t_color result)
// {
// 	printf(PURPLE "%d" RESET " - " RED "[ ✗ ] " RESET
// 		"Expected: (%.2lf, %.2lf, %.2lf, %.2lf) "
// 		"RESULT: (%.2lf, %.2lf, %.2lf, %.2lf)\n",
// 		num_test,
// 		expected.r, expected.g, expected.b,
// 		result.r, result.g, result.b
// 	);
// }

// void	print_result(int num_test, int type, ...)
// {
// 	va_list		args;
// 	double		d_result;
// 	double		d_expected;
// 	t_tuple		t_result;
// 	t_tuple		t_expected;
// 	t_color		c_result;
// 	t_color		c_expected;
// 	t_matrix	m_result;
// 	t_matrix	m_expected;
//
// 	va_start(args, type);
// 	if (type == TUPLE)
// 	{
// 		t_expected = va_arg(args, t_tuple);
// 		t_result = va_arg(args, t_tuple);
// 		if (tuple_compare(t_expected, t_result) == 1)
// 			print_ok(num_test);
// 		else
// 			print_ko_tuple(num_test, t_expected, t_result);
// 	}
// 	else if (type == FLOAT)
// 	{
// 		d_expected = va_arg(args, double);
// 		d_result = va_arg(args, double);
// 		if (float_compare(d_expected, d_result) == 1)
// 			print_ok(num_test);
// 		else
// 		{
// 			printf(PURPLE "%d" RESET " - " RED "[ ✗ ]" RESET
// 			" Expected: (%.2lf) RESULT: (%.2lf)\n", num_test, d_expected, d_result);
// 		}
// 	}
// 	else if (type == COLOR)
// 	{
// 		c_expected = va_arg(args, t_color);
// 		c_result = va_arg(args, t_color);
// 		if (color_compare(c_expected, c_result) == 1)
// 			print_ok(num_test);
// 		else
// 			print_ko_color(num_test, c_expected, c_result);
// 	}
// 	else if (type == MATRIX)
// 	{
// 		m_expected = va_arg(args, t_matrix);
// 		m_result = va_arg(args, t_matrix);
// 		if (matrix_compare(m_expected, m_result))
// 			print_ok(num_test);
// 		else
// 			printf(PURPLE "%d" RESET " - " RED "[ ✗ ]\n" RESET, num_test);
// 	}
// 	va_end(args);
// }

void	print_result(int num_test, void *expected, void *result,
						int (*compare)(void *, void *),
						void (*print_ko)(int, void *, void *))
{
	if (compare(expected, result))
		print_ok(num_test);
	else
		print_ko(num_test, expected, result);
}
