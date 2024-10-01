#include "tests.h"

// TEST 01
void	test_the_normal_of_a_plane_is_constant_everywhere(int num_test)
{
	// ARRANGE
	t_shape		p = plane();
	t_point		n1;
	t_point		n2;
	t_point		n3;
	t_vector	expected_n1 = vector(0, 1, 0);
	t_vector	expected_n2 = vector(0, 1, 0);
	t_vector	expected_n3 = vector(0, 1, 0);

	// ACT
	n1 = normal_at(p, point(0, 0, 0));
	n2 = normal_at(p, point(10, 0, -10));
	n3 = normal_at(p, point(-5, 0, 150));

	// ASSERT
	print_result(num_test, &expected_n1, &n1, tuple_compare_test, print_ko_tuple);
	print_result(num_test, &expected_n2, &n2, tuple_compare_test, print_ko_tuple);
	print_result(num_test, &expected_n3, &n3, tuple_compare_test, print_ko_tuple);
}

// TEST 02
void	test_intersect_with_a_ray_parallel_to_the_plane(int num_test)
{
	// ARRANGE
	t_shape	p = plane();
	t_ray	r = ray(point(0, 10, 0), vector(0, 0, 1));
	t_hit	*hit_list_result = NULL;
	t_hit	*hit_list_expected = NULL;

	// ACT
	intersect(&hit_list_result, p, r);

	// ASSERT
	print_result(num_test, hit_list_expected, hit_list_result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&hit_list_result);
	hit_clear_list(&hit_list_expected);
}

// TEST 03
void	test_intersect_with_a_coplanar_ray(int num_test)
{
	// ARRANGE
	t_shape	p = plane();
	t_ray	r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_hit	*hit_list_result = NULL;
	t_hit	*hit_list_expected = NULL;

	// ACT
	intersect(&hit_list_result, p, r);

	// ASSERT
	print_result(num_test, hit_list_expected, hit_list_result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&hit_list_result);
	hit_clear_list(&hit_list_expected);
}

// TEST 04
void	test_a_ray_intersecting_a_plane_from_above(int num_test)
{
	// ARRANGE
	t_shape	p = plane();
	t_ray	r = ray(point(0, 1, 0), vector(0, -1, 0));
	t_hit	*hit_list_result = NULL;
	t_hit	*hit_list_expected = NULL;

	add_intersection(&hit_list_expected, intersection(1, p));

	// ACT
	intersect(&hit_list_result, p, r);

	// ASSERT
	print_result(num_test, hit_list_expected, hit_list_result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&hit_list_result);
	hit_clear_list(&hit_list_expected);
}

// TEST 05
void	test_a_ray_intersecting_a_plane_from_below(int num_test)
{
	// ARRANGE
	t_shape	p = plane();
	t_ray	r = ray(point(0, -1, 0), vector(0, 1, 0));
	t_hit	*hit_list_result = NULL;
	t_hit	*hit_list_expected = NULL;

	add_intersection(&hit_list_expected, intersection(1, p));

	// ACT
	intersect(&hit_list_result, p, r);

	// ASSERT
	print_result(num_test, hit_list_expected, hit_list_result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&hit_list_result);
	hit_clear_list(&hit_list_expected);
}

// TEST 06
void	test_a_ray_intersection_a_plane_transformed(int num_test)
{
	// ARRANGE
	t_shape	p = plane();
	t_matrix	transform = translation(0, 5, 0);
	t_ray		r = ray(point(0, 10, 0), vector(0, -1, 0));
	t_hit		*hit_list_result = NULL;
	t_hit		*hit_list_expected = NULL;

	add_intersection(&hit_list_expected, intersection(5, p));
	set_transformation(&p, transform);

	// ACT
	intersect(&hit_list_result, p, r);

	// ASSERT
	print_result(num_test, hit_list_expected, hit_list_result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&hit_list_result);
	hit_clear_list(&hit_list_expected);
}

int	main()
{
	void(*test_funcs[])(int) =
	{
		test_the_normal_of_a_plane_is_constant_everywhere,	// 01
		test_intersect_with_a_ray_parallel_to_the_plane,	// 02
		test_intersect_with_a_coplanar_ray,					// 03
		test_a_ray_intersecting_a_plane_from_above,			// 04
		test_a_ray_intersecting_a_plane_from_below,			// 05
		test_a_ray_intersection_a_plane_transformed			// 06
	};

	printf("\n%sTESTING SHADOWS:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}
	return (0);
}
