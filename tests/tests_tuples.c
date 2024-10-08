/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_tuples.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:32:15 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/22 12:56:14 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void test_tuple_1(int num_test) {

	// ARRANGE
	t_tuple	expected = {4.3, -4.2, 3.1, 1.0};
	t_tuple	result;

	// ACT
	result = tuple(4.3, -4.2, 3.1, 1.0);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void test_tuple_2(int num_test) {

	// ARRANGE
	t_tuple	expected = {4.3, -4.2, 3.1, 0.0};
	t_tuple	result;

	// ACT
	result = tuple(4.3, -4.2, 3.1, 0.0);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_point(int num_test)
{
	// ARRANGE
	t_point	expected = {4, -4, 3, 1};
	t_point	result;

	// ACT
	result = point(4, -4, 3);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_vector(int num_test)
{
	// ARRANGE
	t_vector	expected = {4, -4, 3, 0};
	t_vector	result;

	// ACT
	result = vector(4, -4, 3);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_tuple_adding(int num_test)
{
	// ARRANGE
	t_tuple	tuple1 = tuple(3, -2, 5, 1);
	t_tuple	tuple2 = tuple(-2, 3, 1, 0);
	t_tuple	expected = tuple(1, 1, 6, 1);
	t_tuple	result;

	// ACT
	result = tuple_add(tuple1, tuple2);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_tuple_subtracting_points(int num_test)
{
	// ARRANGE
	t_tuple	point1 = point(3, 2, 1);
	t_tuple	point2 = point(5, 6, 7);
	t_tuple	expected = vector(-2, -4, -6);
	t_tuple	result;

	// ACT
	result = tuple_subtract(point1, point2);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_tuple_subtracting_vector_from_point(int num_test)
{
	// ARRANGE
	t_tuple	point1 = point(3, 2, 1);
	t_tuple	vector1 = vector(5, 6, 7);
	t_tuple	expected = point(-2, -4, -6);
	t_tuple	result;

	// ACT
	result = tuple_subtract(point1, vector1);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);

}

void	test_tuple_subtracting_vector(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(3, 2, 1);
	t_tuple	vector2 = vector(5, 6, 7);
	t_tuple	expected = vector(-2, -4, -6);
	t_tuple	result;

	// ACT
	result = tuple_subtract(vector1, vector2);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_tuple_subtracting_vector_from_zero_vector(int num_test)
{
	// ARRANGE
	t_tuple	zero_vector = vector(0, 0, 0);
	t_tuple	vector1 = vector(1, -2, 3);
	t_tuple	expected = vector(-1, 2, -3);
	t_tuple	result;

	// ACT
	result = tuple_subtract(zero_vector, vector1);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);

}

void	test_tuple_negating(int num_test)
{
	// ARRANGE
	t_tuple	tuple1 = tuple(1, -2, 3, -4);
	t_tuple	expected = tuple(-1, 2, -3, 4);
	t_tuple	result;

	// ACT
	result = tuple_negate(tuple1);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_tuple_multiplying_scalar(int num_test)
{
	// ARRANGE
	double	scalar = 3.5;
	t_tuple	tuple1 = tuple(1, -2, 3, -4);
	t_tuple	expected = tuple(3.5, -7, 10.5, -14);
	t_tuple	result;

	// ACT
	result = tuple_multiply(tuple1, scalar);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_tuple_multiplying_fraction(int num_test)
{
	// ARRANGE
	double	fraction = 0.5;
	t_tuple	tuple1 = tuple(1, -2, 3, -4);
	t_tuple	expected = tuple(0.5, -1, 1.5, -2);
	t_tuple	result;

	// ACT
	result = tuple_multiply(tuple1, fraction);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_tuple_dividing(int num_test)
{
	// ARRANGE
	double	scalar = 2;
	t_tuple	tuple1 = tuple(1, -2, 3, -4);
	t_tuple	expected = tuple(0.5, -1, 1.5, -2);
	t_tuple	result;

	// ACT
	result = tuple_divide(tuple1, scalar);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_vector_magnitude(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(1, 0, 0);
	double	expected = 1.0;
	double	result;

	// ACT
	result = magnitude(vector1);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_vector_magnitude_positive(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(1, 2, 3);
	double	expected = sqrt(14);
	double	result;

	// ACT
	result = magnitude(vector1);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_vector_magnitude_negative(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(-1, -2, -3);
	double	expected = sqrt(14);
	double	result;

	// ACT
	result = magnitude(vector1);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_vector_normalize_1(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(4, 0, 0);
	t_tuple	expected = tuple(1, 0, 0, 0);
	t_tuple	result;

	// ACT
	result = normalize(vector1);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_vector_normalize_2(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(1, 2, 3);
	t_tuple	expected = tuple(0.26726, 0.53452, 0.80178, 0);
	t_tuple	result;

	// ACT
	result = normalize(vector1);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_vector_normalize_3(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(1, 2, 3);
	t_tuple	norm_vector = normalize(vector1);
	double	expected = 1.0;
	double	result;

	// ACT
	result = magnitude(norm_vector);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_dot_product(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(1, 2, 3);
	t_tuple	vector2 = vector(2, 3, 4);
	double	expected = 20.0;
	double	result;

	// ACT
	result = dot(vector1, vector2);

	// ASSERT
	print_result(num_test, &expected, &result, float_compare_test, print_ko_float);
}

void	test_cross_product_A_B(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(1, 2, 3);
	t_tuple	vector2 = vector(2, 3, 4);
	t_tuple	expected = tuple(-1, 2, -1, 0);
	t_tuple	result;

	// ACT
	result = cross(vector1, vector2);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_cross_product_B_A(int num_test)
{
	// ARRANGE
	t_tuple	vector1 = vector(1, 2, 3);
	t_tuple	vector2 = vector(2, 3, 4);
	t_tuple	expected = tuple(1, -2, 1, 0);
	t_tuple	result;

	// ACT
	result = cross(vector2, vector1);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
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
		test_vector_magnitude,
		test_vector_magnitude_positive,
		test_vector_magnitude_negative,
		test_vector_normalize_1,
		test_vector_normalize_2,
		test_vector_normalize_3,
		test_dot_product,
		test_cross_product_A_B,
		test_cross_product_B_A,
	};

	printf("\n%sTESTING TUPLES:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
