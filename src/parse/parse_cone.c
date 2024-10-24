/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:05:53 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/20 18:06:08 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_cone(char *line, t_world *world)
{
	double		radius;
	t_point		position;
	t_vector	normal;
	t_shape		new_cone;
	char		**splitted;

	new_cone = cone();
	splitted = ft_split(line, ' ');
	if (!validate_count(splitted, 6) \
		|| !parse_coordinates(splitted[1], &position) \
		|| !parse_direction(splitted[2], &normal) \
		|| !parse_double(splitted[3], &radius)
		|| !parse_double(splitted[4], &new_cone.cone_shape.maximum)
		|| !parse_color(splitted[5], &new_cone.material.color))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	new_cone.cone_shape.minimum = -new_cone.cone_shape.maximum;
	new_cone.cone_shape.closed = true;
	set_transformation(&new_cone, mx_multiply(rotation_matrix(normal),
			translation(position.x, position.y, position.x)));
	add_shape(&world->shape, new_cone);
	return (true);
}

/*
#cone
# <coordinates: x,y,z> <normal: x,y,z> <diameter> <height> <color:red,green,blue>
cy  50.0,0.0,20.6         0,0,1.0        14.2       21.42          10,0,255
*/
