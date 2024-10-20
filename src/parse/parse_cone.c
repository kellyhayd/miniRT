/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:05:53 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/20 15:19:52 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_cone(char *line, t_world *world)
{
	t_point		position;
	t_vector	normal;
	t_color		new_color;
	t_shape		new_cone;
	char		**splitted;

	splitted = ft_split(line, ' ');
	if (!validate_count(splitted, 6) \
		|| !parse_coordinates(splitted[1], &position) \
		|| !parse_normal(splitted[2], &normal) \
		|| !parse_color(splitted[5], &new_color))
	{
		ft_free_split(splitted);
		return (false);
	}
	new_cone = cone();
	new_cone.cone_shape.origin = position;
	// new_cone.cone_shape.normal = normal;
	new_cone.cone_shape.radius = ft_atof(splitted[3]);
	// new_cone.cone_shape.height = ft_atof(splitted[4]);
	new_cone.shape_type = CONE;
	new_cone.material = material();
	new_cone.material.color = new_color;
	add_shape(&world->shape, new_cone);
	return (ft_free_split(splitted), true);
}


/*
#Cylinder
# <coordinates: x,y,z> <normal: x,y,z> <diameter> <height> <color:red,green,blue>
cy  50.0,0.0,20.6         0,0,1.0        14.2       21.42          10,0,255
*/
