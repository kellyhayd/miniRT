/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_lights.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:15:43 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/15 20:37:28 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_all_numbers(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		if (split[i][j] == '-')
			j++;
		while (split[i][j] != '\0' && split[i][j] != '\n')
		{
			if (!ft_isdigit(split[i][j]) && split[i][j] != '.')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_count(char **split, int count)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != count)
		return (false);
	return (true);
}

bool	validate_color_range(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_atoi(str[i]) < 0 || ft_atoi(str[i]) > 255)
			return (false);
		i++;
	}
	return (true);
}

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

bool	parse_light(char *line, t_world *world)
{
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
}
