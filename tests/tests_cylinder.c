#include "tests.h"

// TEST 01
void	test_a_ray_misses_a_cylinder(int num_test)
{
	// ASSERT
	t_shape		cyl = cylinder();
	t_point		origin[3] = {
		point(1, 0, 0),
		point(0, 0, 0),
		point(0, 0, -5)
	};
	t_vector	direction[3] = {
		normalize(vector(0, 1, 0)),
		normalize(vector(0, 1, 0)),
		normalize(vector(1, 1, 1))
	};
	t_ray		r[3] = {
		ray(origin[0], direction[0]),
		ray(origin[1], direction[1]),
		ray(origin[2], direction[2])
	};
	t_hit		*hit_list_result[3] = {0};
	t_hit		*hit_list_expected[3] = {0};

	// ACT
	local_intersect(&hit_list_result[0], cyl, r[0]);
	local_intersect(&hit_list_result[1], cyl, r[1]);
	local_intersect(&hit_list_result[2], cyl, r[2]);

	// ASSERT
	print_result(num_test, hit_list_expected[0], hit_list_result[0], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[1], hit_list_result[1], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[2], hit_list_result[2], hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&hit_list_result[0]);
	hit_clear_list(&hit_list_result[1]);
	hit_clear_list(&hit_list_result[2]);

	hit_clear_list(&hit_list_expected[0]);
	hit_clear_list(&hit_list_expected[1]);
	hit_clear_list(&hit_list_expected[2]);
}

// TEST 02
void	test_a_ray_strikes_a_cylinder(int num_test)
{
	// ASSERT
	t_shape		cyl = cylinder();

	t_point		origin[3] = {
		point(1, 0, -5),
		point(0, 0, -5),
		point(0.5, 0, -5)
	};
	t_vector	direction[3] = {
		normalize(vector(0, 0, 1)),
		normalize(vector(0, 0, 1)),
		normalize(vector(0.1, 1, 1))
	};

	t_ray		r[3] = {
		ray(origin[0], direction[0]),
		ray(origin[1], direction[1]),
		ray(origin[2], direction[2])
	};

	double		t0[3] = {5, 4, 6.80798};
	double		t1[3] = {5, 6, 7.08872};

	t_hit		*hit_list_result[3] = {0};
	t_hit		*hit_list_expected[3] = {0};

	add_intersection(&hit_list_expected[0], intersection(t0[0], cyl));
	add_intersection(&hit_list_expected[0], intersection(t1[0], cyl));

	add_intersection(&hit_list_expected[1], intersection(t0[1], cyl));
	add_intersection(&hit_list_expected[1], intersection(t1[1], cyl));

	add_intersection(&hit_list_expected[2], intersection(t0[2], cyl));
	add_intersection(&hit_list_expected[2], intersection(t1[2], cyl));

	// ACT
	local_intersect(&hit_list_result[0], cyl, r[0]);
	local_intersect(&hit_list_result[1], cyl, r[1]);
	local_intersect(&hit_list_result[2], cyl, r[2]);

	// ASSERT
	print_result(num_test, hit_list_expected[0], hit_list_result[0], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[1], hit_list_result[1], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[2], hit_list_result[2], hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&hit_list_result[0]);
	hit_clear_list(&hit_list_result[1]);
	hit_clear_list(&hit_list_result[2]);

	hit_clear_list(&hit_list_expected[0]);
	hit_clear_list(&hit_list_expected[1]);
	hit_clear_list(&hit_list_expected[2]);
}

// TEST 03
void	test_normal_vector_on_a_cylinder(int num_test)
{
	// ASSERT
	t_shape		cyl = cylinder();

	t_point		p[4] = {
		point(1, 0, 0),
		point(0, 5, -1),
		point(0, -2, 1),
		point(-1, 1, 0)
	};

	t_vector	normal[4] = {
		normalize(vector(1, 0, 0)),
		normalize(vector(0, 0, -1)),
		normalize(vector(0, 0, 1)),
		normalize(vector(-1, 0, 0))
	};

	t_vector	result[3];

	// ACT
	result[0] = normal_at(cyl, p[0]);
	result[1] = normal_at(cyl, p[1]);
	result[2] = normal_at(cyl, p[2]);

	// ASSERT
	print_result(num_test, &normal[0], &result[0], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &normal[1], &result[1], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &normal[2], &result[2], tuple_compare_test, print_ko_tuple);
}

// TEST 04
void	test_the_default_minimum_and_maximum_for_a_cylinder(int num_test)
{
	// ASSERT
	t_shape	cyl = cylinder();
	double	expected[2] = {-INFINITY, INFINITY};
	double	result[2];

	// ACT
	result[0] = cyl.cylinder_shape.minimum;
	result[1] = cyl.cylinder_shape.maximum;

	// ASSERT
	print_result(num_test, &expected[0], &result[0], float_compare_test, print_ko_float);
	print_result(num_test, &expected[1], &result[1], float_compare_test, print_ko_float);
}

