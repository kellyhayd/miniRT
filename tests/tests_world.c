#include "tests.h"

// TEST 01
void	test_creating_a_world(int num_test)
{
	// ARRANGE
	t_world	w;
	t_world	expected;

	expected = world();

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
	t_light	light = point_light(point(-10, 10, -10), color(1, 1, 1));
	t_shape	s1 = sphere();
	t_shape	s2 = sphere();
	s1.material.color = color(0.8, 1.0, 0.6);
	s1.material.diffuse = 0.7;
	s1.material.specular = 0.2;
	s2.transform = scaling(0.5, 0.5, 0.5);
	expected.light = light;
	expected.shape[0] = s1;
	expected.shape[1] = s2;

	// ACT
	w = default_world();

	// ASSERT
	print_result(num_test, &expected, &w, world_compare_test, print_ko_world);
}

int main(void)
{
	void	(*test_funcs[])(int) =
	{
		test_creating_a_world,							// 01
	};

	printf("\n%sTESTING WORLD CREATION:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++)
		test_funcs[i](i + 1);
	return (0);
}
