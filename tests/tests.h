/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:44:58 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/12 14:23:02 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_H
# define TESTS_H

#include "minirt.h"

enum e_test_type
{
	TUPLE = 1,
	FLOAT = 2,
	COLOR = 3,
	MATRIX = 4,
};


// Compares

int	float_compare_test(void *expected, void *result);
int	int_compare_test(void *expected, void *result);

int	tuple_compare_test(void *expected, void *result);
int	color_compare_test(void *expected, void *result);
int	matrix_compare_test(void *expected, void *result);
int	ray_compare_test(void *expected, void *result);
int	hit_list_compare_test(void *expected, void *result);
int	shape_compare_test(void *expected, void *result);
int	hit_compare_test(void *expected, void *result);
int	hit_list_compare_test(void *expected, void *result);
int	light_compare_test(void *expected, void *result);
int	material_compare_test(void *expected, void *result);
int	world_compare_test(void *expected, void *result);
int	shape_list_compare_test(void *expected, void *result);
int	light_list_compare_test(void *expected, void *result);
int	world_compare_test(void *expected, void *result);
int	camera_compare_test(void *expected, void *result);
int	comps_compare_test(void *expected, void *result);
int	pattern_compare_test(void *expected, void *result);


// Prints

void	print_ok(int num_test);
void	print_result(int num_test, void *expected, void *result,
						int (*compare)(void *, void *),
						void (*print_ko)(int, void *, void *));

void	print_ko_float(int num_test, void *expected, void *result);
void	print_ko_int(int num_test, void *expected, void *result);

void	print_ko_tuple(int num_test, void *expected, void *result);
void	print_ko_color(int num_test, void *expected, void *result);
void	print_ko_matrix(int num_test, void *expected, void *result);
void	print_ko_ray(int num_test, void *expected, void *result);
void	print_ko_hit_list(int num_test, void *expected, void *result);
void	print_ko_shape(int num_test, void *expected, void *result);
void	print_ko_hit(int num_test, void *expected, void *result);
void	print_ko_light(int num_test, void *expected, void *result);
void	print_ko_material(int num_test, void *expected, void *result);
void	print_ko_world(int num_test, void *expected, void *result);
void	print_ko_camera(int num_test, void *expected, void *result);
void	print_ko_comps(int num_test, void *expected, void *result);
void	print_ko_pattern(int num_test, void *expected, void *result);

#endif
