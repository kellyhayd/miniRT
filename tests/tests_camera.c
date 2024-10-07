#include "tests.h"

// TEST 01
void	test_constructing_a_camera(int num_test)
{
	// ARRANGE
	t_camera	expected;
	t_camera	result;

	expected.hsize = 160;
	expected.vsize = 120;
	expected.field_of_view = M_PI_2;
	expected.transform = identity();
	expected.half_width = 1;
	expected.half_height = 0.75;
	expected.pixel_size = 0.01;

	// ACT
	result = camera(160, 120, M_PI_2);

	// ASSERT
	print_result(num_test, &expected, &result, camera_compare_test, print_ko_camera);
}

// TEST 02
void	test_the_pixel_size_for_a_horizontal_canvas(int num_test)
{
	// ARRANGE
	t_camera	result;
	t_camera	expected;

	expected.hsize = 200;
	expected.vsize = 125;
	expected.field_of_view = M_PI_2;
	expected.transform = identity();
	expected.pixel_size = 0.01;

	// ACT
	result = camera(200, 125, M_PI_2);

	// ASSERT
	print_result(num_test, &expected, &result, camera_compare_test, print_ko_camera);
}

// TEST 03
void	test_the_pixel_size_for_a_vertical_canvas(int num_test)
{
	// ARRANGE
	t_camera	result;
	t_camera	expected;

	expected.hsize = 125;
	expected.vsize = 200;
	expected.field_of_view = M_PI_2;
	expected.transform = identity();
	expected.pixel_size = 0.01;

	// ACT
	result = camera(125, 200, M_PI_2);

	// ASSERT
	print_result(num_test, &expected, &result, camera_compare_test, print_ko_camera);
}

// TEST 04
void	test_constructing_a_ray_through_the_center_of_the_canvas(int num_test)
{
	// ARRANGE
	t_camera	c;
	t_ray		result;
	t_ray		expected;

	c = camera(201, 101, M_PI / 2);
	expected.origin = point(0, 0, 0);
	expected.direction = vector(0, 0, -1);

	// ACT
	result = ray_for_pixel(c, 100, 50);

	// ASSERT
	print_result(num_test, &expected, &result, ray_compare_test, print_ko_ray);
}

// TEST 05
void	test_constructing_a_ray_through_a_corner_of_the_canvas(int num_test)
{
	// ARRANGE
	t_camera	c;
	t_ray		result;
	t_ray		expected;

	c = camera(201, 101, M_PI / 2);
	expected.origin = point(0, 0, 0);
	expected.direction = vector(0.66519, 0.33259, -0.66851);

	// ACT
	result = ray_for_pixel(c, 0, 0);

	// ASSERT
	print_result(num_test, &expected, &result, ray_compare_test, print_ko_ray);
}

// TEST 06
void	test_constructing_a_ray_when_the_camera_is_transformed(int num_test)
{
	// ARRANGE
	t_camera	c;
	t_ray		result;
	t_ray		expected;

	c = camera(201, 101, M_PI / 2);
	c.transform = mx_multiply(rotation_y(M_PI / 4), translation(0, -2, 5));
	expected.origin = point(0, 2, -5);
	expected.direction = vector((sqrt(2) / 2), 0, -(sqrt(2) / 2));

	// ACT
	result = ray_for_pixel(c, 100, 50);

	// ASSERT
	print_result(num_test, &expected, &result, ray_compare_test, print_ko_ray);
}

// TEST 07
void	test_rendering_a_world_with_a_camera(int num_test)
{
	// ARRANGE
	t_world		w;
	t_camera	c;
	t_canvas	image;
	t_color		result;
	t_color		expected;

	w = default_world();
	c = camera(11, 11, M_PI / 2);
	c.transform = view_transform(point(0, 0, -5), point(0, 0, 0), vector(0, 1, 0));
	image = render(c, w);
	expected = color(0.38066, 0.47583, 0.2855);

	// ACT
	result = pixel_at(image, 5, 5);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	world_clear(&w);
	free(image.pixels);
}

int main(void)
{
	void	(*test_funcs[])(int) =
	{
		test_constructing_a_camera,									// 01
		test_the_pixel_size_for_a_horizontal_canvas,				// 02
		test_the_pixel_size_for_a_vertical_canvas,					// 03
		test_constructing_a_ray_through_the_center_of_the_canvas,	// 04
		test_constructing_a_ray_through_a_corner_of_the_canvas,		// 05
		test_constructing_a_ray_when_the_camera_is_transformed,		// 06
		test_rendering_a_world_with_a_camera,						// 07
	};

	printf("\n%sTESTING CAMERA CREATION:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++)
		test_funcs[i](i + 1);
	return (0);
}
