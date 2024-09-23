/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_transformation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:31:05 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/22 23:13:56 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_multiplying_by_a_translation_matrix(int numatrix_test)
{
	// ARRANGE
	t_matrix	matrix_translation = translation(5, -3, 2);
	t_tuple		p = point(-3, 4, 5);
	t_tuple		expected = point(2, 1, 7);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_translation, p);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_multiplying_by_the_inverse_of_a_translation_matrix(int numatrix_test)
{
	// ARRANGE
	t_matrix	matrix_translation = translation(5, -3, 2);
	t_matrix	matrix_inverse = inverse(matrix_translation);
	t_tuple		p = point(-3, 4, 5);
	t_tuple		expected = point(-8, 7, 3);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_inverse, p);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_translation_does_not_affect_vectors(int numatrix_test)
{
	// ARRANGE
	t_matrix	matrix_translation = translation(5, -3, 2);
	t_tuple		v = vector(-3, 4, 5);
	t_tuple		expected = v;
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_translation, v);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_a_scaling_matrix_applied_to_a_point(int numatrix_test)
{
	// ARRANGE
	t_matrix	matrix_scaling = scaling(2, 3, 4);
	t_tuple		p = point(-4, 6, 8);
	t_tuple		expected = point(-8, 18, 32);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_scaling, p);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_a_scaling_matrix_applied_to_a_vector(int numatrix_test)
{
	// ARRANGE
	t_matrix	matrix_scaling = scaling(2, 3, 4);
	t_tuple		v = vector(-4, 6, 8);
	t_tuple		expected = vector(-8, 18, 32);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_scaling, v);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_multiplying_by_the_inverse_of_a_scaling_matrix(int numatrix_test)
{
	// ARRANGE
	t_matrix	matrix_scaling = scaling(2, 3, 4);
	t_matrix	matrix_inverse = inverse(matrix_scaling);
	t_tuple		v = vector(-4, 6, 8);
	t_tuple		expected = vector(-2, 2, 2);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_inverse, v);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_reflection_is_scaling_by_a_negative_value(int numatrix_test)
{
	// ARRANGE
	t_matrix	matrix_scaling = scaling(-1, 1, 1);
	t_tuple		v = vector(2, 3, 4);
	t_tuple		expected = vector(-2, 3, 4);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_scaling, v);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_rotating_a_point_around_the_x_axis(int numatrix_test)
{
	// ARRANGE
	t_tuple		p = point(0, 1, 0);
	t_matrix	half_quarter = rotation_x(M_PI / 4);
	t_matrix	full_quarter = rotation_x(M_PI / 2);
	t_tuple		expected_half = point(0, sqrt(2) / 2, sqrt(2) / 2);
	t_tuple		expected_full = point(0, 0, 1);
	t_tuple		result_half;
	t_tuple		result_full;

	// ACT
	result_half = mx_multiply_tuple(half_quarter, p);
	result_full = mx_multiply_tuple(full_quarter, p);

	// ASSERT
	print_result(numatrix_test, &expected_half, &result_half, tuple_compare_test, print_ko_tuple);
	print_result(numatrix_test, &expected_full, &result_full, tuple_compare_test, print_ko_tuple);
}

