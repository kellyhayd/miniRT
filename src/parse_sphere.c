/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_sphere.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 20:42:43 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/15 20:54:10 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_sphere(char *line, t_world *world)
{
	t_point	position;
	t_color	new_color;
	t_shape	new_sphere;
	double	radius;
	char	*splitted;

	splitted = ft_split(line, ',');
	radius = 0.0;
	if (!validate_count(splitted, 4) \
		|| !parse_coordinates(splitted[1]) \
		|| !parse_radius(splitted[2]) \
		|| !parse_color(splitted[3]))
		{
			ft_free_split(splitted);
			return (false);
		}
	new_sphere = sphere();
	new_sphere.sphere_shape.origin = position;
	new_sphere.sphere_shape.radius = radius;
	new_sphere.shape_type = SPHERE;
	add_shape(&world->shape, new_sphere);
}

/*
# Sphere
# <coordinates: x,y,z> <diameter> <color:red,green,blue>
sp  0,0,0                1               255,51,255
*/

/*
	t_color	new_color;
	t_point	position;
	double	bright;
	char	**splitted;

	splitted = ft_split(line, ' ');
	bright = 0;
	if (!validate_count(splitted, 4) \
		|| !parse_coordinates(splitted[1], &position) \
		|| !parse_brightness(splitted[2], &bright) \
		|| !parse_color(splitted[3], &new_color))
		{
			ft_free_split(splitted);
			return (false);
		}
	add_light(&world->light, point_light(position, color_multiply(new_color, bright)));
	ft_free_split(splitted);
	return (true);
*/
