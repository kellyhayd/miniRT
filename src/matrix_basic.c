/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_basic.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:01:17 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/22 16:15:29 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	matrix_create(double *tab, int rows, int cols)
{
	t_matrix	matrix;

	matrix.rows = rows;
	matrix.cols = cols;
	ft_memcpy(matrix.tab, tab, sizeof(double) * rows * cols);
	return (matrix);
}

int	mx_compare(t_matrix matrix1, t_matrix matrix2)
{
	int	i;
	int	size_all;

	if (matrix1.rows != matrix2.rows || matrix1.cols != matrix2.cols)
		return (0);
	i = 0;
	size_all = matrix1.rows * matrix1.cols;
	while (i < size_all)
	{
		if (matrix1.tab[i] != matrix2.tab[i])
			return (0);
		i++;
	}
	return (1);
}

t_matrix	identity(void)
{
	t_matrix	result;

	ft_bzero(&result.tab, sizeof(double) * 16);
	result.cols = 4;
	result.rows = 4;
	mx_set(&result, 0, 0, 1);
	mx_set(&result, 1, 1, 1);
	mx_set(&result, 2, 2, 1);
	mx_set(&result, 3, 3, 1);
	return (result);
}
