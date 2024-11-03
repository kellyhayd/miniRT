/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:42:43 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:50:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

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
	t_point		position;
	t_shape		new_sphere;
	char		**splitted;

	new_sphere = sphere();
	splitted = ft_split(line, ' ');
	if (!parse_coordinates(splitted[1], &position)
		|| !parse_radius(splitted[2], &new_sphere.sphere_shape.radius)
		|| !parse_color(splitted[3], &new_sphere.material.color)
		|| !parse_mater_shape(&splitted[4], &new_sphere.material, world)
		|| !validade_optionals(&splitted[4]))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	new_sphere.sphere_shape.radius /= 2;
	set_transformation(&new_sphere, rotation_matrix(position, point(0, 1, 0),
			new_sphere));
	add_shape(&world->shape, new_sphere);
	return (true);
}
