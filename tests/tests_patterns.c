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
	color_result[0] = lighting(m, light, point1, sight);
	color_result[1] = lighting(m, light, point2, sight);

	// ASSERT
	print_result(num_test, &color_expected[0], &color_result[0], color_compare_test, print_ko_color);
	print_result(num_test, &color_expected[1], &color_result[1], color_compare_test, print_ko_color);
}

int main(void)
{
	void	(*test_funcs[])(int) =
	{
		test_creating_a_stripe_pattern,
		test_the_stripe_pattern_is_constant_in_y,
		test_the_stripe_pattern_is_constant_in_z,
		test_the_stripe_pattern_alternates_in_x,
		test_lighting_with_a_pattern_applied,
	};

	printf("\n%sTESTING PATTERNS:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++)
		test_funcs[i](i + 1);
	return (0);
}
