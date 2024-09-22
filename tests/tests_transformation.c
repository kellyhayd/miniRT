/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_transformation.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/31 13:31:05 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/22 13:50:43 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	test_transformation_translation(int num_test)
{
	// ARRANGE
	t_matrix	m_translation = translation(5, -3, 2);
	t_tuple		p = point(-3, 4, 5);
	t_tuple		expected = point(2, 1, 7);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_translation, p);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_scaling_point(int num_test)
{
	// ARRANGE
	t_matrix	m_scaling = scaling(2, 3, 4);
	t_tuple		p = point(-4, 6, 8);
	t_tuple		expected = point(-8, 18, 32);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_scaling, p);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_scaling_vector(int num_test)
{
	// ARRANGE
	t_matrix	m_scaling = scaling(2, 3, 4);
	t_tuple		v = vector(-4, 6, 8);
	t_tuple		expected = vector(-8, 18, 32);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_scaling, v);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_scaling_vector_inverse(int num_test)
{
	// ARRANGE
	t_matrix	m_scaling = scaling(2, 3, 4);
	t_matrix	m_inverse = inverse(m_scaling);
	t_tuple		v = vector(-4, 6, 8);
	t_tuple		expected = vector(-2, 2, 2);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_inverse, v);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_scaling_negative(int num_test)		// Reflection
{
	// ARRANGE
	t_matrix	m_scaling = scaling(-1, -1, -1);
	t_tuple		v = vector(-4, 6, 8);
	t_tuple		expected = vector(4, -6, -8);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_scaling, v);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_rotation_x(int num_test)
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
	result_half = matrix_multiply_tuple(half_quarter, p);
	result_full = matrix_multiply_tuple(full_quarter, p);

	// ASSERT
	print_result(num_test, &expected_half, &result_half, tuple_compare_test, print_ko_tuple);
	print_result(num_test, &expected_full, &result_full, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_rotation_y(int num_test)
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
	result_half = matrix_multiply_tuple(half_quarter, p);
	result_full = matrix_multiply_tuple(full_quarter, p);

	// ASSERT
	print_result(num_test, &expected_half, &result_half, tuple_compare_test, print_ko_tuple);
	print_result(num_test, &expected_full, &result_full, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_rotation_z(int num_test)
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
	result_half = matrix_multiply_tuple(half_quarter, p);
	result_full = matrix_multiply_tuple(full_quarter, p);

	// ASSERT
	print_result(num_test, &expected_half, &result_half, tuple_compare_test, print_ko_tuple);
	print_result(num_test, &expected_full, &result_full, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_shearing_x_to_y(int num_test)
{
	// ARRANGE
	double		prop_x[2] = {1, 0};
	double		prop_y[2] = {0, 0};
	double		prop_z[2] = {0, 0};

	t_matrix	m_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(5, 3, 4);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_shearing, p);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_shearing_x_to_z(int num_test)
{
	// ARRANGE
	double		prop_x[2] = {0, 1};
	double		prop_y[2] = {0, 0};
	double		prop_z[2] = {0, 0};

	t_matrix	m_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(6, 3, 4);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_shearing, p);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_shearing_y_to_x(int num_test)
{
	// ARRANGE
	double		prop_x[2] = {0, 0};
	double		prop_y[2] = {1, 0};
	double		prop_z[2] = {0, 0};

	t_matrix	m_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(2, 5, 4);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_shearing, p);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_shearing_y_to_z(int num_test)
{
	// ARRANGE
	double		prop_x[2] = {0, 0};
	double		prop_y[2] = {0, 1};
	double		prop_z[2] = {0, 0};

	t_matrix	m_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(2, 7, 4);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_shearing, p);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_shearing_z_to_x(int num_test)
{
	// ARRANGE
	double		prop_x[2] = {0, 0};
	double		prop_y[2] = {0, 0};
	double		prop_z[2] = {1, 0};

	t_matrix	m_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(2, 3, 6);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_shearing, p);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_shearing_z_to_y(int num_test)
{
	// ARRANGE
	double		prop_x[2] = {0, 0};
	double		prop_y[2] = {0, 0};
	double		prop_z[2] = {0, 1};

	t_matrix	m_shearing = shearing(prop_x, prop_y, prop_z);
	t_tuple		p = point(2, 3, 4);
	t_tuple		expected = point(2, 3, 7);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(m_shearing, p);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_in_sequence(int num_test)
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
	p2 = matrix_multiply_tuple(A, p);
	result1 = p2;

	p3 = matrix_multiply_tuple(B, p2);
	result2 = p3;

	p4 = matrix_multiply_tuple(C, p3);
	result3 = p4;

	// ASSERT
	print_result(num_test, &expected1, &result1, tuple_compare_test, print_ko_tuple);
	print_result(num_test, &expected2, &result2, tuple_compare_test, print_ko_tuple);
	print_result(num_test, &expected3, &result3, tuple_compare_test, print_ko_tuple);
}

void	test_transformation_chain_sequence(int num_test)
{
	// ARRANGE
	t_tuple		p 			= point(1, 0, 1);
	t_matrix	A			= rotation_x(M_PI / 2);
	t_matrix	B			= scaling(5, 5, 5);
	t_matrix	C			= translation(10, 5, 7);
	t_matrix	T1			= matrix_multiply(B, A);
	t_matrix	T			= matrix_multiply(C, T1);
	t_tuple		expected	= point(15, 0, 7);
	t_tuple		result;

	// ACT
	result = matrix_multiply_tuple(T, p);
	// t = multiply_mx_mx(multiply_mx_mx(c, b), a);

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
		test_transformation_rotation_x,				// 06
		test_transformation_rotation_y,				// 07
		test_transformation_rotation_z,				// 08
		test_transformation_shearing_x_to_y,		// 09
		test_transformation_shearing_x_to_z,		// 10
		test_transformation_shearing_y_to_x,		// 11
		test_transformation_shearing_y_to_z,		// 12
		test_transformation_shearing_z_to_x,		// 13
		test_transformation_shearing_z_to_y,		// 14
		test_transformation_in_sequence,			// 15
		test_transformation_chain_sequence,			// 16
	};

	printf("\n%sTESTING TRANFORMATION:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
