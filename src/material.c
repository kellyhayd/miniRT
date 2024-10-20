/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   material.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 08:41:10 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/12 08:23:37 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_pattern	default_pattern(void)
{
	return ((t_pattern){
		.pattern_type = STRIPE,
		.has_pattern = false,
		.color_a = color(0, 0, 0),
		.color_b = color(0, 0, 0),
		.transform = identity(),
		.inverse = identity()
	});
}

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
		.ambient = 0.1,
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
