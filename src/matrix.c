/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:03:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/21 21:27:509 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	matrix_create(double *tab, int rows, int cols)
{
	double		*new_tab;
	t_matrix	matrix;

	new_tab = malloc(rows * cols * sizeof(double));
	ft_memcpy(new_tab, tab, rows * cols * sizeof(double));
	matrix.rows = rows;
	matrix.cols = cols;
	matrix.tab = new_tab;
	return (matrix);
}

int	matrix_compare(t_matrix matrix1, t_matrix matrix2)
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

double	multiply_element(t_matrix matrix1, t_matrix matrix2, int i, int j)
{
	int		idx;
	double	value;

	idx = 0;
	value = 0;
	while (idx < matrix1.cols)
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

	if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows)
		return ((t_matrix){.cols = 0, .rows = 0, .tab = NULL});
	new_tab = malloc(sizeof(double) * matrix1.rows * matrix1.cols);
	result.tab = new_tab;
	result.rows = matrix1.rows;
	result.cols = matrix1.cols;
	j = 0;
	while (j < matrix1.rows)
	{
		i = 0;
		while (i < matrix1.cols)
		{
			matrix_set(result, i, j, multiply_element(matrix1, matrix2, i, j));
			i++;
		}
		j++;
	}
	return (result);
}

t_tuple	matrix_multiply_tuple(t_matrix matrix, t_tuple tuple1)
{
	int		i;
	double	values_tuple[4];
	t_tuple	result;

	if (matrix.cols != 4 || matrix.rows != 4)
		return ((t_tuple){.x = 0, .y = 0, .z = 0, .w = 0});
	i = 0;
	while (i < matrix.cols)
	{
		values_tuple[i] = matrix_get(matrix, 0, i) * tuple1.x + \
							matrix_get(matrix, 1, i) * tuple1.y + \
							matrix_get(matrix, 2, i) * tuple1.z + \
							matrix_get(matrix, 3, i) * tuple1.w;
		i++;
	}
	result.x = values_tuple[0];
	result.y = values_tuple[1];
	result.z = values_tuple[2];
	result.w = values_tuple[3];
	return (result);
}

t_matrix	matrix_transposing(t_matrix matrix)
{
	int			x;
	int			y;
	t_matrix	result;

	result.tab = malloc(sizeof(double) * matrix.rows * matrix.cols);
	result.cols = matrix.cols;
	result.rows = matrix.rows;
	y = 0;
	while (y < matrix.rows)
	{
		x = 0;
		while (x < matrix.cols)
		{
			matrix_set(result, x, y, matrix_get(matrix, y, x));
			x++;
		}
		y++;
	}
	return (result);
}

double	matrix_determinant(t_matrix matrix)
{
	double	result;
	int		col;

	col = 0;
	result = 0;
	if (matrix.cols == 2 && matrix.rows == 2)
		result = matrix_get(matrix, 0, 0) * matrix_get(matrix, 1, 1) -
				matrix_get(matrix, 1, 0) * matrix_get(matrix, 0, 1);
	else
	{
		while (col < matrix.cols)
		{
			result += matrix_get(matrix, 0, col) * matrix_cofactor(matrix, 0, col);
			col++;
		}
	}
	return (result);
}

t_matrix	matrix_submatrix(t_matrix matrix, int x, int y)
{
	int			i_m1;
	int			j_m1;
	int			i_res;
	int			j_res;
	t_matrix	result;

	result.cols = matrix.cols - 1;
	result.rows = matrix.rows - 1;
	result.tab = malloc(sizeof(double) * result.cols * result.rows);
	j_m1 = 0;
	j_res = 0;
	while (j_m1 < matrix.rows)
	{
		i_m1 = 0;
		i_res = 0;
		while (i_m1 < matrix.cols)
		{
			if (i_m1 != x && j_m1 != y)
				matrix_set(result, i_res++, j_res, matrix_get(matrix, i_m1, j_m1));
			i_m1++;
		}
		j_res = j_res + (j_m1 != y);
		j_m1++;
	}
	return (result);
}

double	matrix_minor(t_matrix matrix, int x, int j)
{
	t_matrix	sub_matrix;
	double		minor;

	sub_matrix = matrix_submatrix(matrix, x, j);
	minor = matrix_determinant(sub_matrix);
	return (minor);
}

double	matrix_cofactor(t_matrix matrix, int x, int y)
{
	double	minor;
	double	cofactor;

	minor = matrix_minor(matrix, x, y);
	if ((x + y) % 2 != 0)
		cofactor = -minor;
	else
		cofactor = minor;
	return (cofactor);
}
t_matrix	matrix_inverse(t_matrix matrix)
{
	int			i;
	int			j;
	double		cofactor;
	double		determinant;
	t_matrix	result;

	result.cols = matrix.cols;
	result.rows = matrix.rows;
	result.tab = malloc(sizeof(double) * result.cols * result.rows);
	determinant = matrix_determinant(matrix);
	if (determinant == 0)
		return (result);
	cofactor = 0;
	j = -1;
	while (++j < result.rows)
	{
		i = -1;
		while (++i < result.cols)
		{
			cofactor = matrix_cofactor(matrix, i, j);
			matrix_set(result, j, i, cofactor / determinant);
		}
	}
	return (result);
}
