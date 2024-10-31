/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:55:40 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/29 22:32:55 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculates the determinant of a given matrix.
 *
 * This function takes a matrix of type `t_matrix` and computes its determinant.
 * The determinant is a scalar value that can be computed from the elements of a
 * square matrix and encodes certain properties of the matrix.
 *
 * @param matrix The matrix for which the determinant is to be calculated.
 * @return The determinant of the matrix.
 */
double	determinant(t_matrix matrix)
{
	double	result;
	int		col;

	col = 0;
	result = 0;
	if (matrix.cols == 2 && matrix.rows == 2)
		result = mx_get(&matrix, 0, 0) * mx_get(&matrix, 1, 1)
			- mx_get(&matrix, 0, 1) * mx_get(&matrix, 1, 0);
	else
	{
		while (col < matrix.cols)
		{
			result += mx_get(&matrix, 0, col) * cofactor(matrix, 0, col);
			col++;
		}
	}
	return (result);
}

/**
 * Extracts a submatrix from the given matrix by removing the specified row
 * and column.
 *
 * @param matrix The original matrix from which the submatrix will be
 * extracted.
 * @param y The row index to be removed from the original matrix.
 * @param x The column index to be removed from the original matrix.
 * @return A new matrix that is the submatrix of the original matrix with the
 * specified row and column removed.
 */
t_matrix	submatrix(t_matrix matrix, int y, int x)
{
	int			x_mx1;
	int			y_mx1;
	int			x_mx2;
	int			y_mx2;
	t_matrix	result;

	result.cols = matrix.cols - 1;
	result.rows = matrix.rows - 1;
	y_mx1 = -1;
	y_mx2 = 0;
	while (++y_mx1 < matrix.rows)
	{
		x_mx1 = -1;
		x_mx2 = 0;
		while (++x_mx1 < matrix.cols)
		{
			if (x_mx1 != x && y_mx1 != y)
			{
				mx_set(&result, y_mx2, x_mx2, mx_get(&matrix, y_mx1, x_mx1));
				x_mx2++;
			}
		}
		y_mx2 += (y_mx1 != y);
	}
	return (result);
}

/**
 * Calculates the minor of a matrix element.
 *
 * @param matrix The matrix from which to calculate the minor.
 * @param y The row index of the element.
 * @param x The column index of the element.
 * @return The minor of the specified element in the matrix.
 */
double	minor(t_matrix matrix, int y, int x)
{
	t_matrix	sub_matrix;
	double		minor;

	sub_matrix = submatrix(matrix, y, x);
	minor = determinant(sub_matrix);
	return (minor);
}

/**
 * @brief Computes the cofactor of a given element in a matrix.
 *
 * This function calculates the cofactor of the element located at the
 * specified row (y) and column (x) in the provided matrix.
 *
 * @param matrix The matrix from which to compute the cofactor.
 * @param y The row index of the element.
 * @param x The column index of the element.
 * @return The cofactor of the specified element.
 */
double	cofactor(t_matrix matrix, int y, int x)
{
	double	matrix_minor;
	double	cofactor;

	matrix_minor = minor(matrix, y, x);
	if ((x + y) % 2 != 0)
		cofactor = -matrix_minor;
	else
		cofactor = matrix_minor;
	return (cofactor);
}