void	test_the_inverse_of_an_x_rotation_rotates_in_the_opposite_direction(int numatrix_test)
{
	// ARRANGE
	t_tuple		p = point(0, 1, 0);
	t_matrix	half_quarter = rotation_x(M_PI / 4);
	t_matrix	inverse_half_quarter = inverse(half_quarter);
	t_tuple		expected = point(0, sqrt(2) / 2, -sqrt(2) / 2);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(inverse_half_quarter, p);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_rotating_a_point_around_the_y_axis(int numatrix_test)
{
	// ARRANGE
	t_tuple		p = point(0, 0, 1);
	t_matrix	half_quarter = rotation_y(M_PI / 4);
	t_matrix	full_quarter = rotation_y(M_PI / 2);
	t_tuple		expected_half = point(sqrt(2) / 2, 0, sqrt(2) / 2);
	t_tuple		expected_full = point(1, 0, 0);
	t_tuple		result_half;
	t_tuple		result_full;

	// ACT
	result_half = mx_multiply_tuple(half_quarter, p);
	result_full = mx_multiply_tuple(full_quarter, p);

	// ASSERT
	print_result(numatrix_test, &expected_half, &result_half, tuple_compare_test, print_ko_tuple);
	print_result(numatrix_test, &expected_full, &result_full, tuple_compare_test, print_ko_tuple);
}

void	test_rotating_a_point_around_the_z_axis(int numatrix_test)
{
	// ARRANGE
	t_tuple		p = point(0, 1, 0);
	t_matrix	half_quarter = rotation_z(M_PI / 4);
	t_matrix	full_quarter = rotation_z(M_PI / 2);
	t_tuple		expected_half = point(-sqrt(2) / 2, sqrt(2) / 2, 0);
	t_tuple		expected_full = point(-1, 0, 0);
	t_tuple		result_half;
	t_tuple		result_full;

	// ACT
	result_half = mx_multiply_tuple(half_quarter, p);
	result_full = mx_multiply_tuple(full_quarter, p);

	// ASSERT
	print_result(numatrix_test, &expected_half, &result_half, tuple_compare_test, print_ko_tuple);
	print_result(numatrix_test, &expected_full, &result_full, tuple_compare_test, print_ko_tuple);
}

void	test_a_shearing_transformation_moves_x_in_proportion_to_y(int numatrix_test)
{
	// ARRANGE
	double		prop_x[2] = {1, 0};
	double		prop_y[2] = {0, 0};
	double		prop_z[2] = {0, 0};

	t_matrix	matrix_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(5, 3, 4);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_shearing, p);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_a_shearing_transformation_moves_x_in_proportion_to_z(int numatrix_test)
{
	// ARRANGE
	double		prop_x[2] = {0, 1};
	double		prop_y[2] = {0, 0};
	double		prop_z[2] = {0, 0};

	t_matrix	matrix_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(6, 3, 4);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_shearing, p);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_a_shearing_transformation_moves_y_in_proportion_to_x(int numatrix_test)
{
	// ARRANGE
	double		prop_x[2] = {0, 0};
	double		prop_y[2] = {1, 0};
	double		prop_z[2] = {0, 0};

	t_matrix	matrix_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(2, 5, 4);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_shearing, p);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_a_shearing_transformation_moves_y_in_proportion_to_z(int numatrix_test)
{
	// ARRANGE
	double		prop_x[2] = {0, 0};
	double		prop_y[2] = {0, 1};
	double		prop_z[2] = {0, 0};

	t_matrix	matrix_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(2, 7, 4);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_shearing, p);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_a_shearing_transformation_moves_z_in_proportion_to_x(int numatrix_test)
{
	// ARRANGE
	double		prop_x[2] = {0, 0};
	double		prop_y[2] = {0, 0};
	double		prop_z[2] = {1, 0};

	t_matrix	matrix_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(2, 3, 6);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_shearing, p);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_a_shearing_transformation_moves_z_in_proportion_to_y(int numatrix_test)
{
	// ARRANGE
	double		prop_x[2] = {0, 0};
	double		prop_y[2] = {0, 0};
	double		prop_z[2] = {0, 1};

	t_matrix	matrix_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(2, 3, 7);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(matrix_shearing, p);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_individual_transformations_are_applied_in_sequence(int numatrix_test)
{
	// ARRANGE
	t_tuple		p 			= point(1, 0, 1);
	t_matrix	A			= rotation_x(M_PI / 2);
	t_matrix	B			= scaling(5, 5, 5);
	t_matrix	C			= translation(10, 5, 7);
	t_tuple		expected1	= point(1, -1, 0);
	t_tuple		expected2	= point(5, -5, 0);
	t_tuple		expected3	= point(15, 0, 7);
	t_tuple		result1;
	t_tuple		result2;
	t_tuple		result3;
	t_point		p2;
	t_point		p3;
	t_point		p4;

	// ACT
	p2 = mx_multiply_tuple(A, p);
	result1 = p2;

	p3 = mx_multiply_tuple(B, p2);
	result2 = p3;

	p4 = mx_multiply_tuple(C, p3);
	result3 = p4;

	// ASSERT
	print_result(numatrix_test, &expected1, &result1, tuple_compare_test, print_ko_tuple);
	print_result(numatrix_test, &expected2, &result2, tuple_compare_test, print_ko_tuple);
	print_result(numatrix_test, &expected3, &result3, tuple_compare_test, print_ko_tuple);
}

void	test_chained_transformations_must_be_applied_in_reverse_order(int numatrix_test)
{
	// ARRANGE
	t_tuple		p 			= point(1, 0, 1);
	t_matrix	A			= rotation_x(M_PI / 2);
	t_matrix	B			= scaling(5, 5, 5);
	t_matrix	C			= translation(10, 5, 7);
	t_matrix	T1			= mx_multiply(B, A);
	t_matrix	T			= mx_multiply(C, T1);
	t_tuple		expected	= point(15, 0, 7);
	t_tuple		result;

	// ACT
	result = mx_multiply_tuple(T, p);
	// t = multiply_mx_mx(multiply_mx_mx(c, b), a);

	// ASSERT
	print_result(numatrix_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_multiplying_by_a_translation_matrix,								// 01
		test_multiplying_by_the_inverse_of_a_translation_matrix,				// 02
		test_translation_does_not_affect_vectors,								// 03
		test_a_scaling_matrix_applied_to_a_point,								// 04
		test_a_scaling_matrix_applied_to_a_vector,								// 05
		test_multiplying_by_the_inverse_of_a_scaling_matrix,					// 06
		test_reflection_is_scaling_by_a_negative_value,							// 07
		test_rotating_a_point_around_the_x_axis,								// 08
		test_the_inverse_of_an_x_rotation_rotates_in_the_opposite_direction,	// 09
		test_rotating_a_point_around_the_y_axis,								// 10
		test_rotating_a_point_around_the_z_axis,								// 11
		test_a_shearing_transformation_moves_x_in_proportion_to_y,				// 12
		test_a_shearing_transformation_moves_x_in_proportion_to_z,				// 13
		test_a_shearing_transformation_moves_y_in_proportion_to_x,				// 14
		test_a_shearing_transformation_moves_y_in_proportion_to_z,				// 15
		test_a_shearing_transformation_moves_z_in_proportion_to_x,				// 16
		test_a_shearing_transformation_moves_z_in_proportion_to_y,				// 17
		test_individual_transformations_are_applied_in_sequence,				// 18
		test_chained_transformations_must_be_applied_in_reverse_order,			// 19
	};

	printf("\n%sTESTING TRANFORMATION:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
