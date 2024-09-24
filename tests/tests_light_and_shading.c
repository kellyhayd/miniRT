/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_light_and_shading.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:24:42 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/23 23:24:13 by krocha-h         ###   ########.fr       */
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

// TEST 07
void	test_reflecting_a_vector_approaching_at_45_degrees(int num_test)
{
	// ARRANGE
	t_vector	v = vector(1, -1, 0);
	t_vector	n = vector(0, 1, 0);
	t_vector	expected = vector(1, 1, 0);
	t_vector	result;


	// ACT
	result = reflect(v, n);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

// TEST 08
void	test_reflecting_a_vector_off_slanted_surface(int num_test)
{
	// ARRANGE
	t_vector	v = vector(0, -1, 0);
	t_vector	n = vector(sqrt(2) / 2, sqrt(2) / 2, 0);
	t_vector	expected = vector(1, 0, 0);
	t_vector	result;

	// ACT
	result = reflect(v, n);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

// TEST 09
void	test_a_point_light_has_a_position_and_intensity(int num_test)
{
	// ARRANGE
	t_color		intensity = color(1, 1, 1);
	t_point		position = point(0, 0, 0);
	t_light		expected = point_light(position, intensity);
	t_light		result;

	// ACT
	result = point_light(position, intensity);

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

// TEST 10
void	test_the_default_material(int num_test)
{
	// ARRANGE
	t_material	expected = material();
	t_material	result;

	// ACT
	result = material();

	// ASSERT
	print_result(num_test, &expected, &result, tuple_compare_test, print_ko_tuple);
}

/*
Scenario: The default material
Given m ← material()
Then m.color = color(1, 1, 1)
And m.ambient = 0.1
And m.diffuse = 0.9
And m.specular = 0.9
And m.shininess = 200.0
*/

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
		test_reflecting_a_vector_approaching_at_45_degrees,		// 07
		test_reflecting_a_vector_off_slanted_surface,			// 08
		test_a_point_light_has_a_position_and_intensity,		// 09
		test_the_default_material,								// 10
	};

	printf("\n%sTESTING LIGHT AND SHANDING:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
