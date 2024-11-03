/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_ambient.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:33:37 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/30 07:34:52 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

bool	validade_if_has_ambient_color(int has_ambient_color)
{
	if (has_ambient_color == 0)
		return (true);
	ft_putendl_fd(RED "Error!" RESET, 2);
	ft_putendl_fd("Only one ambient light allowed", 2);
	return (false);
}

bool	parse_ambient(char *line, t_world *world)
{
	double	ambient_ratio;
	t_color	ambient_color;
	char	**splitted;

	splitted = ft_split(line, ' ');
	if (!validate_count(splitted, 3)
		|| !validade_if_has_ambient_color(world->scene.has_ambient_color)
		|| !parse_double(splitted[1], &ambient_ratio)
		|| !parse_color(splitted[2], &ambient_color))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	world->scene.has_ambient_color = 1;
	world->scene.ambient_ratio = ambient_ratio;
	world->scene.ambient_color = ambient_color;
	return (true);
}
