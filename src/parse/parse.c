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
	else if (token == CONE)
		return (parse_cone(line, world));
	return (true);
}

bool	pos_validation(t_world *world)
{
	bool	state;

	state = true;
	if (!world->scene.has_ambient_color)
		state = print_error("There must be 1 ambient color");
	if (!world->scene.has_camera)
		state = print_error("There must be 1 camera");
	if (!world->light)
		state = print_error("There must be at least 1 light");
	if (!world->shape)
		state = print_error("There must be at least 1 object in the scene");
	return (state);
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
			// Isso pode virar uma função
			ft_putstr_fd(BLUE "Line: " RESET, 2);
			if (count_line < 10)
				ft_putchar_fd('0', 2);
			ft_putnbr_fd(count_line, 2);
			ft_putstr_fd(" | ", 2);
			ft_putendl_fd(line, 2);
			////////////////////////////////

			free(line);
			state = false;
			break ;
		}
		free(line);
		line = get_next_line(fd);
		count_line++;
	}
	if (state && !pos_validation(world))
		state = false;
	put_ambient_color(world);
	clear_material_list(world);
	clear_pattern_list(world);
	return (state);
}
