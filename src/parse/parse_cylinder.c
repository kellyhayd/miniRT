/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cylinder.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 11:06:20 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/19 11:15:56 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_cylinder(char *line, t_world *world)
{
	t_point		position;
	t_vector	normal;
	t_color		new_color;
	t_shape		new_cylinder;
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
	new_cylinder = cylinder();
	new_cylinder.cylinder_shape.origin = position;
	// new_cylinder.cylinder_shape.normal = normal;
	new_cylinder.cylinder_shape.radius = ft_atof(splitted[3]);
	// new_cylinder.cylinder_shape.height = ft_atof(splitted[4]);
	new_cylinder.shape_type = CYLINDER;
	new_cylinder.material = material();
	new_cylinder.material.color = new_color;
	add_shape(&world->shape, new_cylinder);
	return (ft_free_split(splitted), true);
}

// onde colocar a normal e height do cilindro? adicionar campos no struct cylinder_shape?

/*
#Cylinder
# <coordinates: x,y,z> <normal: x,y,z> <diameter> <height> <color:red,green,blue>
cy  50.0,0.0,20.6         0,0,1.0        14.2       21.42          10,0,255
*/
