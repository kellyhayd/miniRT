/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 12:00:36 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/14 22:02:50 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	set_transformation(t_shape *shape, t_matrix tranformation)
{
	shape->transform = tranformation;
	shape->inverse = matrix_inverse(tranformation);
	shape->transpose = matrix_transposing(tranformation);
}
