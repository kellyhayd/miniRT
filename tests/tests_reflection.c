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


int	main(void)
{
	void	(*tests[])(int) =
	{
		test_reflectivity_for_the_default_material,				// 01
	};

	printf("\n%sTESTING REFLECTIONS:%s\n", YELLOW, RESET);
	for (unsigned int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
		tests[i](i + 1);
	return (0);
}
