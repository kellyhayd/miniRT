/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_tuples.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:32:15 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/05 21:45:53 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	print_ok(int num_test)
{
	printf(PURPLE "%d" RESET " - " GREEN "[ ✓ ]\n" RESET, num_test);
}

void	print_ko(int num_test, t_tuple expected, t_tuple result)
{
	printf(PURPLE "%d" RESET " - " RED "[ ✗ ]" RESET
	" Expected: (%.3lf, %.3lf, %.3lf, %.3lf) \
	RESULT: (%.3lf, %.3lf, %.3lf, %.3lf)\n", \
	num_test, expected.x, expected.y, expected.z, expected.w, result.x, result.y, result.z, result.w);
}

void test_tuple_1(int num_test) {

	// ARRANGE
	t_tuple	expected = {4.3, -4.2, 3.1, 1.0};
	t_tuple result;

	// ACT
	result = tuple(4.3, -4.2, 3.1, 1.0);

	// ASSERT
	if (tuple_compare(expected, result) == 1)
		print_ok(num_test);
	else
		print_ko(num_test, expected, result);
}

int	main()
{
	test_tuple_1(1);

	return (0);
}
