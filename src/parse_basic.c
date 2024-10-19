/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_basic.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:02:47 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/19 10:03:15 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_color(char *splitted, t_color *new_color)
{
	char	**colors;

	*new_color = color(0, 0, 0);
	colors = ft_split(splitted, ',');
	if (!validate_count(colors, 3) || !is_all_numbers(colors)
		|| !validate_color_range(colors))
	{
		ft_free_split(colors);
		return (false);
	}
	*new_color = color(ft_atoi(colors[0]), \
					ft_atoi(colors[1]), \
					ft_atoi(colors[2]));
	ft_free_split(colors);
	return (true);
}

bool	parse_brightness(char *splitted, double *brightness)
{
	*brightness = ft_atof(splitted);
	if (*brightness < 0 || *brightness > 1)
		return (false);
	return (true);
}

bool	parse_coordinates(char *splitted, t_point *position)
{
	char	**coordinates;

	*position = point(0, 0, 0);
	coordinates = ft_split(splitted, ',');
	if (!validate_count(coordinates, 3) || !is_all_numbers(coordinates))
		{
			ft_free_split(coordinates);
			return (false);
		}
	position->x = ft_atof(coordinates[0]);
	position->y = ft_atof(coordinates[1]);
	position->z = ft_atof(coordinates[2]);
	ft_free_split(coordinates);
	return (true);
}
