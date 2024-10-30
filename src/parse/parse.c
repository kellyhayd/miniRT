/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 20:14:11 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/30 07:35:47 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

int	get_token(char *line)
{
	if (ft_strncmp(line, "A ", 2) == 0)
		return (AMBIENT);
	else if (ft_strncmp(line, "C ", 2) == 0)
		return (CAMERA);
	else if (ft_strncmp(line, "L ", 2) == 0)
		return (LIGHT);
	else if (ft_strncmp(line, "sp ", 3) == 0)
		return (SPHERE);
	else if (ft_strncmp(line, "pl ", 3) == 0)
		return (PLANE);
	else if (ft_strncmp(line, "cy ", 3) == 0)
		return (CYLINDER);
	else if (ft_strncmp(line, "cn ", 3) == 0)
		return (CONE);
	else if (ft_strncmp(line, "m ", 2) == 0)
		return (MATERIAL);
	else if (ft_strncmp(line, "p ", 2) == 0)
		return (PATTERN);
	else
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putendl_fd("Unexpected element", 2);
		return (-1);
	}
}

bool	parse_line(char *line, t_world *world)
{
	int	token;

	if (!line[0] || line[0] == '\n' || line[0] == '#')
		return (true);
	token = get_token(line);
	if (token == -1)
		return (false);
	if (token == AMBIENT)
		return (parse_ambient(line, world));
	else if (token == CAMERA)
		return (parse_camera(line, world));
	else if (token == LIGHT)
		return (parse_light(line, world));
	else if (token == MATERIAL)
		return (parse_material(line, world));
	else if (token == PATTERN)
		return (parse_pattern(line, world));
	else if (token == SPHERE)
		return (parse_sphere(line, world));
	else if (token == PLANE)
		return (parse_plane(line, world));
	else if (token == CYLINDER)
		return (parse_cylinder(line, world));
	else
		return (parse_cone(line, world));
}

void	finish_parsing(t_world *world)
{
	put_ambient_color(world);
	clear_material_list(world);
	clear_pattern_list(world);
}

bool	parse(int fd, t_world *world)
{
	int		state;
	int		count_line;
	char	*line;

	state = true;
	count_line = 1;
	init_default_material(world);
	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strchr(line, '\n'))
			ft_strchr(line, '\n')[0] = '\0';
		if (!parse_line(line, world))
		{
			print_line_error(line, count_line);
			state = false;
			break ;
		}
		free(line);
		line = get_next_line(fd);
		count_line++;
	}
	state = state && pos_validation(world);
	finish_parsing(world);
	return (state);
}
