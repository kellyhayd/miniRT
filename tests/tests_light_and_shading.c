/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_light_and_shading.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:24:42 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/22 21:47:38 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

// TEST 01
void	test_normal_on_sphere_at_a_point_on_the_x_axis(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_vector	expected = vector(1, 0, 0);
	t_vector	result;

	// ACT
	result = normal_at(s, point(1, 0, 0));

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

// TEST 02
void	test_normal_on_sphere_at_a_point_on_the_y_axis(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_vector	expected = vector(0, 1, 0);
	t_vector	result;

	// ACT
	result = normal_at(s, point(0, 1, 0));

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

// TEST 03
void	test_normal_on_sphere_at_a_point_on_the_z_axis(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_vector	expected = vector(0, 0, 1);
	t_vector	result;

	// ACT
	result = normal_at(s, point(0, 0, 1));

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

// TEST 04
void	test_normal_on_sphere_at_a_nonaxial_point(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_vector	expected = vector(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3);
	t_vector	result;

	// ACT
	result = normal_at(s, point(sqrt(3) / 3, sqrt(3) / 3, sqrt(3) / 3));

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

// TEST 05
void	test_normal_on_a_translated_sphere(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_vector	expected = vector(0, 0.70711, -0.70711);
	t_vector	result;

	set_transformation(&s, translation(0, 1, 0));

	// ACT
	result = normal_at(s, point(0, 1.70711, -0.70711));

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

// TEST 06
void	test_normal_on_a_transformed_sphere(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_matrix	transformation_matrix;
	t_vector	expected = vector(0, 0.97014, -0.24254);
	t_vector	result;

	transformation_matrix = mx_multiply(scaling(1, 0.5, 1), rotation_z(M_PI / 5));
	set_transformation(&s, transformation_matrix);

	// ACT
	result = normal_at(s, point(0, sqrt(2) / 2, -sqrt(2) / 2));

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_normal_on_sphere_at_a_point_on_the_x_axis,			// 01
		test_normal_on_sphere_at_a_point_on_the_y_axis,			// 02
		test_normal_on_sphere_at_a_point_on_the_z_axis,			// 03
		test_normal_on_sphere_at_a_nonaxial_point,				// 04
		test_normal_on_a_translated_sphere,						// 05
		test_normal_on_a_transformed_sphere,					// 06
	};

	printf("\n%sTESTING LIGHT AND SHANDING:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
