/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_plane_bonus.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:40:14 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:50:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

bool	parse_plane(char *line, t_world *world)
{
	t_point		position;
	t_vector	normal;
	t_shape		new_plane;
	char		**splitted;

	new_plane = plane();
	splitted = ft_split(line, ' ');
	if (!parse_coordinates(splitted[1], &position)
		|| !parse_direction(splitted[2], &normal)
		|| !parse_color(splitted[3], &new_plane.material.color)
		|| !parse_mater_shape(&splitted[4], &new_plane.material, world)
		|| !validade_optionals(&splitted[4]))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	set_transformation(&new_plane, rotation_matrix(position, normal,
			new_plane));
	add_shape(&world->shape, new_plane);
	return (true);
}
