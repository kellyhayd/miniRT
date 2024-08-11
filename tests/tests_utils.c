/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:18:05 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/11 17:28:22 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include <stdarg.h>

#define TUPLE 1
#define FLOAT 2
#define COLOR 3

int	color_compare(t_color color1, t_color color2)
{
	return (float_compare(color1.r, color2.r)
		&& float_compare(color1.g, color2.g)
		&& float_compare(color1.b, color2.b));
}

void	print_ok(int num_test)
{
	printf(PURPLE "%d" RESET " - " GREEN "[ ✓ ]\n" RESET, num_test);
}

void	print_ko_tuple(int num_test, t_tuple expected, t_tuple result)
{
	printf(PURPLE "%d" RESET " - " RED "[ ✗ ]" RESET
		" Expected: (%.2lf, %.2lf, %.2lf, %.2lf) \
		RESULT: (%.2lf, %.2lf, %.2lf, %.2lf)\n", \
		num_test, expected.x, expected.y, expected.z, expected.w, result.x, result.y, result.z, result.w
	);
}

void	print_ko_color(int num_test, t_color expected, t_color result)
{
	printf(PURPLE "%d" RESET " - " RED "[ ✗ ]" RESET
		" Expected: (%.2lf, %.2lf, %.2lf, %.2lf) \
		RESULT: (%.2lf, %.2lf, %.2lf, %.2lf)\n", \
		num_test, expected.r, expected.g, expected.b, result.r, result.g, result.b
	);
}

void	print_result(int num_test, int type, ...)
{
	va_list	args;
	double	d_result;
	double	d_expected;
	t_tuple	t_result;
	t_tuple	t_expected;
	t_color	c_result;
	t_color	c_expected;

	va_start(args, type);
	if (type == TUPLE)
	{
		t_expected = va_arg(args, t_tuple);
		t_result = va_arg(args, t_tuple);
		if (tuple_compare(t_expected, t_result) == 1)
			print_ok(num_test);
		else
			print_ko_tuple(num_test, t_expected, t_result);
	}
	else if (type == FLOAT)
	{
		d_expected = va_arg(args, double);
		d_result = va_arg(args, double);
		if (float_compare(d_expected, d_result) == 1)
			print_ok(num_test);
		else
		{
			printf(PURPLE "%d" RESET " - " RED "[ ✗ ]" RESET
			" Expected: (%.2lf) RESULT: (%.2lf)\n", num_test, d_expected, d_result);
		}
	}
	else if (type == COLOR)
	{
		c_expected = va_arg(args, t_color);
		c_result = va_arg(args, t_color);
		if (color_compare(c_expected, c_result) == 1)
			print_ok(num_test);
		else
			print_ko_color(num_test, c_expected, c_result);
	}
	va_end(args);
}
