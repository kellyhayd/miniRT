/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   matrix.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 20:03:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/08/11 20:50:02 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_matrix	matrix_create(double *tab, int row, int column)
{
	double		*new_tab;
	t_matrix	matrix;

	new_tab = malloc(row * column * sizeof(double));
	ft_memcpy(new_tab, tab, row * column * sizeof(double));
	matrix.row = row;
	matrix.column = column;
	matrix.tab = new_tab;
	return (matrix);
}

int	matrix_compare(t_matrix matrix1, t_matrix matrix2)
{
	int	i;
	int	size_all;

	if (matrix1.row != matrix2.row || matrix1.column != matrix2.column)
		return (0);
	i = 0;
	size_all = matrix1.row * matrix1.column;
	while (i < size_all)
	{
		if (matrix1.tab[i] != matrix2.tab[i])
			return (0);
		i++;
	}
	return (1);
}
