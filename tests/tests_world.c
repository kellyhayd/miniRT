#include "tests.h"

// TEST 01
void	test_creating_a_world(int num_test)
{
	// ARRANGE
	t_world	expected = {0};
	t_world	result;

	// ACT
	result = world();

	// ASSERT
	print_result(num_test, &expected, &result, world_compare_test, print_ko_world);
}

// TEST 02
void	test_default_world(int num_test)
{
	// ARRANGE
	t_world	expected;
	t_world	result;
	t_shape	sphere1 = sphere();
	t_shape	sphere2 = sphere();

	expected = world();

	// Create list of shapes
	add_light(&expected.light, point_light(point(-10, 10, -10), color(1, 1, 1)));

	// Create first sphere
	sphere1.material.color = color(0.8, 1.0, 0.6);
	sphere1.material.diffuse = 0.7;
	sphere1.material.specular = 0.2;

	// Create second sphere
	set_transformation(&sphere2, scaling(0.5, 0.5, 0.5));

	// Add shapes to world
	add_shape(&expected.shape, sphere1);
	add_shape(&expected.shape, sphere2);

	// ACT
	result = default_world();

	// ASSERT
	print_result(num_test, &expected, &result, world_compare_test, print_ko_world);

	// CLEAR
	world_clear(&expected);
	world_clear(&result);
}

// TEST 03
void	test_intersect_a_world_with_a_ray(int num_test)
{
	// ARRANGE
	int		xs_count_expected = 4;
	int		xs_count_result;
	t_world	w = default_world();
	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_hit	*expected = NULL;
	t_hit	*result;

	add_intersection(&expected, intersection(4, *w.shape));
	add_intersection(&expected, intersection(4.5, *w.shape->next));
	add_intersection(&expected, intersection(5.5, *w.shape->next));
	add_intersection(&expected, intersection(6, *w.shape));

	// ACT
	result = intersect_world(w, r);
	xs_count_result = intersection_count(result);

	// ASSERT
	print_result(num_test, &xs_count_expected, &xs_count_result, int_compare_test, print_ko_int);
	print_result(num_test, expected, result, hit_list_compare_test, print_ko_hit_list);

	// CLEAR
	world_clear(&w);
	hit_clear_list(&expected);
	hit_clear_list(&result);
}

// TEST 04
void	test_precomputing_state_of_an_intersection(int num_test)
{
	// ARRANGE
	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_shape	s = sphere();
	t_hit	i = intersection(4, s);
	t_comps	expected;
	t_comps	result;

	expected.t = i.t;
	expected.object = i.object;
	expected.point = point(0, 0, -1);
	expected.sight.eye = vector(0, 0, -1);
	expected.sight.normal = vector(0, 0, -1);

	// ACT
	result = prepare_computations(i, r);

	// ASSERT
	print_result(num_test, &expected, &result, comps_compare_test, print_ko_comps);
}

// TEST 05
void	test_the_hit_when_an_intersection_occurs_on_the_outside(int num_test)
{
	// ARRANGE
	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_shape	s = sphere();
	t_hit	i = intersection(4, s);
	t_comps	comps;
	int		expected;
	int		result;

	expected = false;

	// ACT
	comps = prepare_computations(i, r);
	result = comps.inside;

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);
}

// TEST 06
void	test_the_hit_when_an_intersection_occurs_on_the_inside(int num_test)
{
	// ARRANGE
	t_ray	r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_shape	s = sphere();
	t_hit	i = intersection(1, s);
	t_comps	comps;
	int		expected;
	int		result;

	expected = true;

	// ACT
	comps = prepare_computations(i, r);
	result = comps.inside;

	// ASSERT
	print_result(num_test, &expected, &result, int_compare_test, print_ko_int);
}

// TEST 07
void	test_shading_an_intersection(int num_test)
{
	// ARRANGE
	t_world	w = default_world();
	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_shape	s = *w.shape;
	t_hit	i = intersection(4, s);
	t_comps	comps = prepare_computations(i, r);
	t_color	expected;
	t_color	result;

	expected = color(0.38066, 0.47583, 0.2855);

	// ACT
	result = shade_hit(w, comps);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	world_clear(&w);
}

// TEST 08
void	test_shading_an_intersection_from_the_inside(int num_test)
{
	// ARRANGE
	t_world	w = default_world();
	t_ray	r = ray(point(0, 0, 0), vector(0, 0, 1));
	t_shape	s = *w.shape->next;
	t_hit	i = intersection(0.5, s);
	t_comps	comps = prepare_computations(i, r);
	t_color	expected;
	t_color	result;

	w.light->intensity = color(1, 1, 1);
	w.light->position = point(0, 0.25, 0);
	expected = color(0.90498, 0.90498, 0.90498);

	// ACT
	result = shade_hit(w, comps);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	world_clear(&w);
}

// TEST 09
void	test_color_at_with_ray_misses(int num_test)
{
	// ARRANGE
	t_world	w = default_world();
	t_ray	r = ray(point(0, 0, -5), vector(0, 1, 0));
	t_color	expected;
	t_color	result;

	expected = color(0, 0, 0);

	// ACT
	result = color_at(w, r);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	world_clear(&w);
}

// TEST 10
void	test_color_at_with_ray_hits(int num_test)
{
	// ARRANGE
	t_world	w = default_world();
	t_ray	r = ray(point(0, 0, -5), vector(0, 0, 1));
	t_color	expected;
	t_color	result;

	expected = color(0.38066, 0.47583, 0.2855);

	// ACT
	result = color_at(w, r);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	world_clear(&w);
}

// TEST 11
void	test_color_at_with_intersection_behind_ray(int num_test)
{
	// ARRANGE
	t_world	w = default_world();
	t_ray	r = ray(point(0, 0, 0.75), vector(0, 0, -1));
	t_color	expected;
	t_color	result;

	w.shape->material.ambient = 1;
	w.shape->next->material.ambient = 1;
	expected = w.shape->next->material.color;

	// ACT
	result = color_at(w, r);

	// ASSERT
	print_result(num_test, &expected, &result, color_compare_test, print_ko_color);

	// CLEAR
	world_clear(&w);
}

int main(void)
{
	void	(*test_funcs[])(int) =
	{
		test_creating_a_world,										// 01
		test_default_world,											// 02
		test_intersect_a_world_with_a_ray,							// 03
		test_precomputing_state_of_an_intersection,					// 04
		test_the_hit_when_an_intersection_occurs_on_the_outside,	// 05
		test_the_hit_when_an_intersection_occurs_on_the_inside,		// 06
		test_shading_an_intersection,								// 07
		test_shading_an_intersection_from_the_inside,				// 08
		test_color_at_with_ray_misses,								// 09
		test_color_at_with_ray_hits,								// 10
		test_color_at_with_intersection_behind_ray,					// 11
	};

	printf("\n%sTESTING WORLD CREATION:%s\n", YELLOW, RESET);

	for (unsigned int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++)
		test_funcs[i](i + 1);
	return (0);
}
