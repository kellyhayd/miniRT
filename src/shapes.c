/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:00:36 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/22 13:43:33 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_transformation(t_shape *shape, t_matrix tranformation)
{
	shape->transform = tranformation;
	shape->inverse = inverse(tranformation);
	shape->transpose = transposing(tranformation);
}
