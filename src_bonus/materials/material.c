/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 08:41:10 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/31 06:13:28 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "shapes.h"

/**
 * @brief Creates and returns a default material.
 *
 * This function initializes a material structure with default values.
 * The default material can be used as a base for further customization.
 *
 * @return A t_material structure initialized with default values.
 */
t_material	material(void)
{
	return ((t_material){
		.color = color(1, 1, 1),
		.ambient = color_multiply(color(1, 1, 1), 0.1),
		.diffuse = 0.9,
		.specular = 0.9,
		.shininess = 200,
		.reflective = 0.0,
		.transparency = 0.0,
		.refractive_index = 1.0,
		.pattern = default_pattern()
	});
}

t_shape	glass_sphere(void)
{
	t_shape	g_sphere;

	g_sphere = sphere();
	g_sphere.material.transparency = 1.0;
	g_sphere.material.refractive_index = 1.5;
	return (g_sphere);
}