// TEST 05
void	test_intersecting_a_constrained_cylinder(int num_test)
{
	// ASSERT
	t_shape		cyl = cylinder();
	t_ray		r[] = {
		ray(point(0, 1.5, 0), normalize(vector(0.1, 1, 0))),
		ray(point(0, 3, -5), normalize(vector(0, 0, 1))),
		ray(point(0, 0, -5), normalize(vector(0, 0, 1))),
		ray(point(0, 2, -5), normalize(vector(0, 0, 1))),
		ray(point(0, 1, -5), normalize(vector(0, 0, 1))),
		ray(point(0, 1.5, -2), normalize(vector(0, 0, 1)))
	};
	t_hit		*hit_list_result[6] = {};
	t_hit		*hit_list_expected[6] = {0};

	cyl.cylinder_shape.minimum = 1;
	cyl.cylinder_shape.maximum = 2;

	add_intersection(&hit_list_expected[5], intersection(1, cyl));
	add_intersection(&hit_list_expected[5], intersection(3, cyl));

	// ACT
	for (int i = 0; i < 6; i++)
		local_intersect(&hit_list_result[i], cyl, r[i]);

	// ASSERT
	print_result(num_test, hit_list_expected[0], hit_list_result[0], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[1], hit_list_result[1], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[2], hit_list_result[2], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[3], hit_list_result[3], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[4], hit_list_result[4], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[5], hit_list_result[5], hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	for (int i = 0; i < 6; i++)
		hit_clear_list(&hit_list_result[i]);

	for (int i = 0; i < 6; i++)
		hit_clear_list(&hit_list_expected[i]);
}

// TEST 06
void	test_the_default_closed_value_for_a_cylinder(int num_test)
{
	// ASSERT
	t_shape	cyl = cylinder();
	int		expected = 0;
	int		result;

	// ACT
	result = cyl.cylinder_shape.closed;

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);
}

// TEST 07
void	test_intersecting_the_caps_of_a_closed_cylinder(int num_test)
{
	// ASSERT
	t_shape		cyl = cylinder();
	cyl.cylinder_shape.minimum = 1;
	cyl.cylinder_shape.maximum = 2;
	cyl.cylinder_shape.closed = true;

	t_ray		r[] = {
		ray(point(0, 3, 0), normalize(vector(0, -1, 0))),
		ray(point(0, 3, -2), normalize(vector(0, -1, 2))),
		ray(point(0, 4, -2), normalize(vector(0, -1, 1))),
		ray(point(0, 0, -2), normalize(vector(0, 1, 2))),
		ray(point(0, -1, -2), normalize(vector(0, 1, 1)))
	};

	t_hit		*hit_list[5] = {0};

	int			intersect_count_expected[] = {2, 2, 2, 2, 2};
	int			intersect_count_result[5];

	// ACT
	for (int i = 0; i < 5; i++)
	{
		local_intersect(&hit_list[i], cyl, r[i]);
		intersect_count_result[i] = intersection_count(hit_list[i]);
	}

	// ASSERT
	print_result(num_test, &intersect_count_expected[0], &intersect_count_result[0], int_compare_test, print_ko_int);
	print_result(num_test, &intersect_count_expected[1], &intersect_count_result[1], int_compare_test, print_ko_int);
	print_result(num_test, &intersect_count_expected[2], &intersect_count_result[2], int_compare_test, print_ko_int);
	print_result(num_test, &intersect_count_expected[3], &intersect_count_result[3], int_compare_test, print_ko_int);
	print_result(num_test, &intersect_count_expected[4], &intersect_count_result[4], int_compare_test, print_ko_int);

	// CLEAR
	for (int i = 0; i < 5; i++)
		hit_clear_list(&hit_list[i]);
}

// TEST 08
void	test_the_normal_vector_on_a_cylinder_end_caps(int num_test)
{
	// ASSERT
	t_shape		cyl = cylinder();
	cyl.cylinder_shape.minimum = 1;
	cyl.cylinder_shape.maximum = 2;
	cyl.cylinder_shape.closed = true;

	t_point		p[6] = {
		point(0, 1, 0),
		point(0.5, 1, 0),
		point(0, 1, 0.5),
		point(0, 2, 0),
		point(0.5, 2, 0),
		point(0, 2, 0.5)
	};

	t_vector	normal[6] = {
		normalize(vector(0, -1, 0)),
		normalize(vector(0, -1, 0)),
		normalize(vector(0, -1, 0)),
		normalize(vector(0, 1, 0)),
		normalize(vector(0, 1, 0)),
		normalize(vector(0, 1, 0))
	};

	t_vector	result[6];

	// ACT
	for (int i = 0; i < 6; i++)
		result[i] = normal_at(cyl, p[i]);

	// ASSERT
	print_result(num_test, &normal[0], &result[0], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &normal[1], &result[1], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &normal[2], &result[2], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &normal[3], &result[3], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &normal[4], &result[4], tuple_compare_test, print_ko_tuple);
	print_result(num_test, &normal[5], &result[5], tuple_compare_test, print_ko_tuple);
}

int	main(void)
{
	void	(*test_funcs[])(int) =
	{
		test_a_ray_misses_a_cylinder,							// 01
		test_a_ray_strikes_a_cylinder,							// 02
		test_normal_vector_on_a_cylinder,						// 03
		test_the_default_minimum_and_maximum_for_a_cylinder,	// 04
		test_intersecting_a_constrained_cylinder,				// 05
		test_the_default_closed_value_for_a_cylinder,			// 06
		test_intersecting_the_caps_of_a_closed_cylinder,		// 07
	};

	printf("\n%sTESTING CYLINDERS:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++)
		test_funcs[i](i + 1);
	return (0);
}
