#include "tests.h"

// TEST 01
void	test_checker_patter_in_2D(int num_test)
{
	// ARRANGE
	t_color	black = color(0, 0, 0);
	t_color	white = color(1, 1, 1);

	t_checkers	checkers = uv_checkers(2, 2, black, white);

	double	u[] = {0.0, 0.5, 0.0, 0.5, 1.0};
	double	v[] = {0.0, 0.0, 0.5, 0.5, 1.0};
	t_color	expected[] = {
		black, white, white, black, black
	};
	t_color	result;

	// ACT / ASSERT
	for (int i = 0; i < 5; i++)
	{
		result = uv_pattern_at(checkers, u[i], v[i]);
		print_result(num_test, &expected[i], &result, color_compare_test, print_ko_color);
	}
}

// TEST 02
void	test_using_a_spherical_mapping_on_a_3D_point(int num_test)
{
	t_point	p[] = {
		point(0, 0, -1),
		point(1, 0, 0),
		point(0, 0, 1),
		point(-1, 0, 0),
		point(0, 1, 0),
		point(0, -1, 0),
		point(sqrt(2) / 2, sqrt(2) / 2, 0)
	};

	double	u[] = {0.0, 0.25, 0.5, 0.75, 0.5, 0.5, 0.25};
	double	v[] = {0.5, 0.5, 0.5, 0.5, 1.0, 0.0, 0.75};

	double	u_result;
	double	v_result;

	// ACT / ASSERT
	for (int i = 0; i < 7; i++)
	{
		spherical_map(p[i], &u_result, &v_result);
		print_result(num_test, &u[i], &u_result, float_compare_test, print_ko_float);
		print_result(num_test, &v[i], &v_result, float_compare_test, print_ko_float);
	}
}

// TEST 03
void	test_using_a_texture_map_pattern_with_a_spherical_map(int num_test)
{
	// ARRANGE
	t_color	black = color(0, 0, 0);
	t_color	white = color(1, 1, 1);
	t_shape	s = sphere();

	t_checkers	checkers = uv_checkers(16, 8, black, white);
	t_map		pattern_map = texture_map(checkers, spherical_map);
	t_pattern	pattern = checkers_pattern(black, white);
	pattern.map = pattern_map;
	s.material.pattern = pattern;

	t_color	expected[] = {
		white, black, white, black, black, black, black, white, black, black
	};
	t_point	points[] = {
		point(0.4315, 0.4670, 0.7719),
		point(-0.9654, 0.2552, -0.0534),
		point(0.1039, 0.7090, 0.6975),
		point(-0.4986, -0.7856, -0.3663),
		point(-0.0317, -0.9395, 0.3411),
		point(0.4809, -0.7721, 0.4154),
		point(0.0285, -0.9612, -0.2745),
		point(-0.5734, -0.2162, -0.7903),
		point(0.7688, -0.1470, 0.6223),
		point(-0.7652, 0.2175, 0.6060)
	};
	t_color	result;

	// ACT / ASSERT
	for (int i = 0; i < 10; i++)
	{
		result = pattern_at_shape(pattern, s, points[i]);
		print_result(num_test, &expected[i], &result, color_compare_test, print_ko_color);
	}
}

// TEST 04

void	test_using_a_cylindrical_mapping_on_a_3D_point(int num_test)
{
	t_point	p[] = {
		point(0, 0, -1),
		point(0, 0.5, -1),
		point(0, 1, -1),
		point(0.70711, 0.5, -0.70711),
		point(1, 0.5, 0),
		point(0.70711, 0.5, 0.70711),
		point(0, -0.25, 1),
		point(-0.70711, 0.5, 0.70711),
		point(-1, 1.25, 0),
		point(-0.70711, 0.5, -0.70711)
	};

	double	u[] = {0.0, 0.0, 0.0, 0.125, 0.25, 0.375, 0.5, 0.625, 0.75, 0.875};
	double	v[] = {0.0, 0.5, 0.0, 0.5, 0.5, 0.5, 0.75, 0.5, 0.25, 0.5};

	double	u_result;
	double	v_result;

	// ACT / ASSERT
	for (int i = 0; i < 10; i++)
	{
		cylindrical_map(p[i], &u_result, &v_result);
		print_result(num_test, &u[i], &u_result, float_compare_test, print_ko_float);
		print_result(num_test, &v[i], &v_result, float_compare_test, print_ko_float);
	}
}

void	test_bump_map_in_a_sphere(int num_test)
{
	// ARRANGE
	(void) num_test;

	mlx_texture_t	*image = mlx_load_png("textures/texture.png");
	unsigned char	*pixel = get_pixel(image, 0, 0);

	printf("%x %x %x %x\n", pixel[0], pixel[1], pixel[2], pixel[3]);

	mlx_delete_texture(image);

}

int main(void)
{
	void	(*test_funcs[])(int) =
	{
		test_checker_patter_in_2D,
		test_using_a_spherical_mapping_on_a_3D_point,
		test_using_a_texture_map_pattern_with_a_spherical_map,
		// test_bump_map_in_a_sphere
	};

	printf("\n%sTESTING TEXTURE MAP:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++)
		test_funcs[i](i + 1);
	return (0);
}
