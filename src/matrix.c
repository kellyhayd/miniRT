/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:03:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/19 20:53:33 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	matrix_create(double *tab, int row, int column)
{
	double		*new_tab;
	t_matrix	matrix;

	new_tab = malloc(row * column * sizeof(double));
	ft_memcpy(new_tab, tab, row * column * sizeof(double));
	matrix.row = row;
	matrix.column = column;
	matrix.tab = new_tab;
	return (matrix);
}

int	matrix_compare(t_matrix matrix1, t_matrix matrix2)
{
	int	i;
	int	size_all;

	if (matrix1.row != matrix2.row || matrix1.column != matrix2.column)
		return (0);
	i = 0;
	size_all = matrix1.row * matrix1.column;
	while (i < size_all)
	{
		if (matrix1.tab[i] != matrix2.tab[i])
			return (0);
		i++;
	}
	return (1);
}

static double	multiply_element(t_matrix matrix1, t_matrix matrix2, int i, int j)
{
	int		idx;
	double	value;

	idx = 0;
	value = 0;
	while (idx < matrix1.column)
	{
		value += matrix_get(matrix1, idx, j) * matrix_get(matrix2, i, idx);
		idx++;
	}
	return (value);
}

t_matrix	matrix_multiply(t_matrix matrix1, t_matrix matrix2)
{
	t_matrix	result;
	double		*new_tab;
	int			i;
	int			j;

	if (matrix1.column != matrix2.column || matrix1.row != matrix2.row)
	{
		ft_bzero(&result, sizeof(t_matrix));
		return (result);
	}
	new_tab = malloc(sizeof(double) * matrix1.row * matrix1.column);
	result.tab = new_tab;
	result.row = matrix1.row;
	result.column = matrix1.column;
	j = 0;
	while (j < matrix1.row)
	{
		i = 0;
		while (i < matrix1.column)
		{
			// value = matrix_get(matrix1, 0, j) * matrix_get(matrix2, i, 0) +
			// 		matrix_get(matrix1, 1, j) * matrix_get(matrix2, i, 1) +
			// 		matrix_get(matrix1, 2, j) * matrix_get(matrix2, i, 2) +
			// 		matrix_get(matrix1, 3, j) * matrix_get(matrix2, i, 3);
			matrix_set(result, i, j, multiply_element(matrix1, matrix2, i, j));
			i++;
		}
		j++;
	}
	return (result);

// 	value = matrix_get(matrix1, 0, 0) * matrix_get(matrix2, 0, 0) +
// 			matrix_get(matrix1, 1, 0) * matrix_get(matrix2, 0, 1) +
// 			matrix_get(matrix1, 2, 0) * matrix_get(matrix2, 0, 2) +
// 			matrix_get(matrix1, 3, 0) * matrix_get(matrix2, 0, 3);
// 	matrix_set(result, 0, 0, value);
//
// 	value = matrix_get(matrix1, 0, 0) * matrix_get(matrix2, 1, 0) +
// 			matrix_get(matrix1, 1, 0) * matrix_get(matrix2, 1, 1) +
// 			matrix_get(matrix1, 2, 0) * matrix_get(matrix2, 1, 2) +
// 			matrix_get(matrix1, 3, 0) * matrix_get(matrix2, 1, 3);
//
//
// 	value = matrix_get(matrix1, 0, 2) * matrix_get(matrix2, 2, 0) +
// 			matrix_get(matrix1, 1, 2) * matrix_get(matrix2, 2, 1) +
// 			matrix_get(matrix1, 2, 2) * matrix_get(matrix2, 2, 2) +
// 			matrix_get(matrix1, 3, 2) * matrix_get(matrix2, 2, 3);
}
