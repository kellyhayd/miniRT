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
	t_point		position;
	t_vector	normal;
	t_shape		new_cylinder;
	char		**splitted;

	new_cylinder = cylinder();
	splitted = ft_split(line, ' ');
	if (!parse_coordinates(splitted[1], &position)
		|| !parse_direction(splitted[2], &normal)
		|| !parse_double(splitted[3], &new_cylinder.cylinder_shape.radius)
		|| !parse_double(splitted[4], &new_cylinder.cylinder_shape.maximum)
		|| !parse_color(splitted[5], &new_cylinder.material.color)
		|| !parse_material_shape(&splitted[6], &new_cylinder.material, world)
		|| !validade_optionals(&splitted[6]))
		return (ft_free_split(splitted), false);
	ft_free_split(splitted);
	new_cylinder.cylinder_shape.radius /= 2;
	new_cylinder.cylinder_shape.maximum /= new_cylinder.cylinder_shape.radius;
	new_cylinder.cylinder_shape.minimum = 0;
	new_cylinder.cylinder_shape.closed = true;
	set_transformation(&new_cylinder, rotation_matrix(position, normal,
		new_cylinder));
	add_shape(&world->shape, new_cylinder);
	return (true);
}
