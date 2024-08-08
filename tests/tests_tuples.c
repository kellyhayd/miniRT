/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_tuples.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:32:15 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/07 22:03:59 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdarg.h>

#define TUPLE 1
#define FLOAT 2

void	print_ok(int num_test)
{
	printf(PURPLE "%d" RESET " - " GREEN "[ ✓ ]\n" RESET, num_test);
}

void	print_ko(int num_test, t_tuple expected, t_tuple result)
{
	printf(PURPLE "%d" RESET " - " RED "[ ✗ ]" RESET
	" Expected: (%.2lf, %.2lf, %.2lf, %.2lf) \
	RESULT: (%.2lf, %.2lf, %.2lf, %.2lf)\n", \
	num_test, expected.x, expected.y, expected.z, expected.w, result.x, result.y, result.z, result.w);
}

void	print_result(int num_test, int type, ...)
{
	va_list	args;
	double	d_result;
	double	d_expected;
	t_tuple	t_result;
	t_tuple	t_expected;

	va_start(args, type);
	if (type == TUPLE)
	{
		t_expected = va_arg(args, t_tuple);
		t_result = va_arg(args, t_tuple);
		if (tuple_compare(t_expected, t_result) == 1)
			print_ok(num_test);
		else
			print_ko(num_test, t_expected, t_result);
	}
	if (type == FLOAT)
	{
		d_expected = va_arg(args, double);
		d_result = va_arg(args, double);
		if (float_compare(d_expected, d_result) == 1)
			print_ok(num_test);
		else
		{
			printf(PURPLE "%d" RESET " - " RED "[ ✗ ]" RESET
			" Expected: (%.2lf) RESULT: (%.2lf)\n", num_test, d_expected, d_result);
		}
	}
	va_end(args);
}

void test_tuple_1(int num_test) {

	// ARRANGE
	t_tuple	expected = {4.3, -4.2, 3.1, 1.0};
	t_tuple	result;

	// ACT
	result = tuple(4.3, -4.2, 3.1, 1.0);

	// ASSERT
	print_result(num_test, 1, expected, result);
}

void test_tuple_2(int num_test) {

	// ARRANGE
	t_tuple	expected = {4.3, -4.2, 3.1, 0.0};
	t_tuple	result;

	// ACT
	result = tuple(4.3, -4.2, 3.1, 0.0);

	// ASSERT
	print_result(num_test, 1, expected, result);
}

void	test_point(int num_test)
{
	// ARRANGE
	t_point	expected = {4, -4, 3, 1};
	t_point	result;

	// ACT
	result = point(4, -4, 3);

	// ASSERT
	print_result(num_test, 1, expected, result);
}

void	test_vector(int num_test)
{
	// ARRANGE
	t_vector	expected = {4, -4, 3, 0};
	t_vector	result;

	// ACT
	result = vector(4, -4, 3);

	// ASSERT
	print_result(num_test, 1, expected, result);
}

void	test_tuple_adding(int num_test)
{
	// ARRANGE
	t_tuple	tuple1 = tuple(3, -2, 5, 1);
	t_tuple	tuple2 = tuple(-2, 3, 1, 0);
	t_tuple	expected = tuple(1, 1, 6, 1);
	t_tuple	result;

	// ACT
	result = tuple_adding(tuple1, tuple2);

	// ASSERT
	print_result(num_test, 1, expected, result);
}

void	test_tuple_subtracting_points(int num_test)
{
	// ARRANGE
	t_tuple	point1 = point(3, 2, 1);
	t_tuple	point2 = point(5, 6, 7);
	t_tuple	expected = vector(-2, -4, -6);
	t_tuple	result;

	// ACT
	result = tuple_subtracting(point1, point2);

	// ASSERT
	print_result(num_test, 1, expected, result);
}

void	test_tuple_subtracting_vector_from_point(int num_test)
{
	// ARRANGE
	t_tuple	point1 = point(3, 2, 1);
	t_tuple	vector1 = vector(5, 6, 7);
	t_tuple	expected = point(-2, -4, -6);
	t_tuple	result;

	// ACT
	result = tuple_subtracting(point1, vector1);

	// ASSERT
	print_result(num_test, 1, expected, result);

}

void	test_tuple_subtracting_vector(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(3, 2, 1);
	t_tuple	vector2 = vector(5, 6, 7);
	t_tuple	expected = vector(-2, -4, -6);
	t_tuple	result;

	// ACT
	result = tuple_subtracting(vector1, vector2);

	// ASSERT
	print_result(num_test, 1, expected, result);

}

void	test_tuple_subtracting_vector_from_zero_vector(int num_test)
{
	// ARRANGE
	t_tuple	zero_vector = vector(0, 0, 0);
	t_tuple	vector1 = vector(1, -2, 3);
	t_tuple	expected = vector(-1, 2, -3);
	t_tuple	result;

	// ACT
	result = tuple_subtracting(zero_vector, vector1);

	// ASSERT
	print_result(num_test, 1, expected, result);

}

void	test_tuple_negating(int num_test)
{
	// ARRANGE
	t_tuple	tuple1 = tuple(1, -2, 3, -4);
	t_tuple	expected = tuple(-1, 2, -3, 4);
	t_tuple	result;

	// ACT
	result = tuple_negating(tuple1);

	// ASSERT
	print_result(num_test, 1, expected, result);

}

void	test_tuple_multiplying_scalar(int num_test)
{
	// ARRANGE
	double	scalar = 3.5;
	t_tuple	tuple1 = tuple(1, -2, 3, -4);
	t_tuple	expected = tuple(3.5, -7, 10.5, -14);
	t_tuple	result;

	// ACT
	result = tuple_multiplying(tuple1, scalar);

	// ASSERT
	print_result(num_test, 1, expected, result);

}

void	test_tuple_multiplying_fraction(int num_test)
{
	// ARRANGE
	double	fraction = 0.5;
	t_tuple	tuple1 = tuple(1, -2, 3, -4);
	t_tuple	expected = tuple(0.5, -1, 1.5, -2);
	t_tuple	result;

	// ACT
	result = tuple_multiplying(tuple1, fraction);

	// ASSERT
	print_result(num_test, 1, expected, result);

}

void	test_tuple_dividing(int num_test)
{
	// ARRANGE
	double	scalar = 2;
	t_tuple	tuple1 = tuple(1, -2, 3, -4);
	t_tuple	expected = tuple(0.5, -1, 1.5, -2);
	t_tuple	result;

	// ACT
	result = tuple_dividing(tuple1, scalar);

	// ASSERT
	print_result(num_test, 1, expected, result);

}

void	test_vector_magnitude(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(1, 0, 0);
	double	expected = 1.0;
	double	result;

	// ACT
	result = vector_magnitude(vector1);

	// ASSERT
	print_result(num_test, 2, expected, result);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_tuple_1, test_tuple_2, test_point, test_vector,
		test_tuple_adding, test_tuple_subtracting_points,
		test_tuple_subtracting_vector_from_point,
		test_tuple_subtracting_vector,
		test_tuple_subtracting_vector_from_zero_vector,
		test_tuple_negating,
		test_tuple_multiplying_scalar,
		test_tuple_multiplying_fraction,
		test_tuple_dividing,
		test_vector_magnitude
	};

	printf("\n%sTESTING TUPLES:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
