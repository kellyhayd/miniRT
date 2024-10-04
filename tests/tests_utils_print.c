/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils_print.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/20 21:41:13 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/29 07:45:20 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tests.h"

void	print_ok(int num_test)
{
	// printf(PURPLE "%2d" RESET " - " GREEN "[ ✓ ]" RESET "\n", num_test);
	printf("%s%2d%s - %s[ ✓ ]%s\n", PURPLE, num_test, RESET, GREEN, RESET);
}

void	print_result(int num_test, void *expected, void *result,
						int (*compare)(void *, void *),
						void (*print_ko)(int, void *, void *))
{
	static int	num_test_global = 0;

	num_test_global++;
	printf(BLUE "%2d" RESET " -> ", num_test_global);

	if (compare(expected, result))
		print_ok(num_test);
	else
		print_ko(num_test, expected, result);
}

void	print_ko_float(int num_test, void *expected, void *result)
{
	double	*expected_double = expected;
	double	*result_double = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: (%.2lf) "
		"Result: (%.2lf)\n",
		num_test,
		*expected_double,
		*result_double
	);
}

void	print_ko_int(int num_test, void *expected, void *result)
{
	int	*expected_int = expected;
	int	*result_int = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: (%d) "
		"Result: (%d)\n",
		num_test,
		*expected_int,
		*result_int
	);
}

void	print_ko_tuple(int num_test, void *expected, void *result)
{
	t_tuple	*expected_tuple = expected;
	t_tuple	*result_tuple = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: (%.2lf, %.2lf, %.2lf, %.2lf) "
		"Result: (%.2lf, %.2lf, %.2lf, %.2lf)\n",
		num_test,
		expected_tuple->x, expected_tuple->y, expected_tuple->z, expected_tuple->w,
		result_tuple->x, result_tuple->y, result_tuple->z, result_tuple->w
	);
}

void	print_ko_color(int num_test, void *expected, void *result)
{
	t_color	*expected_color = expected;
	t_color	*result_color = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: (%.2lf, %.2lf, %.2lf) "
		"Result: (%.2lf, %.2lf, %.2lf)\n",
		num_test,
		expected_color->r, expected_color->g, expected_color->b,
		result_color->r, result_color->g, result_color->b
	);
}

void	print_ko_matrix(int num_test, void *expected, void *result)
{
	t_matrix	*matrix_expected = expected;
	t_matrix	*matrix_result = result;

	int	size_matrix = matrix_expected->rows * matrix_result->cols;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET"\nExpected: ( ", num_test);
	for (int i = 0; i < size_matrix; i++)
		printf("%.2lf%s", matrix_expected->tab[i], i + 1 < size_matrix ? " " : "");
	printf(" )\n");

	printf("Result:   ( ");
	for (int i = 0; i < size_matrix; i++)
		printf("%.2lf%s", matrix_result->tab[i], i + 1 < size_matrix ? " " : "");
	printf(" )\n");
}

void	print_ko_ray(int num_test, void *expected, void *result)
{
	t_ray	*ray_expected = expected;
	t_ray	*ray_result = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: origin (%.2lf, %.2lf, %.2lf, %.2lf) direction (%.2lf, %.2lf, %.2lf, %.2lf)\n"
		"\t\tResult: origin (%.2lf, %.2lf, %.2lf, %.2lf) direction (%.2lf, %.2lf, %.2lf, %.2lf)\n",
		num_test,
		ray_expected->origin.x, ray_expected->origin.y, ray_expected->origin.z, ray_expected->origin.w,
		ray_expected->direction.x, ray_expected->direction.y, ray_expected->direction.z, ray_expected->direction.w,
		ray_result->origin.x, ray_result->origin.y, ray_result->origin.z, ray_result->origin.w,
		ray_result->direction.x, ray_result->direction.y, ray_result->direction.z, ray_result->direction.w
	);
}

