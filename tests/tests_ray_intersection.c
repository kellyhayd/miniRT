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
	t_ray		expected = {.origin = origin, direction = direction};
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
	t_shape		s = sphere();
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
	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_a_ray_intersects_a_sphere_at_a_tangent(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 1, -5), vector(0, 0, 1));
	t_shape		s = sphere();
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
	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_a_ray_misses_a_sphere(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 0, -5), vector(0, 1, 0));
	t_shape		s = sphere();
	t_hit		*expected = NULL;
	t_hit		*result = NULL;
	int			xs_count_expected = 0;
	int			xs_count_result;

	// ACT
	intersect(&result, s, r);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_a_ray_originates_inside_a_sphere(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_shape		s = sphere();
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
	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_a_sphere_is_behind_a_ray(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 0, 5), vector(0, 0, 1));
	t_shape		s = sphere();
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
	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_an_intersection_encapsulates_t_and_object(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_hit		expected = {.t = 3.5, .object = s, .next = NULL};
	t_hit		result;

	// ACT
	result = intersection(3.5, s);

	// ASSERT
	print_result(num_test, &expected, &result, hit_compare_test, print_ko_hit);
}

void	test_aggregating_intersections(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_hit		i1 = {.t = 1, .object = s, .next = NULL};
	t_hit		i2 = {.t = 2, .object = s, .next = NULL};
	t_hit		*expected;
	t_hit		*result = NULL;
	int			xs_count_expected = 2;
	int			xs_count_result;

	expected = malloc(sizeof(t_hit));
	*expected = i1;

	expected->next = malloc(sizeof(t_hit));
	*expected->next = i2;

	// ACT
	add_intersection(&result, i1);
	add_intersection(&result, i2);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_intersect_sets_the_object_on_the_intersection(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_shape		s = sphere();
	t_hit		*expected;
	t_hit		*result = NULL;
	int			xs_count_expected = 2;
	int			xs_count_result;

	expected = malloc(sizeof(t_hit));
	expected->t = 4.0;
	expected->object = s;

	expected->next = malloc(sizeof(t_hit));
	expected->next->t = 6.0;
	expected->next->object = s;
	expected->next->next = NULL;

	// ACT
	intersect(&result, s, r);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_the_hit_when_all_intersections_have_positive_t(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_hit		i1 = {.t = 1, .object = s, .next = NULL};
	t_hit		i2 = {.t = 2, .object = s, .next = NULL};
	t_hit		*hit_list;
	t_hit		*expected;
	t_hit		*result;

	hit_list = malloc(sizeof(t_hit));
	*hit_list = i1;

	hit_list->next = malloc(sizeof(t_hit));
	*hit_list->next = i2;

	expected = hit_list;

	// ACT
	result = hit(hit_list);

	// ASSERT
	print_result(num_test, expected, result, hit_compare_test, print_ko_hit);

	// CLEAR
	hit_clear_list(&hit_list);
}

void	test_the_hit_when_some_intersections_have_negative_t(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_hit		i1 = {.t = -1, .object = s, .next = NULL};
	t_hit		i2 = {.t = 1, .object = s, .next = NULL};
	t_hit		*hit_list;
	t_hit		*expected;
	t_hit		*result;

	hit_list = malloc(sizeof(t_hit));
	*hit_list = i1;

	hit_list->next = malloc(sizeof(t_hit));
	*hit_list->next = i2;

	expected = hit_list->next;

	// ACT
	result = hit(hit_list);

	// ASSERT
	print_result(num_test, expected, result, hit_compare_test, print_ko_hit);

	// CLEAR
	hit_clear_list(&hit_list);
}

void	test_the_hit_when_all_intersections_have_negative_t(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_hit		i1 = {.t = -2, .object = s, .next = NULL};
	t_hit		i2 = {.t = -1, .object = s, .next = NULL};
	t_hit		*hit_list;
	t_hit		*expected;
	t_hit		*result;

	// A lista precisa estar ordenada
	hit_list = malloc(sizeof(t_hit));
	*hit_list = i2;

	hit_list->next = malloc(sizeof(t_hit));
	*hit_list->next = i1;

	expected = NULL;

	// ACT
	result = hit(hit_list);

	// ASSERT
	print_result(num_test, expected, result, hit_compare_test, print_ko_hit);

	// CLEAR
	hit_clear_list(&hit_list);
}

void	test_the_hit_is_always_the_lowest_nonnegative_intersection(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_hit		i1 = {.t = 5, .object = s, .next = NULL};
	t_hit		i2 = {.t = 7, .object = s, .next = NULL};
	t_hit		i3 = {.t = -3, .object = s, .next = NULL};
	t_hit		i4 = {.t = 2, .object = s, .next = NULL};
	t_hit		*hit_list;
	t_hit		*expected;
	t_hit		*result;

	// A lista precisa estar ordenada
	hit_list = malloc(sizeof(t_hit));
	*hit_list = i3;						// -3

	hit_list->next = malloc(sizeof(t_hit));
	*hit_list->next = i4;				// 2

	hit_list->next->next = malloc(sizeof(t_hit));
	*hit_list->next->next = i1;			// 5

	hit_list->next->next->next = malloc(sizeof(t_hit));
	*hit_list->next->next->next = i2;	// 7

	expected = hit_list->next;

	// ACT
	result = hit(hit_list);

	// ASSERT
	print_result(num_test, expected, result, hit_compare_test, print_ko_hit);

	// CLEAR
	hit_clear_list(&hit_list);
}

void	test_translating_a_ray(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(1, 2, 3), vector(0, 1, 0));
	t_matrix	m = translation(3, 4, 5);
	t_ray		expected = ray(point(4, 6, 8), vector(0, 1, 0));
	t_ray		result;

	// ACT
	result = ray_transform(r, m);

	// ASSERT
	print_result(num_test, &expected, &result, ray_compare_test, print_ko_ray);
}

void test_scaling_a_ray(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(1, 2, 3), vector(0, 1, 0));
	t_matrix	m = scaling(2, 3, 4);
	t_ray		expected = ray(point(2, 6, 12), vector(0, 3, 0));
	t_ray		result;

	// ACT
	result = ray_transform(r, m);

	// ASSERT
	print_result(num_test, &expected, &result, ray_compare_test, print_ko_ray);
}

