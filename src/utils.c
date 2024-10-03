/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:45:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/29 10:25:07 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Compares two floating-point numbers for equality.
 *
 * This function compares two double precision floating-point numbers
 * to determine if they are equal within a certain tolerance.
 *
 * @param d1 The first double to compare.
 * @param d2 The second double to compare.
 * @return An integer indicating the result of the comparison:
 *         1 if the numbers are considered equal (minor than EPSILON),
 *         0 otherwise.
 */
int	float_compare(double d1, double d2)
{
	return (fabs(d1 - d2) < EPSILON);
}

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

void	ft_error(char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error\n", 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(RESET, 2);
	exit(EXIT_FAILURE);
}

int	almost_zero(float num)
{
	return (num < EPSILON && num > -EPSILON);
}

void	swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}
