/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_determinant.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/22 13:55:40 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/22 20:04:39 by danbarbo         ###   ########.fr       */
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
