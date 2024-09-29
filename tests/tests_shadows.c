#include "tests.h"

// TEST 01
void	test_lighting_with_the_surface_in_shadow(int num_test)
{
	// ARRANGE
	t_color		result;
	t_sight		sight;
	t_color		expected = color(0.1, 0.1, 0.1);

	t_light		light = point_light(point(0, 0, -10), color(1, 1, 1));
	t_material	m = material();
	t_point		position = point(0, 0, 0);
	sight.eye = vector(0, 0, -1);
	sight.normal = vector(0, 0, -1);
	sight.in_shadow = true;

	// ACT
	result = lighting(m, light, position, sight);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
}

// TEST 02
void	test_there_is_no_shadow_when_nothing_is_collinear_with_point_and_light(int num_test)
{
	// ARRANGE
	int		result;
	int		expected = false;
	t_world		w = default_world();
	t_point		p = point(0, 10, 0);

	// ACT
	result = is_shadowed(w, p);

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);
}

// TEST 03
void	test_the_shadow_when_an_object_is_between_the_point_and_the_light(int num_test)
{
	// ARRANGE
	int		result;
	int		expected = true;
	t_world		w = default_world();
	t_point		p = point(10, -10, 10);

	// ACT
	result = is_shadowed(w, p);

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);
}

// TEST 04
void	test_there_is_no_shadow_when_an_object_is_behind_the_light(int num_test)
{
	// ARRANGE
	int		result;
	int		expected = false;
	t_world		w = default_world();
	t_point		p = point(-20, 20, -20);

	// ACT
	result = is_shadowed(w, p);

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);
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
	result = is_shadowed(w, p);

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);
}

// // TEST 06
// void	test_shade_hit_is_given_an_intersection_in_shadow(int num_test)
// {
// 	// ARRANGE
// 	t_color		expected = color(0.1, 0.1, 0.1);
// 	t_color		result;
// 	t_ray		r;
// 	t_world		w;
// 	t_hit		hit;
// 	t_comp		comps;

// 	w = world();
// 	*w.light = point_light(point(0, 0, -10), color(1, 1, 1));
// 	w.shape[0]	= sphere();
// 	w.shape[1]	= sphere();
// 	set_transformation(&w.shape[1], translation(0, 0, 10));
// 	r = ray(point(0, 0, 5), vector(0, 0, 1));
// 	hit = intersection(4, w.shape[1]);
// 	comps = prepare_computations(hit, r);

// 	// ACT
// 	result = shade_hit(w, comps);

// 	// ASSERT
// 	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
// }


int	main()
{
	void(*test_funcs[])(int) =
	{
		// test_lighting_with_the_surface_in_shadow,								// 01
		test_there_is_no_shadow_when_nothing_is_collinear_with_point_and_light,	// 02
		test_the_shadow_when_an_object_is_between_the_point_and_the_light,		// 03
		test_there_is_no_shadow_when_an_object_is_behind_the_light,				// 04
		test_there_is_no_shadow_when_an_object_is_behind_the_point,				// 05
		// test_shade_hit_is_given_an_intersection_in_shadow,						// 06
	};

	printf("\n%sTESTING SHADOWS:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}
	return (0);
}
