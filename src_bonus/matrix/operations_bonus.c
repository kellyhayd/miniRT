/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   operations_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:22:28 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:50:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "tuples_bonus.h"

/**
 * @brief Retrieves the value from a matrix at the specified row and column.
 *
 * @param matrix1 Pointer to the matrix from which the value is to be retrieved.
 * @param y The row index of the value to be retrieved.
 * @param x The column index of the value to be retrieved.
 * @return The value at the specified row and column in the matrix.
 */
double	mx_get(t_matrix *matrix1, int y, int x)
{
	double	result;

	result = matrix1->tab[x + (y * matrix1->cols)];
	return (result);
}

/**
 * @brief Sets a value in the specified position of a matrix.
 *
 * This function assigns the given value to the element at the specified
 * row (y) and column (x) in the provided matrix.
 *
 * @param matrix1 Pointer to the matrix where the value will be set.
 * @param y The row index where the value will be set.
 * @param x The column index where the value will be set.
 * @param value The value to be set in the matrix.
 */
void	mx_set(t_matrix *matrix1, int y, int x, double value)
{
	matrix1->tab[x + (y * matrix1->cols)] = value;
}
