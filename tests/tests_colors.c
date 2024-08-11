/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_colors.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 17:12:44 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/11 18:08:48 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

#define TUPLE 1
#define FLOAT 2
#define COLOR 3

void	print_result(int num_test, int type, ...);

void	test_color(int num_test)
{
	// ARRANGE
	t_color	expected = {-0.5, 0.4, 1.7};
	t_color	result;

	// ACT
	result = color(-0.5, 0.4, 1.7);

	// ASSERT
	print_result(num_test, COLOR, expected, result);
}

void	test_color_adding(int num_test)
{
	// ARRANGE
	t_color	color1 = color(0.9, 0.6, 0.75);
	t_color	color2 = color(0.7, 0.1, 0.25);
	t_color	expected = color(1.6, 0.7, 1.0);
	t_color	result;

	// ACT
	result = color_adding(color1, color2);

	// ASSERT
	print_result(num_test, COLOR, expected, result);
}

void	test_color_subtracting(int num_test)
{
	// ARRANGE
	t_color	color1 = color(0.9, 0.6, 0.75);
	t_color	color2 = color(0.7, 0.1, 0.25);
	t_color	expected = color(0.2, 0.5, 0.5);
	t_color	result;

	// ACT
	result = color_subtracting(color1, color2);

	// ASSERT
	print_result(num_test, COLOR, expected, result);
}

void	test_color_multiplying(int num_test)
{
	// ARRANGE
	t_color	color1 = color(0.2, 0.3, 0.4);
	t_color	expected = color(0.4, 0.6, 0.8);
	t_color	result;

	// ACT
	result = color_multiplying(color1, 2.0);

	// ASSERT
	print_result(num_test, COLOR, expected, result);
}

void	test_color_hadamard(int num_test)
{
	// ARRANGE
	t_color	color1 = color(1, 0.2, 0.4);
	t_color	color2 = color(0.9, 1, 0.1);
	t_color	expected = color(0.9, 0.2, 0.04);
	t_color	result;

	// ACT
	result = hadamard_product(color1, color2);

	// ASSERT
	print_result(num_test, COLOR, expected, result);
}

// void	test_canvas_create(int num_test)
// {
// 	// ARRANGE
// 	mlx_set_setting(MLX_HEADLESS, true);
//
// 	void		*mlx = mlx_init(100, 100, "test", true);
// 	mlx_image_t	*img;
//
// 	// ACT
// 	img = mlx_new_image(mlx, 100, 100);
//
// 	// ASSERT
// 	print_result(num_test);
// }

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_color,
		test_color_adding,
		test_color_subtracting,
		test_color_multiplying,
		test_color_hadamard,
	};

	printf("\n%sTESTING COLORS:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