void	print_ko_shape(int num_test, void *expected, void *result)
{
	t_shape	*shape_expected = expected;
	t_shape	*shape_result = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: sphere (origin (%.2lf, %.2lf, %.2lf) radius (%.2lf))\n"
		"\t\tResult: sphere (origin (%.2lf, %.2lf, %.2lf) radius (%.2lf))\n",
		num_test,
		shape_expected->sphere_shape.origin.x, shape_expected->sphere_shape.origin.y, shape_expected->sphere_shape.origin.z, shape_expected->sphere_shape.radius,
		shape_result->sphere_shape.origin.x, shape_result->sphere_shape.origin.y, shape_result->sphere_shape.origin.z, shape_result->sphere_shape.radius
	);
}

void	print_ko_hit(int num_test, void *expected, void *result)
{
	t_hit	*hit_expected = expected;
	t_hit	*hit_result = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET, num_test);
	if (hit_expected)
		printf("Expected: t (%.2lf) object (sphere (origin (%.2lf, %.2lf, %.2lf) radius (%.2lf)))\n",
			hit_expected->t,
			hit_expected->object.sphere_shape.origin.x, hit_expected->object.sphere_shape.origin.y, hit_expected->object.sphere_shape.origin.z, hit_expected->object.sphere_shape.radius
		);
	else
		printf("Expected: (NULL)\n");

	if (hit_result)
		printf("           Result:   t (%.2lf) object (sphere (origin (%.2lf, %.2lf, %.2lf) radius (%.2lf)))\n",
				hit_result->t,
				hit_result->object.sphere_shape.origin.x, hit_result->object.sphere_shape.origin.y, hit_result->object.sphere_shape.origin.z, hit_result->object.sphere_shape.radius
		);
	else
		printf("           Result:   (NULL)\n");
}

void	print_ko_hit_list(int num_test, void *expected, void *result)
{
	t_hit	*hit_expected = expected;
	t_hit	*hit_result = result;
	t_hit	*aux;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: count (%d) hits (",
		num_test, intersection_count(expected)
	);

	aux = hit_expected;
	while (aux)
	{
		printf("%.2lf%s", aux->t, aux->next ? " " : "");
		aux = aux->next;
	}
	printf(") ");


	printf("Result: count (%d) hits (",
		intersection_count(hit_result)
	);

	aux = hit_result;
	while (aux)
	{
		printf("%.2lf%s", aux->t, aux->next ? " " : "");
		aux = aux->next;
	}
	printf(")\n");
}

void	print_ko_light(int num_test, void *expected, void *result)
{
	t_light	*light_expected = expected;
	t_light	*light_result = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: position (%.2lf, %.2lf, %.2lf) intensity (%.2lf, %.2lf, %.2lf)\n"
		"\t\tResult: position (%.2lf, %.2lf, %.2lf) intensity (%.2lf, %.2lf, %.2lf)\n",
		num_test,
		light_expected->position.x, light_expected->position.y, light_expected->position.z,
		light_expected->intensity.r, light_expected->intensity.g, light_expected->intensity.b,
		light_result->position.x, light_result->position.y, light_result->position.z,
		light_result->intensity.r, light_result->intensity.g, light_result->intensity.b
	);
}

void	print_ko_material(int num_test, void *expected, void *result)
{
	t_material	*material_expected = expected;
	t_material	*material_result = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: ambient (%.2lf) diffuse (%.2lf) specular (%.2lf) shininess (%.2lf) color (%.2lf, %.2lf, %.2lf)\n"
		"\t\tResult: ambient (%.2lf) diffuse (%.2lf) specular (%.2lf) shininess (%.2lf) color (%.2lf, %.2lf, %.2lf)\n",
		num_test,
		material_expected->ambient, material_expected->diffuse, material_expected->specular, material_expected->shininess, material_expected->color.r, material_expected->color.g, material_expected->color.b,
		material_result->ambient, material_result->diffuse, material_result->specular, material_result->shininess, material_result->color.r, material_result->color.g, material_result->color.b
	);
}

void	print_ko_world(int num_test, void *expected, void *result)
{
	t_world	*w_expected = expected;
	t_world	*w_result = result;

	// Ainda preciso revisar essa função
	(void) w_expected;
	(void) w_result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ]" RESET " Your world is out of this galaxy!\n", num_test);

