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
	t_hit	*hit_list = NULL;

	shape = plane();
	r = ray(point(0, 1, -1), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), shape);

	// add_intersection(&hit_list, intersection(1, shape));
	expected = prepare_computations(i, r, hit_list);
	expected.reflectv = vector(0, sqrt(2) / 2, sqrt(2) / 2);

	// ACT
	result = prepare_computations(i, r, hit_list);

	// ASSERT
	print_result(num, &expected, &result, comps_compare_test, print_ko_comps);

	// CLEAR
	hit_clear_list(&hit_list);
}

// TEST 03
void	test_the_reflected_color_for_a_nonreflective_material(int num_test)
{
	// ARRANGE
	t_world	w;
	t_ray	r;
	t_shape	shape;
	t_hit	i;
	t_comps	comps;
	t_color	expected;
	t_color	result;
	t_hit	*hit_list;

	w = default_world();
	r = ray(point(0, 0, 0), vector(0, 0, 1));
	shape = *w.shape->next;
	shape.material.ambient = 1;
	i = intersection(1, shape);

	hit_list = intersect_world(w, r);
	comps = prepare_computations(i, r, hit_list);
	expected = color(0, 0, 0);

	// ACT
	result = reflected_color(w, comps, 4);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	hit_clear_list(&hit_list);
	world_clear(&w);
}

// TEST 04
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
	t_hit	*hit_list;

	w = default_world();
	shape = plane();
	shape.material.reflective = 0.5;
	set_transformation(&shape, translation(0, -1, 0));
	add_shape(&w.shape, shape);
	r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), shape);

	hit_list = intersect_world(w, r);
	comps = prepare_computations(i, r, hit_list);

	// TODO: there's a difference in the 5th decimal place
	expected = color(0.19032, 0.2379, 0.14274);

	// ACT
	result = reflected_color(w, comps, 4);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	hit_clear_list(&hit_list);
	world_clear(&w);
}

// TEST 05
void	test_shade_hit_with_a_reflective_material(int num_test)
{
	// ARRANGE
	t_world	w;
	t_ray	r;
	t_shape	shape;
	t_hit	i;
	t_comps	comps;
	t_color	expected;
	t_color	result;
	t_hit	*hit_list;

	w = default_world();
	shape = plane();
	shape.material.reflective = 0.5;
	set_transformation(&shape, translation(0, -1, 0));
	add_shape(&w.shape, shape);
	r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), shape);

	hit_list = intersect_world(w, r);
	comps = prepare_computations(i, r, hit_list);

	// TODO: there's a difference in the 5th decimal place
	expected = color(0.87677, 0.92436, 0.82918);

	// ACT
	result = shade_hit(w, comps, 4);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	hit_clear_list(&hit_list);
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
	t_hit	*hit_list;

	w = default_world();
	shape = plane();
	shape.material.reflective = 0.5;
	set_transformation(&shape, translation(0, -1, 0));
	add_shape(&w.shape, shape);
	r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));
	i = intersection(sqrt(2), shape);

	hit_list = intersect_world(w, r);
	comps = prepare_computations(i, r, hit_list);

	expected = color(0, 0, 0);

	// ACT
	result = reflected_color(w, comps, 0);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	hit_clear_list(&hit_list);
	world_clear(&w);
}

// TEST 08
void	test_transparency_and_refractive_index_for_the_default_material(int num_test)
{
	// ARRANGE
	t_material	expected;
	t_material	result;

	expected = material();
	expected.transparency = 0.0;
	expected.refractive_index = 1.0;

	// ACT
	result = material();

	// ASSERT
	print_result(num_test, &expected, &result, material_compare_test, print_ko_material);
}

// TEST 09
void	test_a_helper_for_producing_a_sphere_with_a_glassy_material(int num_test)
{
	// ARRANGE
	t_shape		g_sphere = glass_sphere();
	t_matrix	matrix_expected = identity();
	t_matrix	matrix_result;
	double		transparency_result;
	double		transparency_expected = 1.0;
	double		refractive_index_result;
	double		refractive_index_expected = 1.5;

	// ACT
	matrix_result = g_sphere.transform;
	transparency_result = g_sphere.material.transparency;
	refractive_index_result = g_sphere.material.refractive_index;

	// ASSERT
	print_result(num_test, &matrix_expected, &matrix_result, matrix_compare_test, print_ko_matrix);
	print_result(num_test, &transparency_expected, &transparency_result, float_compare_test, print_ko_float);
	print_result(num_test, &refractive_index_expected, &refractive_index_result, float_compare_test, print_ko_float);
}

// TEST 10
void	test_finding_n1_and_n2_at_various_intersections(int num_test)
{
	t_shape	A = glass_sphere();
	set_transformation(&A, scaling(2, 2, 2));
	A.material.refractive_index = 1.5;

	t_shape	B = glass_sphere();
	set_transformation(&B, translation(0, 0, -0.25));
	B.material.refractive_index = 2.0;

	t_shape	C = glass_sphere();
	set_transformation(&C, translation(0, 0, 0.25));
	C.material.refractive_index = 2.5;

	t_ray	r = ray(point(0, 0, -4), vector(0, 0, 1));

	t_hit	*xs = NULL;
	add_intersection(&xs, intersection(2, A));
	add_intersection(&xs, intersection(2.75, B));
	add_intersection(&xs, intersection(3.25, C));
	add_intersection(&xs, intersection(4.75, B));
	add_intersection(&xs, intersection(5.25, C));
	add_intersection(&xs, intersection(6, A));

	double	n1_expected[] = {1.0, 1.5, 2.0, 2.5, 2.5, 1.5};
	double	n2_expected[] = {1.5, 2.0, 2.5, 2.5, 1.5, 1.0};

	t_comps	comps;
	t_hit	*hit;

	// ACT / ASSERT
	for (int i = 0; i < 6; i++)
	{
		hit = hit_index(xs, i);
		comps = prepare_computations(*hit, r, xs);
		print_result(num_test, &n1_expected[i], &comps.n1, float_compare_test, print_ko_float);
		print_result(num_test, &n2_expected[i], &comps.n2, float_compare_test, print_ko_float);
		printf("\n");
	}

	// CLEAR
	hit_clear_list(&xs);
}