void	test_a_sphere_default_transformation(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_matrix	expected = matrix_identity();
	t_matrix	result;

	// ACT
	result = s.transform;

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_changing_a_sphere_transformation(int num_test)
{
	// ARRANGE
	t_shape		s = sphere();
	t_matrix	t = translation(2, 3, 4);
	t_matrix	expected = t;
	t_matrix	result;

	// ACT
	set_transformation(&s, t);
	result = s.transform;

	// ASSERT
	print_result(num_test, &expected, &result, matrix_compare_test, print_ko_matrix);
}

void	test_intersecting_a_scaled_sphere_with_a_ray(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_shape		s = sphere();
	t_matrix	m = scaling(2, 2, 2);
	t_hit		*expected;
	t_hit		*result = NULL;
	int			xs_count_expected = 2;
	int			xs_count_result;

	expected = malloc(sizeof(t_hit));
	expected->t = 3.0;
	expected->object = s;

	expected->next = malloc(sizeof(t_hit));
	expected->next->t = 7.0;
	expected->next->object = s;
	expected->next->next = NULL;

	// ACT
	set_transformation(&s, m);
	intersect(&result, s, r);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

void	test_intersecting_a_translated_sphere_with_a_ray(int num_test)
{
	// ARRANGE
	t_ray		r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_shape		s = sphere();
	t_matrix	m = translation(5, 0, 0);
	t_hit		*expected;
	t_hit		*result = NULL;
	int			xs_count_expected = 0;
	int			xs_count_result;

	expected = NULL;

	// ACT
	set_transformation(&s, m);
	intersect(&result, s, r);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_creating_and_querying_a_ray,							// 01
		test_computing_a_point_from_a_distance,						// 02
		test_a_ray_intersects_a_sphere_at_two_points,				// 03
		test_a_ray_intersects_a_sphere_at_a_tangent,				// 04
		test_a_ray_misses_a_sphere,									// 05
		test_a_ray_originates_inside_a_sphere,						// 06
		test_a_sphere_is_behind_a_ray,								// 07
		test_an_intersection_encapsulates_t_and_object,				// 08
		test_aggregating_intersections,								// 09
		test_intersect_sets_the_object_on_the_intersection,			// 10
		test_the_hit_when_all_intersections_have_positive_t,		// 11
		test_the_hit_when_some_intersections_have_negative_t,		// 12
		test_the_hit_when_all_intersections_have_negative_t,		// 13
		test_the_hit_is_always_the_lowest_nonnegative_intersection, // 14
		test_translating_a_ray,										// 15
		test_scaling_a_ray,											// 16
		test_a_sphere_default_transformation,						// 17
		test_changing_a_sphere_transformation,						// 18
		test_intersecting_a_scaled_sphere_with_a_ray,				// 19
		test_intersecting_a_translated_sphere_with_a_ray,			// 20
	};

	printf("\n%sTESTING INTERSECTIONS:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
