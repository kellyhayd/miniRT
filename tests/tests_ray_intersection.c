/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   tests_ray_intersection.c						   :+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: krocha-h <krocha-h@student.42sp.org.br>	+#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/09/05 20:09:18 by danbarbo		  #+#	#+#			 */
/*   Updated: 2024/09/07 19:41:48 by krocha-h		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "tests.h"

void	test_creating_and_querying_a_ray(int num_test)
{
	// ARRANGE
	t_point		origin = point(1, 2, 3);
	t_vector	direction = vector(4, 5, 6);
	t_ray		expected = (t_ray) {.origin = origin, direction = direction};
	t_ray		result;

	// ACT
	result = ray(origin, direction);

	// ASSERT
	print_result(num_test, &expected, &result, ray_compare_test, print_ko_ray);
}

void	test_computing_a_point_from_a_distance(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(2, 3, 4), vector(1, 0, 0));
	t_point		expected[4];
	t_point		result[4];

	expected[0] = point(2, 3, 4);
	expected[1] = point(3, 3, 4);
	expected[2] = point(1, 3, 4);
	expected[3] = point(4.5, 3, 4);

	// ACT
	result[0] = position(r, 0);
	result[1] = position(r, 1);
	result[2] = position(r, -1);
	result[3] = position(r, 2.5);

	// ASSERT
	print_result(num_test, &expected[0], &result[0], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &expected[1], &result[1], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &expected[2], &result[2], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &expected[3], &result[3], tuple_compare_test, print_ko_tuple);
}

void	test_a_ray_intersects_a_sphere_at_two_points(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_shape		s = {.sphere_shape = sphere()};
	t_hit		*expected;
	t_hit		*result = NULL;
	int			xs_count_expected = 2;
	int			xs_count_result;

	expected = malloc(sizeof(t_hit));
	expected->t = 4.0;
	expected->object = s;

	expected->next = malloc(sizeof(t_hit));
	expected->next->t = 6.0;
	expected->next->next = NULL;

	// ACT
	intersect(&result, s, r);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_compare_test, print_ko_hit);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_a_ray_intersects_a_sphere_at_a_tangent(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 1, -5), vector(0, 0, 1));
	t_shape		s = {.sphere_shape = sphere()};
	t_hit		*expected;
	t_hit		*result = NULL;
	int			xs_count_expected = 2;
	int			xs_count_result;

	expected = malloc(sizeof(t_hit));
	expected->t = 5.0;
	expected->object = s;

	expected->next = malloc(sizeof(t_hit));
	expected->next->t = 5.0;
	expected->next->object = s;
	expected->next->next = NULL;

	// ACT
	intersect(&result, s, r);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_compare_test, print_ko_hit);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_a_ray_misses_a_sphere(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 0, -5), vector(0, 1, 0));
	t_shape		s = {.sphere_shape = sphere()};
	t_hit		*expected = NULL;
	t_hit		*result = NULL;
	int			xs_count_expected = 0;
	int			xs_count_result;

	// ACT
	intersect(&result, s, r);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_compare_test, print_ko_hit);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_a_ray_originates_inside_a_sphere(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_shape		s = {.sphere_shape = sphere()};
	t_hit		*expected;
	t_hit		*result = NULL;
	int			xs_count_expected = 2;
	int			xs_count_result;

	expected = malloc(sizeof(t_hit));
	expected->t = -1.0;
	expected->object = s;

	expected->next = malloc(sizeof(t_hit));
	expected->next->t = 1.0;
	expected->next->object = s;
	expected->next->next = NULL;

	// ACT
	intersect(&result, s, r);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_compare_test, print_ko_hit);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_a_sphere_is_behind_a_ray(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 0, 5), vector(0, 0, 1));
	t_shape		s = {.sphere_shape = sphere()};
	t_hit		*expected;
	t_hit		*result = NULL;
	int			xs_count_expected = 2;
	int			xs_count_result;

	expected = malloc(sizeof(t_hit));
	expected->t = -6.0;
	expected->object = s;

	expected->next = malloc(sizeof(t_hit));
	expected->next->t = -4.0;
	expected->next->object = s;
	expected->next->next = NULL;

	// ACT
	intersect(&result, s, r);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_compare_test, print_ko_hit);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_creating_and_querying_a_ray,				// 01
		test_computing_a_point_from_a_distance,			// 02
		test_a_ray_intersects_a_sphere_at_two_points,	// 03
		test_a_ray_intersects_a_sphere_at_a_tangent,	// 04
		test_a_ray_misses_a_sphere,						// 05
		test_a_ray_originates_inside_a_sphere,			// 06
		test_a_sphere_is_behind_a_ray,					// 07
	};

	printf("\n%sTESTING INTERSECTIONS:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
