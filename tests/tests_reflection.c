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

// TEST 03
void	test_the_reflected_color_for_a_nonreflective_material(int num_test)
{
	// ARRANGE
	t_world	w;
	t_ray	r;
	t_shape	*shape;
	t_hit	i;
	t_comps	comps;
	t_color	expected;
	t_color	result;

	w = default_world();
	r = ray(point(0, 0, 0), vector(0, 0, 1));
	shape = w.shape->next;
	shape->material.ambient = 1;
	i = intersection(1, *shape);
	comps = prepare_computations(i, r);
	expected = color(0, 0, 0);

	// ACT
	result = reflected_color(w, comps, 4);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	world_clear(&w);
}

void	test_the_reflected_color_for_a_reflective_material(int num_test)
{
	// ARRANGE
	t_world	w;
	t_ray	r;
	t_shape	shape;
	t_hit	i;
	t_comps	comps;
	t_color	expected;
	t_color	result;

	w = default_world();
	shape = plane();
	shape.material.reflective = 0.5;
	set_transformation(&shape, translation(0, -1, 0));
	add_shape(&w.shape, shape);
	r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), shape);
	comps = prepare_computations(i, r);

	// TODO: there's a difference in the 5th decimal place
	expected = color(0.19032, 0.2379, 0.14274);

	// ACT
	result = reflected_color(w, comps, 4);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// free(shape);
	world_clear(&w);
}

// TEST 05
void	test_shade_hit_with_a_reflective_material(int num_test)
{
	// ARRANGE
	t_world	w;
	t_ray	r;
	t_shape	*shape;
	t_hit	i;
	t_comps	comps;
	t_color	expected;
	t_color	result;

	w = default_world();
	shape = malloc(sizeof(t_shape));
	*shape = plane();
	shape->material.reflective = 0.5;
	set_transformation(shape, translation(0, -1, 0));
	add_shape(&w.shape, *shape);
	r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), *shape);
	comps = prepare_computations(i, r);

	// TODO: there's a difference in the 5th decimal place
	expected = color(0.87677, 0.92436, 0.82918);

	// ACT
	result = shade_hit(w, comps, 4);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	free(shape);
	world_clear(&w);
}

// TEST 06
void	test_color_at_with_mutually_reflective_surfaces(int num_test)
{
	// ARRANGE
	t_world	w;
	t_shape	lower;
	t_shape	upper;
	t_ray	r;
	t_color	result;
	t_color	expected;

	w = world();
	add_light(&w.light, point_light(point(0, 0, 0), color(1, 1, 1)));
	lower = plane();
	lower.material.reflective = 1;
	set_transformation(&lower, translation(0, -1, 0));
	add_shape(&w.shape, lower);
	upper = plane();
	upper.material.reflective = 1;
	set_transformation(&upper, translation(0, 1, 0));
	add_shape(&w.shape, upper);
	r = ray(point(0, 0, 0), vector(0, 1, 0));

	expected = color(9.5, 9.5, 9.5);

	// ACT
	result = color_at(w, r, 4);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	world_clear(&w);
}

// TEST 07
void	test_the_reflected_color_at_the_maximum_recursive_depth(int num_test)
{
	// ARRANGE
	t_world	w;
	t_shape	shape;
	t_ray	r;
	t_hit	i;
	t_comps	comps;
	t_color	expected;
	t_color	result;

	w = default_world();
	shape = plane();
	shape.material.reflective = 0.5;
	set_transformation(&shape, translation(0, -1, 0));
	add_shape(&w.shape, shape);
	r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), shape);
	comps = prepare_computations(i, r);

	expected = color(0, 0, 0);

	// ACT
	result = reflected_color(w, comps, 0);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	world_clear(&w);
}

int	main(void)
{
	void	(*tests[])(int) =
	{
		test_reflectivity_for_the_default_material,					// 01
		test_precomputing_the_reflection_vector,					// 02
		test_the_reflected_color_for_a_nonreflective_material,		// 03
		test_the_reflected_color_for_a_reflective_material,			// 04
		test_shade_hit_with_a_reflective_material,					// 05
		test_color_at_with_mutually_reflective_surfaces,			// 06
		test_the_reflected_color_at_the_maximum_recursive_depth,	// 07
	};

	printf("\n%sTESTING REFLECTIONS:%s\n", YELLOW, RESET);
	for (unsigned int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
		tests[i](i + 1);
	return (0);
}
