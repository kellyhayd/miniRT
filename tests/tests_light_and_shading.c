/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_light_and_shading.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 15:24:42 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/22 17:22:35 by krocha-h         ###   ########.fr       */
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


int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_normal_on_sphere_at_a_point_on_the_x_axis,					// 01
		test_normal_on_sphere_at_a_point_on_the_y_axis,					// 02
		test_normal_on_sphere_at_a_point_on_the_z_axis,					// 03
	};

	printf("\n%sTESTING LIGHT AND SHANDING:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
