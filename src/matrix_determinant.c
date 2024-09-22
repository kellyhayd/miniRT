/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:55:40 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/22 16:03:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

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

t_matrix	submatrix(t_matrix matrix, int y, int x)
{
	int			im1;
	int			jm1;
	int			im2;
	int			jm2;
	t_matrix	result;

	result.cols = matrix.cols - 1;
	result.rows = matrix.rows - 1;
	jm1 = 0;
	jm2 = 0;
	while (jm1 < matrix.rows)
	{
		im1 = 0;
		im2 = 0;
		while (im1 < matrix.cols)
		{
			if (im1 != x && jm1 != y)
				mx_set(&result, jm2, im2++, mx_get(&matrix, jm1, im1));
			im1++;
		}
		if (jm1 != y)
			jm2++;
		jm1++;
	}
	return (result);
}
		// jres = jres + (jm1 != y);		// if jm1 != y then jres += 1

double	minor(t_matrix matrix, int y, int x)
{
	t_matrix	sub_matrix;
	double		minor;

	sub_matrix = submatrix(matrix, y, x);
	minor = determinant(sub_matrix);
	return (minor);
}

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
