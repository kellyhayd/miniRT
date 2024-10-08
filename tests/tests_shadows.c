#include "tests.h"

// TEST 01
void	test_lighting_with_the_surface_in_shadow(int num_test)
{
	// ARRANGE
	t_shape		sphere1 = sphere();
	t_color		result;
	t_sight		sight;
	t_color		expected = color(0.1, 0.1, 0.1);

	t_light		light = point_light(point(0, 0, -10), color(1, 1, 1));
	t_material	m = material();
	t_point		position = point(0, 0, 0);
	sphere1.material = m;

	sight.eye = vector(0, 0, -1);
	sight.normal = vector(0, 0, -1);
	sight.in_shadow = true;

	// ACT
	result = lighting(sphere1, light, position, sight);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
}

// TEST 02
void	test_there_is_no_shadow_when_nothing_is_collinear_with_point_and_light(int num_test)
{
	// ARRANGE
	int			result;
	int			expected = false;
	t_world		w = default_world();
	t_point		p = point(0, 10, 0);

	// ACT
	result = is_shadowed(w, p, w.light);

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);

	// CLEAR
	world_clear(&w);
}

// TEST 03
void	test_the_shadow_when_an_object_is_between_the_point_and_the_light(int num_test)
{
	// ARRANGE
	int			result;
	int			expected = true;
	t_world		w = default_world();
	t_point		p = point(10, -10, 10);

	// ACT
	result = is_shadowed(w, p, w.light);

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);

	// CLEAR
	world_clear(&w);
}

// TEST 04
void	test_there_is_no_shadow_when_an_object_is_behind_the_light(int num_test)
{
	// ARRANGE
	int			result;
	int			expected = false;
	t_world		w = default_world();
	t_point		p = point(-20, 20, -20);

	// ACT
	result = is_shadowed(w, p, w.light);

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);

	// CLEAR
	world_clear(&w);
}

// TEST 05
void	test_there_is_no_shadow_when_an_object_is_behind_the_point(int num_test)
{
	// ARRANGE
	int		result;
	int		expected = false;
	t_world	w = default_world();
	t_point	p = point(-2, 2, -2);

	// ACT
	result = is_shadowed(w, p, w.light);

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);

	// CLEAR
	world_clear(&w);
}

// TEST 06
void	test_shade_hit_is_given_an_intersection_in_shadow(int num_test)
{
	// ARRANGE
	t_color		expected = color(0.1, 0.1, 0.1);
	t_color		result;
	t_ray		r;
	t_world		w;
	t_hit		hit;
	t_comps		comps;
	t_shape		sphere1;
	t_shape		sphere2;

	w = world();
	add_light(&w.light, point_light(point(0, 0, 10), color(1, 1, 1)));

	sphere1 = sphere();
	sphere2 = sphere();
	set_transformation(&sphere2, translation(0, 0, 10));
	add_shape(&w.shape, sphere1);
	add_shape(&w.shape, sphere2);

	r = ray(point(0, 0, 5), vector(0, 0, 1));
	hit = intersection(4, *w.shape->next);
	comps = prepare_computations(hit, r);

	// ACT
	result = shade_hit(w, comps);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	world_clear(&w);
}

// TEST 07
void	test_the_hit_should_offset_the_point(int num_test)
{
	// ARRANGE
	t_comps		expected;
	t_comps		result;
	t_ray		r;
	t_shape		shape;
	t_hit		h;
	int			expected_over_point_z = 1;
	int			result_over_point_z;
	int			expected_point_z = 1;
	int			result_point_z;

	r = ray(point(0, 0, -5), vector(0, 0, 1));
	shape = sphere();
	set_transformation(&shape, translation(0, 0, 1));
	h = intersection(5, shape);

	// ACT
	result = prepare_computations(h, r);
	result_over_point_z = result.over_point.z < -EPSILON / 2;
	result_point_z = result.point.z > result.over_point.z;

	// ASSERT
	print_result(num_test, &expected_over_point_z, &result_over_point_z, int_compare_test, print_ko_int);
	print_result(num_test, &expected_point_z, &result_point_z, int_compare_test, print_ko_int);

	// assert(result.over_point.z < -EPSILON / 2);
	// assert(result.point.z > result.over_point.z);
	// printf(BLUE "%2d" RESET " -> ", num_test);
	// printf("%s%2d%s - %s[ ✓ ]%s ", PURPLE, num_test, RESET, GREEN, RESET);
	// printf("If you see this message, the test passed.\n");
}

int	main()
{
	void(*test_funcs[])(int) =
	{
		test_lighting_with_the_surface_in_shadow,								// 01
		test_there_is_no_shadow_when_nothing_is_collinear_with_point_and_light,	// 02
		test_the_shadow_when_an_object_is_between_the_point_and_the_light,		// 03
		test_there_is_no_shadow_when_an_object_is_behind_the_light,				// 04
		test_there_is_no_shadow_when_an_object_is_behind_the_point,				// 05
		test_shade_hit_is_given_an_intersection_in_shadow,						// 06
		test_the_hit_should_offset_the_point,									// 07
	};

	printf("\n%sTESTING SHADOWS:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}
	return (0);
}
