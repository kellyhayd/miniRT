#include "tests.h"

// TEST 01
void	test_creating_a_world(int num_test)
{
	// ARRANGE
	t_world	w;
	t_world	expected;

	expected.light = point_light(point(0, 0, 0), color(1, 1, 1));
	expected.shape = NULL;
	expected.shape_nb = 0;

	// ACT
	w = world();

	// ASSERT
	print_result(num_test, &expected, &w, world_compare_test, print_ko_world);
}

// TEST 02
void	test_default_world(int num_test)
{
	// ARRANGE
	t_world	w;
	t_world	expected;
	expected = world();
	expected.shape_nb = 2;
	expected.shape = malloc(sizeof(t_shape) * 2);
	expected.shape[0] = sphere();
	expected.shape[0].material.color = color(0.8, 1.0, 0.6);
	expected.shape[0].material.diffuse = 0.7;
	expected.shape[0].material.specular = 0.2;
	expected.shape[1] = sphere();
	set_transformation(&expected.shape[1], scaling(0.5, 0.5, 0.5));
	expected.light = point_light(point(-10, 10, -10), color(1, 1, 1));

	// ACT
	w = default_world();

	// ASSERT
	print_result(num_test, &expected, &w, world_compare_test, print_ko_world);
}

// TEST 03
// void	test_intersect_a_world_with_a_ray(int num_test)
// {
// 	// ARRANGE
// 	t_world	w = default_world();
// 	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));
// 	t_hit	*result = malloc(sizeof(t_hit) * 4);
// 	t_hit	*expected;
// 	t_hit	*hit;

// 	expected = malloc(sizeof(t_hit) * 4);
// 	expected[0] = intersection(4, w.shape[0]);
// 	expected[1] = intersection(4.5, w.shape[0]);
// 	expected[2] = intersection(5.5, w.shape[0]);
// 	expected[3] = intersection(6, w.shape[0]);

// 	int			xs_count_expected = 4;
// 	int			xs_count_result = intersection_count(result);

// 	// ACT
// 	result = intersect_world(w, r);

// 	// ASSERT
// 	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
// 	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);
// }

int main(void)
{
	void	(*test_funcs[])(int) =
	{
		test_creating_a_world,							// 01
		test_default_world,								// 02
		// test_intersect_a_world_with_a_ray,			// 03
	};

	printf("\n%sTESTING WORLD CREATION:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++)
		test_funcs[i](i + 1);
	return (0);
}