// 	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
// 		"Expected: light (point (%.2lf, %.2lf, %.2lf) color (%.2lf, %.2lf, %.2lf))\n"
// 		"          sphere (origin (%.2lf, %.2lf, %.2lf) radius (%.2lf))\n"
// 		"\t\tResult: light (point (%.2lf, %.2lf, %.2lf) color (%.2lf, %.2lf, %.2lf))\n"
// 		"\t\t        sphere (origin (%.2lf, %.2lf, %.2lf) radius (%.2lf))\n",
// 		num_test,
//
// 		w_expected->light.position.x, w_expected->light.position.y, w_expected->light.position.z,
// 		w_expected->light.intensity.r, w_expected->light.intensity.g, w_expected->light.intensity.b,
// 		w_expected->shape->sphere_shape.origin.x, w_expected->shape->sphere_shape.origin.y, w_expected->shape->sphere_shape.origin.z,
// 		w_expected->shape->sphere_shape.radius,
//
// 		w_result->light.position.x, w_result->light.position.y, w_result->light.position.z,
// 		w_result->light.intensity.r, w_result->light.intensity.g, w_result->light.intensity.b,
// 		w_result->shape->sphere_shape.origin.x, w_result->shape->sphere_shape.origin.y, w_result->shape->sphere_shape.origin.z,
// 		w_result->shape->sphere_shape.radius
// 	);
}

void	print_ko_camera(int num_test, void *expected, void *result)
{
	t_camera	*camera_expected = expected;
	t_camera	*camera_result = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: hsize (%.2f) vsize (%.2f) field_of_view (%.2lf)\n"
		"\t\tResult: hsize (%.2f) vsize (%.2f) field_of_view (%.2lf)\n"
		"If until here everything is right, maybe the matrix has a problem\n",
		num_test,
		camera_expected->hsize, camera_expected->vsize, camera_expected->field_of_view,
		camera_result->hsize, camera_result->vsize, camera_result->field_of_view
	);
}

void	print_ko_comps(int num_test, void *expected, void *result)
{
	t_comps	*comps_expected = expected;
	t_comps	*comps_result = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: t (%.2lf) object (sphere (origin (%.2lf, %.2lf, %.2lf) radius (%.2lf)))\n"
		"\t\tResult: t (%.2lf) object (sphere (origin (%.2lf, %.2lf, %.2lf) radius (%.2lf)))\n",
		num_test,
		comps_expected->t,
		comps_expected->object.sphere_shape.origin.x, comps_expected->object.sphere_shape.origin.y, comps_expected->object.sphere_shape.origin.z, comps_expected->object.sphere_shape.radius,
		comps_result->t,
		comps_result->object.sphere_shape.origin.x, comps_result->object.sphere_shape.origin.y, comps_result->object.sphere_shape.origin.z, comps_result->object.sphere_shape.radius
	);
}

void	print_ko_pattern(int num_test, void *expected, void *result)
{
	t_pattern	*pattern_expected = expected;
	t_pattern	*pattern_result = result;

	printf(PURPLE "%2d" RESET " - " RED "[ ✗ ] " RESET
		"Expected: has_pattern (%d) color_a (%.2lf, %.2lf, %.2lf) color_b (%.2lf, %.2lf, %.2lf)\n"
		"\t\tResult: has_pattern (%d) color_a (%.2lf, %.2lf, %.2lf) color_b (%.2lf, %.2lf, %.2lf)\n",
		num_test,
		pattern_expected->has_pattern,
		pattern_expected->color_a.r, pattern_expected->color_a.g, pattern_expected->color_a.b,
		pattern_expected->color_b.r, pattern_expected->color_b.g, pattern_expected->color_b.b,
		pattern_result->has_pattern,
		pattern_result->color_a.r, pattern_result->color_a.g, pattern_result->color_a.b,
		pattern_result->color_b.r, pattern_result->color_b.g, pattern_result->color_b.b
	);
}
