/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:14:11 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/20 18:05:20 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	get_token(char *line)
{
	if (ft_strncmp(line, "A", 1) == 0)
		return (AMBIENT);
	else if (ft_strncmp(line, "C", 1) == 0)
		return (CAMERA);
	else if (ft_strncmp(line, "L", 1) == 0)
		return (LIGHT);
	else if (ft_strncmp(line, "sp", 2) == 0)
		return (SPHERE);
	else if (ft_strncmp(line, "pl", 2) == 0)
		return (PLANE);
	else if (ft_strncmp(line, "cy", 2) == 0)
		return (CYLINDER);
	else if (ft_strncmp(line, "co", 2) == 0)		// Aqui é cn
		return (CONE);
	else
		return (-1);
}

bool	parse_line(char *line, t_world *world)
{
	int	token;

	token = get_token(line);
	printf("token: %d\n", token);
	// if (token == AMBIENT)
	// 	return (parse_ambient(line, world));
	// else if (token == CAMERA)
	// 	return (parse_camera(line, world));
	if (token == LIGHT)
		return (parse_light(line, world));
	else if (token == SPHERE)
		return (parse_sphere(line, world));
	else if (token == PLANE)
		return (parse_plane(line, world));
	else if (token == CYLINDER)
		return (parse_cylinder(line, world));
	else if (token == CONE)
		return (parse_cone(line, world));
	return (true);
}

bool	parse(int fd, t_world *world)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (line[0] != '\n' && line[0] != '#' && !parse_line(line, world))
		{
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	return (true);
}
