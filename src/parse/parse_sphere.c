/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:42:43 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/19 11:11:14 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Parses a line to extract sphere data and adds it to the world.
 *
 * This function takes a line of text that describes a sphere and parses it to
 * extract the relevant sphere data. The extracted data is then added to the
 * world structure.
 *
 * @param line A string containing the sphere description.
 * @param world A pointer to the world structure where the sphere data will be
 *              added.
 *
 * @return Returns true if the sphere was successfully parsed and added to the
 *         world, false otherwise.
 */
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
	return (ft_free_split(splitted), true);
}

/*
# Sphere
# <coordinates: x,y,z> <diameter> <color:red,green,blue>
sp  0,0,0                1               255,51,255
*/
