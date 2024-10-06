#include "tests.h"

// TEST 01
void	test_creating_a_stripe_pattern(int num_test)
{
	// ARRANGE
	t_color		black = color(0, 0, 0);
	t_color		white = color(1, 1, 1);

	t_pattern	expected = {.has_pattern = true, .color_a = white, .color_b = black};
	t_pattern	result;

	// ACT
	result = stripe_pattern(white, black);

	// ASSERT
	print_result(num_test, &expected, &result, pattern_compare_test, print_ko_pattern);
}

// TEST 02
void	test_the_stripe_pattern_is_constant_in_y(int num_test)
{
	// ARRANGE
	t_color		black = color(0, 0, 0);
	t_color		white = color(1, 1, 1);
	t_pattern	pattern = stripe_pattern(white, black);
	t_color		result[3];
	t_color		expected[3] = {white, white, white};

	// ACT
	result[0] = stripe_at(pattern, point(0, 0, 0));
	result[1] = stripe_at(pattern, point(0, 1, 0));
	result[2] = stripe_at(pattern, point(0, 2, 0));

	// ASSERT
	print_result(num_test, &expected, &result[0], color_compare_test, print_ko_color);
	print_result(num_test, &expected, &result[1], color_compare_test, print_ko_color);
	print_result(num_test, &expected, &result[2], color_compare_test, print_ko_color);
}

// TEST 03
void	test_the_stripe_pattern_is_constant_in_z(int num_test)
{
	// ARRANGE
	t_color		black = color(0, 0, 0);
	t_color		white = color(1, 1, 1);
	t_pattern	pattern = stripe_pattern(white, black);
	t_color		result[3];
	t_color		expected[3] = {white, white, white};

	// ACT
	result[0] = stripe_at(pattern, point(0, 0, 0));
	result[1] = stripe_at(pattern, point(0, 0, 1));
	result[2] = stripe_at(pattern, point(0, 0, 2));

	// ASSERT
	print_result(num_test, &expected, &result[0], color_compare_test, print_ko_color);
	print_result(num_test, &expected, &result[1], color_compare_test, print_ko_color);
	print_result(num_test, &expected, &result[2], color_compare_test, print_ko_color);
}

// TEST 04
void	test_the_stripe_pattern_alternates_in_x(int num_test)
{
	// ARRANGE
	t_color		black = color(0, 0, 0);
	t_color		white = color(1, 1, 1);
	t_pattern	pattern = stripe_pattern(white, black);
	t_color		result[6];
	t_color		expected[6] = {white, white, black, black, black, white};

	// ACT
	result[0] = stripe_at(pattern, point(0, 0, 0));
	result[1] = stripe_at(pattern, point(0.9, 0, 0));
	result[2] = stripe_at(pattern, point(1, 0, 0));
	result[3] = stripe_at(pattern, point(-0.1, 0, 0));
	result[4] = stripe_at(pattern, point(-1, 0, 0));
	result[5] = stripe_at(pattern, point(-1.1, 0, 0));

	// ASSERT
	print_result(num_test, &expected[0], &result[0], color_compare_test, print_ko_color);
	print_result(num_test, &expected[1], &result[1], color_compare_test, print_ko_color);
	print_result(num_test, &expected[2], &result[2], color_compare_test, print_ko_color);
	print_result(num_test, &expected[3], &result[3], color_compare_test, print_ko_color);
	print_result(num_test, &expected[4], &result[4], color_compare_test, print_ko_color);
	print_result(num_test, &expected[5], &result[5], color_compare_test, print_ko_color);
}

