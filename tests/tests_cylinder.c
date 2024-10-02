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
		vector(0, 1, 0),
		vector(0, 1, 0),
		vector(1, 1, 1)
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
		vector(0, 0, 1),
		vector(0, 0, 1),
		vector(0.1, 1, 1)
	};

	t_ray		r[3] = {
		ray(origin[0], direction[0]),
		ray(origin[1], direction[1]),
		ray(origin[2], direction[2])
	};

	double		t0[3] = {
		5,
		4,
		6.80798, // ATENÇÃO: Teste com problema!
	};
	double		t1[3] = {
		5,
		6,
		7.08872, // ATENÇÃO: Teste com problema!
	};

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
		vector(1, 0, 0),
		vector(0, 0, -1),
		vector(0, 0, 1),
		vector(-1, 0, 0)
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

void	test_intersecting_a_constrained_cylinder(int num_test)
{
	// ASSERT
	t_shape		cyl = cylinder();
	t_ray		r[] = {
		ray(point(0, 1.5, 0), vector(0.1, 1, 0)),
		ray(point(0, 3, -5), vector(0, 0, 1)),
		ray(point(0, 0, -5), vector(0, 0, 1)),
		ray(point(0, 2, -5), vector(0, 0, 1)),
		ray(point(0, 1, -5), vector(0, 0, 1)),
		ray(point(0, 1.5, -2), vector(0, 0, 1))
	};
	t_hit		*hit_list_result[6] = {};
	t_hit		*hit_list_expected[6] = {0};

	cyl.cylinder_shape.minimum = 1;
	cyl.cylinder_shape.maximum = 2;

	add_intersection(&hit_list_expected[5], intersection(1, cyl));
	add_intersection(&hit_list_expected[5], intersection(3, cyl));

	// ACT
	local_intersect(&hit_list_result[0], cyl, r[0]);
	local_intersect(&hit_list_result[1], cyl, r[1]);
	local_intersect(&hit_list_result[2], cyl, r[2]);
	local_intersect(&hit_list_result[3], cyl, r[3]);
	local_intersect(&hit_list_result[4], cyl, r[4]);
	local_intersect(&hit_list_result[5], cyl, r[5]);

	// ASSERT
	print_result(num_test, hit_list_expected[0], hit_list_result[0], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[1], hit_list_result[1], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[2], hit_list_result[2], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[3], hit_list_result[3], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[4], hit_list_result[4], hit_list_compare_test, print_ko_hit_list);
	print_result(num_test, hit_list_expected[5], hit_list_result[5], hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	hit_clear_list(&hit_list_result[0]);
	hit_clear_list(&hit_list_result[1]);
	hit_clear_list(&hit_list_result[2]);
	hit_clear_list(&hit_list_result[3]);
	hit_clear_list(&hit_list_result[4]);
	hit_clear_list(&hit_list_result[5]);

	hit_clear_list(&hit_list_expected[0]);
	hit_clear_list(&hit_list_expected[1]);
	hit_clear_list(&hit_list_expected[2]);
	hit_clear_list(&hit_list_expected[3]);
	hit_clear_list(&hit_list_expected[4]);
	hit_clear_list(&hit_list_expected[5]);
}

int	main(void)
{
	void	(*test_funcs[])(int) =
	{
		test_a_ray_misses_a_cylinder,
		test_a_ray_strikes_a_cylinder,
		test_normal_vector_on_a_cylinder,
		test_the_default_minimum_and_maximum_for_a_cylinder,
		test_intersecting_a_constrained_cylinder,
	};

	printf("\n%sTESTING CYLINDERS:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++)
		test_funcs[i](i + 1);
	return (0);
}
