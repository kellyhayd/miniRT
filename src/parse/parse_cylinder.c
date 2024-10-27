/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:06:20 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/20 18:05:44 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_cylinder(char *line, t_world *world)
{
	double		radius;
	t_point		position;
	t_vector	normal;
	t_shape		new_cylinder;
	char		**splitted;

	new_cylinder = cylinder();
	splitted = ft_split(line, ' ');
	if (
		// !validate_count(splitted, 6)
		!parse_coordinates(splitted[1], &position)
		|| !parse_direction(splitted[2], &normal)
		|| !parse_double(splitted[3], &radius)
		|| !parse_double(splitted[4], &new_cylinder.cylinder_shape.maximum)
		|| !parse_color(splitted[5], &new_cylinder.material.color)
		|| !parse_material_name(splitted[6], &new_cylinder.material, world)
		|| (splitted[6] && splitted[7])
		)
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	new_cylinder.cylinder_shape.minimum = 0;
	new_cylinder.cylinder_shape.closed = true;
	set_transformation(&new_cylinder, mx_multiply(
			translation(position.x, position.y, position.x),
			rotation_matrix(normal)));
	add_shape(&world->shape, new_cylinder);
	return (true);
}

/*
#Cylinder
# <coordinates: x,y,z> <normal: x,y,z> <diameter> <height> <color:red,green,blue>
cy  50.0,0.0,20.6         0,0,1.0        14.2       21.42          10,0,255
*/