// TEST 05
void	test_lighting_with_a_pattern_applied(int num_test)
{
	// ARRANGE
	t_color		color1 = color(1, 1, 1);
	t_color		color2 = color(0, 0, 0);

	t_material	m = material();
	m.pattern = stripe_pattern(color1, color2);
	m.ambient = 1;
	m.diffuse = 0;
	m.specular = 0;

	t_shape	sphere1 = sphere();
	sphere1.material = m;

	t_sight	sight = {
		.eye = vector(0, 0, -1),
		.normal = vector(0, 0, -1),
		.in_shadow = false
	};
	t_light	light = point_light(point(0, 0, -10), color(1, 1, 1));

	t_point	point1 = point(0.9, 0, 0);
	t_point	point2 = point(1.1, 0, 0);

	t_color	color_result[2];
	t_color	color_expected[2] = {color1, color2};

	// ACT
	color_result[0] = lighting(sphere1, light, point1, sight);
	color_result[1] = lighting(sphere1, light, point2, sight);

	// ASSERT
	print_result(num_test, &color_expected[0], &color_result[0], color_compare_test, print_ko_color);
	print_result(num_test, &color_expected[1], &color_result[1], color_compare_test, print_ko_color);
}

// TEST 06
void	test_stripes_with_an_object_transformation(int num_test)
{
	// ARRANGE
	t_color		black = color(0, 0, 0);
	t_color		white = color(1, 1, 1);

	t_shape		sphere1 = sphere();
	set_transformation(&sphere1, scaling(2, 2, 2));

	t_pattern	pattern = stripe_pattern(white, black);
	t_color		result;
	t_color		expected = white;

	// ACT
	result = pattern_at_shape(pattern, sphere1, point(1.5, 0, 0));

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
}

// TEST 07
void	test_stripes_with_a_pattern_transformation(int num_test)
{
	// ARRANGE
	t_color		black = color(0, 0, 0);
	t_color		white = color(1, 1, 1);

	t_shape		sphere1 = sphere();
	t_pattern	pattern = stripe_pattern(white, black);
	set_pattern_transformation(&pattern, scaling(2, 2, 2));

	t_color		result;
	t_color		expected = white;

	// ACT
	result = pattern_at_shape(pattern, sphere1, point(1.5, 0, 0));

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
}

// TEST 08
void	test_stripes_with_both_an_object_and_a_pattern_transformation(int num_test)
{
	// ARRANGE
	t_color		black = color(0, 0, 0);
	t_color		white = color(1, 1, 1);

	t_shape		sphere1 = sphere();
	set_transformation(&sphere1, scaling(2, 2, 2));

	t_pattern	pattern = stripe_pattern(white, black);
	set_pattern_transformation(&pattern, translation(0.5, 0, 0));

	t_color		result;
	t_color		expected = white;

	// ACT
	result = pattern_at_shape(pattern, sphere1, point(2.5, 0, 0));

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);
}

// TEST 09
void	test_a_gradient_linearly_interpolates_between_colors(int num_test)
{
	// ASSERT
	t_color		white = color(1, 1, 1);
	t_color		black = color(0, 0, 0);
	t_shape		sphere1 = sphere();
	t_pattern	pattern = gradient_pattern(white, black);
	t_color		result[4];
	t_color		expected[4] = {
		white,
		color(0.75, 0.75, 0.75),
		color(0.5, 0.5, 0.5),
		color(0.25, 0.25, 0.25)
	};

	// ACT
	result[0] = pattern_at_shape(pattern, sphere1, point(0, 0, 0));
	result[1] = pattern_at_shape(pattern, sphere1, point(0.25, 0, 0));
	result[2] = pattern_at_shape(pattern, sphere1, point(0.5, 0, 0));
	result[3] = pattern_at_shape(pattern, sphere1, point(0.75, 0, 0));

	// ASSERT
	print_result(num_test, &expected[0], &result[0], color_compare_test, print_ko_color);
	print_result(num_test, &expected[1], &result[1], color_compare_test, print_ko_color);
	print_result(num_test, &expected[2], &result[2], color_compare_test, print_ko_color);
	print_result(num_test, &expected[3], &result[3], color_compare_test, print_ko_color);
}

