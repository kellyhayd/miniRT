/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:03:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/21 20:23:33 by krocha-h         ###   ########.fr       */
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

double	multiply_element(t_matrix matrix1, t_matrix matrix2, int i, int j)
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
		return ((t_matrix){.column = 0, .row = 0, .tab = NULL});
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
			matrix_set(result, i, j, multiply_element(matrix1, matrix2, i, j));
			i++;
		}
		j++;
	}
	return (result);
}

t_tuple	matrix_multiply_tuple(t_matrix matrix1, t_tuple tuple1)
{
	int		i;
	double	values_tuple[4];
	t_tuple	result;

	if (matrix1.column != 4 || matrix1.row != 4)
		return ((t_tuple){.x = 0, .y = 0, .z = 0, .w = 0});
	i = 0;
	while (i < matrix1.column)
	{
		values_tuple[i] = matrix_get(matrix1, 0, i) * tuple1.x + \
							matrix_get(matrix1, 1, i) * tuple1.y + \
							matrix_get(matrix1, 2, i) * tuple1.z + \
							matrix_get(matrix1, 3, i) * tuple1.w;
		i++;
	}
	result.x = values_tuple[0];
	result.y = values_tuple[1];
	result.z = values_tuple[2];
	result.w = values_tuple[3];
	return (result);
}
