#include "tests.h"

void	test_intersecting_a_cone_with_a_ray(int num_test)
{
	// ASSERT
	t_shape	cn = cone();
	t_ray	r[] = {
		ray(point(0, 0, -5), normalize(vector(0, 0, 1))),
		ray(point(0, 0, -5), normalize(vector(1, 1, 1))),
		ray(point(1, 1, -5), normalize(vector(-0.5, -1, 1)))
	};
	t_hit	*hit_list_result[3] = {0};
	t_hit	*hit_list_expected[3] = {0};

	add_intersection(&hit_list_expected[0], intersection(5, cn));
	add_intersection(&hit_list_expected[0], intersection(5, cn));

	add_intersection(&hit_list_expected[1], intersection(8.66025, cn));
	add_intersection(&hit_list_expected[1], intersection(8.66025, cn));

	add_intersection(&hit_list_expected[2], intersection(4.55006, cn));
	add_intersection(&hit_list_expected[2], intersection(49.44994, cn));

	// ACT
	local_intersect(&hit_list_result[0], cn, r[0]);
	local_intersect(&hit_list_result[1], cn, r[1]);
	local_intersect(&hit_list_result[2], cn, r[2]);

	// ASSERT
	print_result(num_test, hit_list_expected[0], hit_list_result[0], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[1], hit_list_result[1], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[2], hit_list_result[2], hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	for (int i = 0; i < 3; i++)
		hit_clear_list(&hit_list_result[i]);
	for (int i = 0; i < 3; i++)
		hit_clear_list(&hit_list_expected[i]);
}

void	test_intersecting_a_cone_with_a_ray_parallel_to_one_of_its_halves(int num_test)
{
	// ASSERT
	t_shape	cn = cone();
	t_ray	r = ray(point(0, 0, -1), normalize(vector(0, 1, 1)));
	t_hit	*hit_list_result = NULL;
	t_hit	*hit_list_expected = NULL;

	add_intersection(&hit_list_expected, intersection(0.35355, cn));

	// ACT
	local_intersect(&hit_list_result, cn, r);

	// ASSERT
	print_result(num_test, hit_list_expected, hit_list_result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&hit_list_result);
	hit_clear_list(&hit_list_expected);
}

void	test_intersecting_a_cone_s_end_caps(int num_test)
{
	t_shape	cn = cone();
	cn.cone_shape.minimum = -0.5;
	cn.cone_shape.maximum = 0.5;
	cn.cone_shape.closed = true;

	t_ray	r[] = {
		ray(point(0, 0, -5), normalize(vector(0, 1, 0))),
		ray(point(0, 0, -0.25), normalize(vector(0, 1, 1))),
		ray(point(0, 0, -0.25), normalize(vector(0, 1, 0))),
	};
	t_hit	*hit_list[3] = {0};

	int	hit_count_expected[3] = {0, 2, 4};
	int	hit_count_result[3];

	// ACT
	for (int i = 0; i < 3; i++)
	{
		local_intersect(&hit_list[i], cn, r[i]);
		hit_count_result[i] = intersection_count(hit_list[i]);
	}

	// ASSERT
	print_result(num_test, &hit_count_expected[0], &hit_count_result[0], int_compare_test, print_ko_int);
	print_result(num_test, &hit_count_expected[1], &hit_count_result[1], int_compare_test, print_ko_int);
	print_result(num_test, &hit_count_expected[2], &hit_count_result[2], int_compare_test, print_ko_int);

	// CLEAR
	for (int i = 0; i < 3; i++)
		hit_clear_list(&hit_list[i]);
}

void	test_computing_the_normal_vector_on_a_cone(int num_test)
{
	// ASSERT
	t_shape	cn = cone();
	t_point	p[] = {
		point(0, 0, 0),
		point(1, 1, 1),
		point(-1, -1, 0),
	};
	t_vector	normal_expected[] = {
		vector(0, 0, 0),
		vector(1, -sqrt(2), 1),
		vector(-1, 1, 0),
	};
	t_vector	normal_result[3];

	// ACT
	normal_result[0] = normal_at_cone(cn, p[0]);
	normal_result[1] = normal_at_cone(cn, p[1]);
	normal_result[2] = normal_at_cone(cn, p[2]);

	// ASSERT
	print_result(num_test, &normal_expected[0], &normal_result[0], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &normal_expected[1], &normal_result[1], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &normal_expected[2], &normal_result[2], tuple_compare_test, print_ko_tuple);
}

int	main(void)
{
	void	(*test_funcs[])(int) =
	{
		test_intersecting_a_cone_with_a_ray,								// 01
		test_intersecting_a_cone_with_a_ray_parallel_to_one_of_its_halves,	// 02
		test_intersecting_a_cone_s_end_caps,								// 03
		test_computing_the_normal_vector_on_a_cone,							// 04
	};

	printf("\n%sTESTING CONES:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++)
		test_funcs[i](i + 1);
	return (0);
}