// TEST 10
void	test_gradient_with_smooth_transition_with_positive_values(int num_test)
{
	// ASSERT
	t_color		white = color(1, 1, 1);
	t_color		black = color(0, 0, 0);
	t_shape		sphere1 = sphere();
	t_pattern	pattern = gradient_pattern(white, black);
	t_color		result[9];
	t_color		expected[9] = {
		white,
		color(0.75, 0.75, 0.75),
		color(0.5, 0.5, 0.5),
		color(0.25, 0.25, 0.25),
		black,
		color(0.25, 0.25, 0.25),
		color(0.5, 0.5, 0.5),
		color(0.75, 0.75, 0.75),
		white
	};

	// ACT
	result[0] = pattern_at_shape(pattern, sphere1, point(0, 0, 0));
	result[1] = pattern_at_shape(pattern, sphere1, point(0.25, 0, 0));
	result[2] = pattern_at_shape(pattern, sphere1, point(0.5, 0, 0));
	result[3] = pattern_at_shape(pattern, sphere1, point(0.75, 0, 0));
	result[4] = pattern_at_shape(pattern, sphere1, point(1, 0, 0));
	result[5] = pattern_at_shape(pattern, sphere1, point(1.25, 0, 0));
	result[6] = pattern_at_shape(pattern, sphere1, point(1.5, 0, 0));
	result[7] = pattern_at_shape(pattern, sphere1, point(1.75, 0, 0));
	result[8] = pattern_at_shape(pattern, sphere1, point(2, 0, 0));

	// ASSERT
	for (int i = 0; i < 9; i++)
		print_result(num_test, &expected[i], &result[i], color_compare_test, print_ko_color);
}

// TEST 11
void	test_gradient_with_smooth_transition_with_negative_values(int num_test)
{
	// ASSERT
	t_color		white = color(1, 1, 1);
	t_color		black = color(0, 0, 0);
	t_shape		sphere1 = sphere();
	t_pattern	pattern = gradient_pattern(white, black);
	t_color		result[9];
	t_color		expected[9] = {
		white,
		color(0.75, 0.75, 0.75),
		color(0.5, 0.5, 0.5),
		color(0.25, 0.25, 0.25),
		black,
		color(0.25, 0.25, 0.25),
		color(0.5, 0.5, 0.5),
		color(0.75, 0.75, 0.75),
		white
	};

	// ACT
	result[0] = pattern_at_shape(pattern, sphere1, point(0, 0, 0));
	result[1] = pattern_at_shape(pattern, sphere1, point(-0.25, 0, 0));
	result[2] = pattern_at_shape(pattern, sphere1, point(-0.5, 0, 0));
	result[3] = pattern_at_shape(pattern, sphere1, point(-0.75, 0, 0));
	result[4] = pattern_at_shape(pattern, sphere1, point(-1, 0, 0));
	result[5] = pattern_at_shape(pattern, sphere1, point(-1.25, 0, 0));
	result[6] = pattern_at_shape(pattern, sphere1, point(-1.5, 0, 0));
	result[7] = pattern_at_shape(pattern, sphere1, point(-1.75, 0, 0));
	result[8] = pattern_at_shape(pattern, sphere1, point(-2, 0, 0));

	// ASSERT
	for (int i = 0; i < 9; i++)
		print_result(num_test, &expected[i], &result[i], color_compare_test, print_ko_color);
}

// TEST 12
void	test_a_ring_should_extend_in_both_x_and_z(int num_test)
{
	// ASSERT
	t_color		white = color(1, 1, 1);
	t_color		black = color(0, 0, 0);
	t_shape		sphere1 = sphere();
	t_pattern	pattern = ring_pattern(white, black);
	t_color		result[4];
	t_color		expected[4] = {
		white,
		black,
		black,
		black
	};

	// ACT
	result[0] = pattern_at_shape(pattern, sphere1, point(0, 0, 0));
	result[1] = pattern_at_shape(pattern, sphere1, point(1, 0, 0));
	result[2] = pattern_at_shape(pattern, sphere1, point(0, 0, 1));
	result[3] = pattern_at_shape(pattern, sphere1, point(0.708, 0, 0.708));

	// ASSERT
	for (int i = 0; i < 4; i++)
		print_result(num_test, &expected[i], &result[i], color_compare_test, print_ko_color);
}

