/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:45:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/22 16:03:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	float_compare(double d1, double d2)
{
	return (fabs(d1 - d2) < EPSILON);
}

double	mx_get(t_matrix *matrix1, int y, int x)
{
	double	result;

	result = matrix1->tab[x + (y * matrix1->cols)];
	return (result);
}

void	mx_set(t_matrix *matrix1, int y, int x, double value)
{
	matrix1->tab[x + (y * matrix1->cols)] = value;
}
