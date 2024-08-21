/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 23:44:58 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/20 21:52:02 by danbarbo         ###   ########.fr       */
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


// Prints

void	print_result(int num_test, void *expected, void *result,
						int (*compare)(void *, void *),
						void (*print_ko)(int, void *, void *));

void	print_ko_float(int num_test, void *expected, void *result);
void	print_ko_int(int num_test, void *expected, void *result);

void	print_ko_tuple(int num_test, void *expected, void *result);
void	print_ko_color(int num_test, void *expected, void *result);
void	print_ko_matrix(int num_test, void *expected, void *result);

#endif
