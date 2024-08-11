/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_matrix.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:09:01 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/11 20:15:06 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

// 1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5

void	test_matrix_create(int num_test)
{
	// ARRANGE
	t_matrix	expected = {1, 2, 3, 4, 5.5, 6.5, 7.5, 8.5, 9, 10, 11, 12, 13.5, 14.5, 15.5, 16.5};
	t_matrix	result;

	// ACT
	result = create_matrix(-0.5, 0.4, 1.7);

	// ASSERT
	print_result(num_test, COLOR, expected, result);
}

int	main()
{
	void	(*test_funcs[])(int) =
	{
		test_color,
	};

	printf("\n%sTESTING COLORS:%s\n", YELLOW, RESET);

	for (int i = 0; i < sizeof(test_funcs) / sizeof(test_funcs[0]); i++) {
		test_funcs[i](i + 1);
	}

	return (0);
}
