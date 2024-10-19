/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:42:43 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/19 10:04:25 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_sphere(char *line, t_world *world)
{
	t_point	position;
	t_color	new_color;
	t_shape	new_sphere;
	char	**splitted;

	splitted = ft_split(line, ' ');
	if (!validate_count(splitted, 4) \
		|| !parse_coordinates(splitted[1], &position) \
		|| !parse_color(splitted[3], &new_color))
		{
			ft_free_split(splitted);
			return (false);
		}
	new_sphere = sphere();
	new_sphere.sphere_shape.origin = position;
	new_sphere.sphere_shape.radius = ft_atof(splitted[2]);
	new_sphere.shape_type = SPHERE;
	new_sphere.material = material();
	new_sphere.material.color = new_color;
	add_shape(&world->shape, new_sphere);
	return (true);
}

/*
# Sphere
# <coordinates: x,y,z> <diameter> <color:red,green,blue>
sp  0,0,0                1               255,51,255
*/
