/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_light.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:24:42 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/29 16:05:30 by krocha-h         ###   ########.fr       */
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
	print_result(num_test, &expected, &result, light_compare_test, print_ko_light);
}

// TEST 10
void	test_the_default_material(int num_test)
{
	// ARRANGE
	t_material	expected;
	t_material	result;

	expected.color = color(1, 1, 1);
	expected.ambient = 0.1;
	expected.diffuse = 0.9;
	expected.specular = 0.9;
	expected.shininess = 200.0;
	expected.pattern = stripe_pattern(color(1, 1, 1), color(0, 0, 0));

	// ACT
	result = material();

	// ASSERT
	print_result(num_test, &expected, &result, material_compare_test, print_ko_material);
}

// TEST 11
void	test_a_sphere_has_a_default_material(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_material	expected = material();
	t_material	result;

	// ACT
	result = s.material;

	// ASSERT
	print_result(num_test, &expected, &result, material_compare_test, print_ko_material);
}

// TEST 12
void	test_a_sphere_may_be_assigned_a_material(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_material	m = material();
	t_material	expected;
	t_material	result;

	m.ambient = 1;
	expected = m;

	// ACT
	s.material = m;
	result = s.material;

	// ASSERT
	print_result(num_test, &expected, &result, material_compare_test, print_ko_material);
}

// TEST 13
void	test_lighting_with_the_eye_between_the_light_and_the_surface(int num_test)
{
	// ARRANGE
	t_shape		sphere1 = sphere();
	t_color		result;
	t_sight		sight;
	t_color		expected = color(1.9, 1.9, 1.9);

	t_light		light = point_light(point(0, 0, -10), color(1, 1, 1));
	t_material	m = material();
	t_point		position = point(0, 0, 0);
	sight.eye = vector(0, 0, -1);
	sight.normal = vector(0, 0, -1);
	sight.in_shadow = false;
	sphere1.material = m;

	// ACT
	result = lighting(sphere1, light, position, sight);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
}

// TEST 14
void	test_lighting_with_the_eye_between_light_and_surface_eye_offset_45_degrees(int num_test)
{
	// ARRANGE
	t_shape		sphere1 = sphere();
	t_color		result;
	t_sight		sight;
	t_color		expected = color(1.0, 1.0, 1.0);

	t_light		light = point_light(point(0, 0, -10), color(1, 1, 1));
	t_material	m = material();
	t_point		position = point(0, 0, 0);
	sight.eye = vector(0, sqrt(2) / 2, -sqrt(2) / 2);
	sight.normal = vector(0, 0, -1);
	sight.in_shadow = false;
	sphere1.material = m;

	// ACT
	result = lighting(sphere1, light, position, sight);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
}

// TEST 15
void	test_lighting_with_eye_opposite_surface_light_offset_45_degrees(int num_test)
{
	// ARRANGE
	t_shape		sphere1 = sphere();
	t_color		result;
	t_sight		sight;
	t_color		expected = color(0.7364, 0.7364, 0.7364);

	t_light		light = point_light(point(0, 10, -10), color(1, 1, 1));
	t_material	m = material();
	t_point		position = point(0, 0, 0);
	sight.eye = vector(0, 0, -1);
	sight.normal = vector(0, 0, -1);
	sight.in_shadow = false;
	sphere1.material = m;

	// ACT
	result = lighting(sphere1, light, position, sight);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
}

// TEST 16
void	test_lighting_with_eye_in_the_path_of_the_reflection_vector(int num_test)
{
	// ARRANGE
	t_shape		sphere1 = sphere();
	t_color		result;
	t_sight		sight;
	t_color		expected = color(1.6364, 1.6364, 1.6364);

	t_light		light = point_light(point(0, 10, -10), color(1, 1, 1));
	t_material	m = material();
	t_point		position = point(0, 0, 0);
	sight.eye = vector(0, -sqrt(2) / 2, -sqrt(2) / 2);
	sight.normal = vector(0, 0, -1);
	sight.in_shadow = false;
	sphere1.material = m;

	// ACT
	result = lighting(sphere1, light, position, sight);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
}

// TEST 17
void	test_lighting_with_light_behind_the_surface(int num_test)
{
	// ARRANGE
	t_shape		sphere1 = sphere();
	t_color		result;
	t_sight		sight;
	t_color		expected = color(0.1, 0.1, 0.1);

	t_light		light = point_light(point(0, 0, 10), color(1, 1, 1));
	t_material	m = material();
	t_point		position = point(0, 0, 0);
	sight.eye = vector(0, 0, -1);
	sight.normal = vector(0, 0, -1);
	sphere1.material = m;

	// ACT
	result = lighting(sphere1, light, position, sight);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_normal_on_sphere_at_a_point_on_the_x_axis,								// 01
		test_normal_on_sphere_at_a_point_on_the_y_axis,								// 02
		test_normal_on_sphere_at_a_point_on_the_z_axis,								// 03
		test_normal_on_sphere_at_a_nonaxial_point,									// 04
		test_normal_on_a_translated_sphere,											// 05
		test_normal_on_a_transformed_sphere,										// 06
		test_reflecting_a_vector_approaching_at_45_degrees,							// 07
		test_reflecting_a_vector_off_slanted_surface,								// 08
		test_a_point_light_has_a_position_and_intensity,							// 09
		test_the_default_material,													// 10
		test_a_sphere_has_a_default_material,										// 11
		test_a_sphere_may_be_assigned_a_material,									// 12
		test_lighting_with_the_eye_between_the_light_and_the_surface,				// 13
		test_lighting_with_the_eye_between_light_and_surface_eye_offset_45_degrees,	// 14
		test_lighting_with_eye_opposite_surface_light_offset_45_degrees,			// 15
		test_lighting_with_eye_in_the_path_of_the_reflection_vector,				// 16
	};

	printf("\n%sTESTING LIGHT:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}
	return (0);
}
