/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:28:43 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/18 18:19:34 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	sphere(void)
{
	t_shape	new_sphere;

	new_sphere.sphere_shape.origin = point(0, 0, 0);
	new_sphere.sphere_shape.radius = 1;
	new_sphere.transform = matrix_identity();
	new_sphere.inverse = matrix_identity();
	new_sphere.transpose = matrix_identity();
	return (new_sphere);
}
