/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cone.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/20 14:05:53 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/30 08:04:59 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	parse_cone(char *line, t_world *world)
{
	t_point		position;
	t_vector	normal;
	t_shape		new_cone;
	char		**splitted;

	new_cone = cone();
	splitted = ft_split(line, ' ');
	if (!parse_coordinates(splitted[1], &position)
		|| !parse_direction(splitted[2], &normal)
		|| !parse_double(splitted[3], &new_cone.cone_shape.radius)
		|| !parse_double(splitted[4], &new_cone.cone_shape.maximum)
		|| !parse_color(splitted[5], &new_cone.material.color)
		|| !parse_mater_shape(&splitted[6], &new_cone.material, world)
		|| !validade_optionals(&splitted[6]))
		return (ft_free_split(splitted), false);
	ft_free_split(splitted);
	new_cone.cone_shape.radius /= 2;
	new_cone.cone_shape.maximum /= 2;
	new_cone.cone_shape.maximum /= new_cone.cone_shape.radius;
	new_cone.cone_shape.minimum = -new_cone.cone_shape.maximum;
	new_cone.cone_shape.closed = true;
	set_transformation(&new_cone, rotation_matrix(position, normal,
			new_cone));
	add_shape(&world->shape, new_cone);
	return (true);
}