// TEST 13
void	test_checkers_should_repeat_in_x(int num_test)
{
	// ASSERT
	t_color		white = color(1, 1, 1);
	t_color		black = color(0, 0, 0);
	t_shape		sphere1 = sphere();
	t_pattern	pattern = checkers_pattern(white, black);
	t_color		result[3];
	t_color		expected[3] = {
		white,
		white,
		black
	};

	// ACT
	result[0] = pattern_at_shape(pattern, sphere1, point(0, 0, 0));
	result[1] = pattern_at_shape(pattern, sphere1, point(0.99, 0, 0));
	result[2] = pattern_at_shape(pattern, sphere1, point(1.01, 0, 0));

	// ASSERT
	for (int i = 0; i < 3; i++)
		print_result(num_test, &expected[i], &result[i], color_compare_test, print_ko_color);
}

// TEST 14
void	test_checkers_should_repeat_in_y(int num_test)
{
	// ASSERT
	t_color		white = color(1, 1, 1);
	t_color		black = color(0, 0, 0);
	t_shape		sphere1 = sphere();
	t_pattern	pattern = checkers_pattern(white, black);
	t_color		result[3];
	t_color		expected[3] = {
		white,
		white,
		black
	};

	// ACT
	result[0] = pattern_at_shape(pattern, sphere1, point(0, 0, 0));
	result[1] = pattern_at_shape(pattern, sphere1, point(0, 0.99, 0));
	result[2] = pattern_at_shape(pattern, sphere1, point(0, 1.01, 0));

	// ASSERT
	for (int i = 0; i < 3; i++)
		print_result(num_test, &expected[i], &result[i], color_compare_test, print_ko_color);
}

void	int_checkers_should_repeat_in_z(int num_test)
{
	// ASSERT
	t_color		white = color(1, 1, 1);
	t_color		black = color(0, 0, 0);
	t_shape		sphere1 = sphere();
	t_pattern	pattern = checkers_pattern(white, black);
	t_color		result[3];
	t_color		expected[3] = {
		white,
		white,
		black
	};

	// ACT
	result[0] = pattern_at_shape(pattern, sphere1, point(0, 0, 0));
	result[1] = pattern_at_shape(pattern, sphere1, point(0, 0, 0.99));
	result[2] = pattern_at_shape(pattern, sphere1, point(0, 0, 1.01));

	// ASSERT
	for (int i = 0; i < 3; i++)
		print_result(num_test, &expected[i], &result[i], color_compare_test, print_ko_color);
}

int main(void)
{
	void	(*test_funcs[])(int) =
	{
		test_creating_a_stripe_pattern,									// 01
		test_the_stripe_pattern_is_constant_in_y,						// 02
		test_the_stripe_pattern_is_constant_in_z,						// 03
		test_the_stripe_pattern_alternates_in_x,						// 04
		test_lighting_with_a_pattern_applied,							// 05
		test_stripes_with_an_object_transformation,						// 06
		test_stripes_with_a_pattern_transformation,						// 07
		test_stripes_with_both_an_object_and_a_pattern_transformation,	// 08
		test_a_gradient_linearly_interpolates_between_colors,			// 09
		test_gradient_with_smooth_transition_with_positive_values,		// 10
		test_gradient_with_smooth_transition_with_negative_values,		// 11
		test_a_ring_should_extend_in_both_x_and_z,						// 12
		test_checkers_should_repeat_in_x,								// 13
		test_checkers_should_repeat_in_y,								// 14
		int_checkers_should_repeat_in_z,								// 15
	};

	printf("\n%sTESTING PATTERNS:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++)
		test_funcs[i](i + 1);
	return (0);
}