// TEST 11
void	test_under_point_is_offset_below_the_surface(int num_test)
{
	// ARRANGE
	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));

	t_shape	shape = glass_sphere();
	set_transformation(&shape, translation(0, 0, 1));

	t_hit	i = intersection(5, shape);
	t_hit	*hit_list = NULL;
	add_intersection(&hit_list, i);

	t_comps	comps = prepare_computations(i, r, hit_list);
	int		expected = 1;
	int		result;

	// ACT
	result = comps.under_point.z > EPSILON / 2;

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);

	// CLEAR
	hit_clear_list(&hit_list);
}

// TEST 12
void	test_the_refracted_color_with_an_opaque_surface(int num_test)
{
	// ARRANGE
	t_world	w = default_world();
	t_shape	shape = *w.shape->next;
	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));

	t_hit	*hit_list = NULL;
	add_intersection(&hit_list, intersection(4, shape));
	add_intersection(&hit_list, intersection(6, shape));

	t_comps	comps = prepare_computations(*hit_list, r, hit_list);
	t_color	expected = color(0, 0, 0);
	t_color	result;

	// ACT
	result = refracted_color(w, comps, 5);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	hit_clear_list(&hit_list);
	world_clear(&w);
}

// TEST 13
void	test_the_refracted_color_at_the_maximum_recursive_depth(int num_test)
{
	// ARRANGE
	t_world	w = default_world();

	t_shape	*shape = w.shape->next;
	shape->material.transparency = 1.0;
	shape->material.refractive_index = 1.5;

	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));

	t_hit	*hit_list = NULL;
	add_intersection(&hit_list, intersection(4, *shape));
	add_intersection(&hit_list, intersection(6, *shape));

	t_comps	comps = prepare_computations(*hit_list, r, hit_list);
	t_color	expected = color(0, 0, 0);
	t_color	result;

	// ACT
	result = refracted_color(w, comps, 0);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	hit_clear_list(&hit_list);
	world_clear(&w);
}

// TEST 14
void	test_the_refracted_color_under_total_internal_reflection(int num_test)
{
	// ARRANGE
	t_world	w = default_world();

	t_shape	*shape = w.shape->next;
	shape->material.transparency = 1.0;
	shape->material.refractive_index = 1.5;

	t_ray	r = ray(point(0, 0, sqrt(2) / 2), vector(0, 1, 0));

	t_hit	*hit_list = NULL;
	add_intersection(&hit_list, intersection(-sqrt(2) / 2, *shape));
	add_intersection(&hit_list, intersection(sqrt(2) / 2, *shape));

	t_comps	comps = prepare_computations(*hit_list->next, r, hit_list);
	t_color	expected = color(0, 0, 0);
	t_color	result;

	// ACT
	result = refracted_color(w, comps, 5);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	hit_clear_list(&hit_list);
	world_clear(&w);
}

// TEST 15
void	test_shade_hit_with_a_transparent_material(int num_test)
{
	// ARRANGE
	t_world	w = default_world();

	t_shape	floor = plane();
	set_transformation(&floor, translation(0, -1, 0));
	floor.material.transparency = 0.5;
	floor.material.refractive_index = 1.5;
	add_shape(&w.shape, floor);

	t_shape	ball = sphere();
	set_transformation(&ball, translation(0, -3.5, -0.5));
	ball.material.color = color(1, 0, 0);
	ball.material.ambient = 0.5;
	add_shape(&w.shape, ball);

	t_ray	r = ray(point(0, 0, -3), vector(0, -sqrt(2) / 2, sqrt(2) / 2));

	t_hit	*hit_list = NULL;
	add_intersection(&hit_list, intersection(sqrt(2), floor));

	t_comps	comps = prepare_computations(*hit_list, r, hit_list);
	t_color	expected = color(0.93642, 0.68642, 0.68642);
	t_color	result;

	// ACT
	result = shade_hit(w, comps, 5);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	hit_clear_list(&hit_list);
	world_clear(&w);
}

int	main(void)
{
	void	(*tests[])(int) =
	{
		test_reflectivity_for_the_default_material,							// 01
		test_precomputing_the_reflection_vector,							// 02
		test_the_reflected_color_for_a_nonreflective_material,				// 03
		test_the_reflected_color_for_a_reflective_material,					// 04
		test_shade_hit_with_a_reflective_material,							// 05
		test_color_at_with_mutually_reflective_surfaces,					// 06
		test_the_reflected_color_at_the_maximum_recursive_depth,			// 07
		test_transparency_and_refractive_index_for_the_default_material,	// 08
		test_a_helper_for_producing_a_sphere_with_a_glassy_material,		// 09
		test_finding_n1_and_n2_at_various_intersections,					// 10
		test_under_point_is_offset_below_the_surface,						// 11
		test_the_refracted_color_with_an_opaque_surface,					// 12
		test_the_refracted_color_at_the_maximum_recursive_depth,			// 13
		test_the_refracted_color_under_total_internal_reflection,			// 14
		test_shade_hit_with_a_transparent_material,							// 15
	};

	printf("\n%sTESTING REFLECTIONS:%s\n", YELLOW, RESET);
	for (unsigned int i = 0; i < sizeof(tests) / sizeof(tests[0]); i++)
		tests[i](i + 1);
	return (0);
}
