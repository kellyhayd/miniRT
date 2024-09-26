/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   determinant.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:55:40 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 15:25:45 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Calculates the determinant of a given matrix.
 *
 * This function takes a matrix of type `t_matrix` and computes its determinant.
 * The determinant is a scalar value that can be computed from the elements of a square matrix
 * and encodes certain properties of the matrix.
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
 * Extracts a submatrix from the given matrix by removing the specified row and column.
 *
 * @param matrix The original matrix from which the submatrix will be extracted.
 * @param y The row index to be removed from the original matrix.
 * @param x The column index to be removed from the original matrix.
 * @return A new matrix that is the submatrix of the original matrix with the specified row and column removed.
 */
t_matrix	submatrix(t_matrix matrix, int y, int x)
{
	int			x_matrix1;
	int			y_matrix1;
	int			x_matrix2;
	int			y_matrix2;
	t_matrix	result;

	result.cols = matrix.cols - 1;
	result.rows = matrix.rows - 1;
	y_matrix1 = 0;
	y_matrix2 = 0;
	while (y_matrix1 < matrix.rows)
	{
		x_matrix1 = 0;
		x_matrix2 = 0;
		while (x_matrix1 < matrix.cols)
		{
			if (x_matrix1 != x && y_matrix1 != y)
			{
				mx_set(&result, y_matrix2, x_matrix2, mx_get(&matrix, y_matrix1, x_matrix1));
				x_matrix2++;
			}
			x_matrix1++;
		}

		//////////////////////////////////////////////
		// NÃO TIRAR ISSO POR ENQUANTO, PODE SER ÚTIL, SE PRECISAR ECONOMIZAR LINHAS DEPOIS
		//
		// jres = jres + (y_matrix1 != y);		// if y_matrix1 != y then jres += 1
		//

		// ISSO É O MESMO QUE O DE CIMA, MAS MAIS LEGÍVEL
		if (y_matrix1 != y)
			y_matrix2++;

		//////////////////////////////////////////////

		y_matrix1++;
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
