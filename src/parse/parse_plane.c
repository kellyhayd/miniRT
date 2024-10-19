/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:40:14 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/19 11:11:02 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_plane(char *line, t_world *world)
{
	t_point		position;
	t_vector	normal;
	t_color		new_color;
	t_shape		new_plane;
	char		**splitted;

	splitted = ft_split(line, ' ');
	if (!validate_count(splitted, 4) \
		|| !parse_coordinates(splitted[1], &position) \
		|| !parse_normal(splitted[2], &normal) \
		|| !parse_color(splitted[3], &new_color))
	{
		ft_free_split(splitted);
		return (false);
	}
	new_plane = plane();
	new_plane.plane_shape.origin = position;
	// new_plane.plane_shape.normal = normal;
	new_plane.shape_type = PLANE;
	new_plane.material = material();
	new_plane.material.color = new_color;
	add_shape(&world->shape, new_plane);
	return (ft_free_split(splitted), true);
}

// onde colocar a normal do plano? adicionar um campo no struct plane_shape?

/*
# Plane
# <coordinates: x,y,z> <normal: x,y,z> <color:red,green,blue>
pl  0,0,0                0,1.0,0           255,0,225
*/
