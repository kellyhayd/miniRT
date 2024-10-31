/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   modification.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:57:37 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/31 08:47:46 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples.h"
#include "minirt.h"

/**
 * @brief Multiplies corresponding elements of two matrices at a given position.
 *
 * This static function takes two matrices and multiplies their elements at the
 * specified row (y) and column (x). It is used internally within the module to
 * perform element-wise multiplication.
 *
 * @param matrix1 The first matrix.
 * @param matrix2 The second matrix.
 * @param y The row index of the element to be multiplied.
 * @param x The column index of the element to be multiplied.
 * @return The product of the elements at the specified position in the two
 * matrices.
 */
static double	mult_element(t_matrix matrix1, t_matrix matrix2, int y, int x)
{
	int		idx;
	double	value;

	idx = 0;
	value = 0;
	while (idx < matrix1.cols)
	{
		value += mx_get(&matrix1, y, idx) * mx_get(&matrix2, idx, x);
		idx++;
	}
	return (value);
}

/**
 * @brief Multiplies two matrices and returns the resulting matrix.
 *
 * This function takes two matrices as input and performs matrix multiplication.
 * The resulting matrix is returned.
 *
 * @param matrix1 The first matrix to be multiplied.
 * @param matrix2 The second matrix to be multiplied.
 * @return The resulting matrix after multiplication.
 */
t_matrix	mx_multiply(t_matrix matrix1, t_matrix matrix2)
{
	t_matrix	result;
	int			i;
	int			j;

	ft_bzero(&result, sizeof(t_matrix));
	if (matrix1.cols != matrix2.cols || matrix1.rows != matrix2.rows)
		return (result);
	result.rows = matrix1.rows;
	result.cols = matrix1.cols;
	j = 0;
	while (j < matrix1.rows)
	{
		i = 0;
		while (i < matrix1.cols)
		{
			mx_set(&result, j, i, mult_element(matrix1, matrix2, j, i));
			i++;
		}
		j++;
	}
	return (result);
}

/**
 * Multiplies a matrix by a tuple.
 *
 * @param matrix The matrix to be multiplied.
 * @param tuple1 The tuple to be multiplied by the matrix.
 * @return The resulting tuple after the multiplication.
 */
t_tuple	mx_multiply_tuple(t_matrix matrix, t_tuple tuple1)
{
	int		i;
	double	values_tuple[4];
	t_tuple	result;

	if (matrix.cols != 4 || matrix.rows != 4)
		return ((t_tuple){.x = 0, .y = 0, .z = 0, .w = 0});
	i = 0;
	while (i < matrix.cols)
	{
		values_tuple[i] = mx_get(&matrix, i, 0) * tuple1.x
			+ mx_get(&matrix, i, 1) * tuple1.y
			+ mx_get(&matrix, i, 2) * tuple1.z
			+ mx_get(&matrix, i, 3) * tuple1.w;
		i++;
	}
	result.x = values_tuple[0];
	result.y = values_tuple[1];
	result.z = values_tuple[2];
	result.w = values_tuple[3];
	return (result);
}

/**
 * @brief Transposes the given matrix.
 *
 * This function takes a matrix as input and returns its transpose.
 * The transpose of a matrix is obtained by swapping its rows and columns.
 *
 * @param matrix The matrix to be transposed.
 * @return The transposed matrix.
 */
t_matrix	transpose(t_matrix matrix)
{
	int			x;
	int			y;
	t_matrix	result;

	result.cols = matrix.cols;
	result.rows = matrix.rows;
	y = 0;
	while (y < matrix.rows)
	{
		x = 0;
		while (x < matrix.cols)
		{
			mx_set(&result, y, x, mx_get(&matrix, x, y));
			x++;
		}
		y++;
	}
	return (result);
}

/**
 * @brief Computes the inverse of a given matrix.
 *
 * This function takes a matrix as input and returns its inverse.
 * The input matrix is expected to be a square matrix.
 *
 * @param matrix The matrix to be inverted.
 * @return The inverse of the input matrix.
 */
t_matrix	inverse(t_matrix matrix)
{
	int			x;
	int			y;
	double		matrix_cofactor;
	double		matrix_determinant;
	t_matrix	result;

	result.cols = matrix.cols;
	result.rows = matrix.rows;
	matrix_determinant = determinant(matrix);
	if (matrix_determinant == 0)
		return (identity());
	matrix_cofactor = 0;
	y = 0;
	while (y < result.rows)
	{
		x = 0;
		while (x < result.cols)
		{
			matrix_cofactor = cofactor(matrix, x, y);
			mx_set(&result, y, x, matrix_cofactor / matrix_determinant);
			x++;
		}
		y++;
	}
	return (result);
}
