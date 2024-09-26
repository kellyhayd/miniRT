/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   world.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/26 08:14:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/26 08:36:34 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_world	world(void)
{
	t_world	w;

	w.shape = NULL;
	w.src_light = point_light(point(0, 0, 0), color(1, 1, 1));
	return (w);
}

t_world	default_world(void)
{
	t_world	w;
	t_shape	s1;
	t_shape	s2;

	w.src_light = point_light(point(-10, 10, -10), color(1, 1, 1));
	s1 = sphere();
	set_transformation(&s1, scaling(0.5, 0.5, 0.5));
	s2 = sphere();
	set_transformation(&s2, scaling(0.5, 0.5, 0.5));
	w.shape = malloc(sizeof(t_shape) * 2);
	w.shape[0] = s1;
	w.shape[1] = s2;
	return (w);
}


/*
Scenario: The default world
Given light ← point_light(point(-10, 10,-10), color(1, 1, 1))
And s1 ← sphere() with: | material.color | (0.8, 1.0, 0.6) | material.diffuse | 0.7 | material.specular | 0.2 And s2 ← sphere() with: | transform | scaling(0.5, 0.5, 0.5) |
When w ← default_world()
Then w.light = light
And w contains s1 And w contains s2
*/


/*
Scenario: Creating a world
Given w ← world()
Then w contains no objects
And w has no light source
*/
