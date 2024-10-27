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

int	sign(int number)
{
	if (number > 0)
		return 1;
	else if (number < 0)
		return -1;
	else
		return 0;
}

bool	parse_plane(char *line, t_world *world)
{
	t_point		position;
	t_vector	normal;
	t_shape		new_plane;
	char		**splitted;

	new_plane = plane();
	splitted = ft_split(line, ' ');
	if (
		// !validate_count(splitted, 4)
		!parse_coordinates(splitted[1], &position)
		|| !parse_direction(splitted[2], &normal)
		|| !parse_color(splitted[3], &new_plane.material.color)
		|| !parse_material_shape(&splitted[4], &new_plane.material, world)
		|| (splitted[4] && splitted[5] && splitted[6])
		)
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	set_transformation(&new_plane,
			mx_multiply(translation(position.x, sign(normal.y) * position.y, position.x),
			rotation_matrix(normal)
		));
	add_shape(&world->shape, new_plane);
	return (true);
}

/*
# Plane
# <coordinates: x,y,z> <normal: x,y,z> <color:red,green,blue>
pl  0,0,0                0,1.0,0           255,0,225
*/
