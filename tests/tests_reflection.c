#include "tests.h"

// TEST 01
void	test_reflectivity_for_the_default_material(int num_test)
{
	// ARRANGE
	t_material	expected;
	t_material	result;

	expected = material();
	expected.reflective = 0.0;

	// ACT
	result = material();

	// ASSERT
	print_result(num_test, &expected, &result, material_compare_test, print_ko_material);
}

// TEST 02
void	test_precomputing_the_reflection_vector(int num)
{
	// ARRANGE
	t_ray	r;
	t_hit	i;
	t_shape	shape;
	t_comps	expected;
	t_comps	result;

	shape = plane();
	r = ray(point(0, 1, -1), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), shape);
	expected = prepare_computations(i, r);
	expected.reflectv = vector(0, sqrt(2) / 2, sqrt(2) / 2);

	// ACT
	result = prepare_computations(i, r);

	// ASSERT
	print_result(num, &expected, &result, comps_compare_test, print_ko_comps);
}


int	main(void)
{
	void	(*tests[])(int) =
	{
		test_reflectivity_for_the_default_material,				// 01
		test_precomputing_the_reflection_vector,				// 02
	};

	printf("\n%sTESTING REFLECTIONS:%s\n", YELLOW, RESET);
	for (unsigned int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
		tests[i](i + 1);
	return (0);
}
