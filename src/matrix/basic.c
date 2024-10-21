/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   basic.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 14:01:17 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 22:12:41 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Creates a matrix with the given data.
 *
 * This function initializes a matrix structure with the provided data array,
 * number of rows, and number of columns.
 *
 * @param tab A pointer to a double array containing the matrix data.
 * @param rows The number of rows in the matrix.
 * @param cols The number of columns in the matrix.
 * @return A t_matrix structure representing the created matrix.
 */
t_matrix	matrix_create(double *tab, int rows, int cols)
{
	t_matrix	matrix;

	matrix.rows = rows;
	matrix.cols = cols;
	ft_memcpy(matrix.tab, tab, sizeof(double) * rows * cols);
	return (matrix);
}

/**
 * @brief Compares two matrices for equality.
 *
 * This function takes two matrices as input and compares them element by
 * element. It returns a non-zero value if the matrices are equal, and zero
 * if they are not.
 *
 * @param matrix1 The first matrix to compare.
 * @param matrix2 The second matrix to compare.
 * @return int Non-zero if the matrices are equal, zero otherwise.
 */
int	mx_compare(t_matrix matrix1, t_matrix matrix2)
{
	// FUNÇÃO USADA APENAS NOS TESTES

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

/**
 * @brief Creates and returns an identity matrix.
 *
 * This function generates a 4x4 identity matrix, which is a square matrix
 * with ones on the main diagonal and zeros elsewhere. The identity matrix
 * is a fundamental concept in linear algebra and is used in various
 * mathematical and graphical computations.
 *
 * @return t_matrix The generated identity matrix.
 */
t_matrix	identity(void)
{
	t_matrix	result;

	result = (t_matrix) {0};
	result.cols = 4;
	result.rows = 4;
	mx_set(&result, 0, 0, 1);
	mx_set(&result, 1, 1, 1);
	mx_set(&result, 2, 2, 1);
	mx_set(&result, 3, 3, 1);
	return (result);
}
