/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   sphere.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/05 22:28:43 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/26 14:57:29 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Creates and returns a new sphere shape.
 *
 * This function initializes a new sphere shape and returns it.
 *
 * @return A new sphere shape.
 */
t_shape	sphere(void)
{
	t_shape	new_sphere;

	new_sphere.sphere_shape.origin = point(0, 0, 0);
	new_sphere.sphere_shape.radius = 1;
	new_sphere.transform = identity();
	new_sphere.inverse = identity();
	new_sphere.transpose = identity();
	new_sphere.material = material();
	return (new_sphere);
}
