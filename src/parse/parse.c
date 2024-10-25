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
	else if (ft_strncmp(line, "cn", 2) == 0)
		return (CONE);
	else
		return (-1);
}

bool	parse_line(char *line, t_world *world)
{
	int	token;

	if (!line[0] || line[0] == '\n' || line[0] == '#')
		return (true);
	token = get_token(line);
	if (token == -1)
		return (false);
	printf("token: %d\n", token);
	if (token == AMBIENT)
		return (parse_ambient(line, world));
	else if (token == CAMERA)
		return (parse_camera(line, world));
	else if (token == LIGHT)
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

void	put_ambient_color(t_world *world)
{
	t_color	ambient_color;
	t_shape	*aux;

	ambient_color = color_multiply(world->scene.ambient_color,
		world->scene.ambient_ratio);
	aux = world->shape;
	while (aux)
	{
		aux->material.ambient = color_hadamard(ambient_color,
			aux->material.color);
		aux = aux->next;
	}
}

bool	pos_validation(t_world *world)
{
	bool	state;

	state = true;
	if (!world->scene.has_ambient_color)
	{
		state = false;
		printf("Error\nPrecisa ter 1 cor ambiente\n");
		// state = mensagem_de_erro(sem camera);
	}
	else if (!world->scene.has_camera)
	{
		state = false;
		printf("Error\nPrecisa ter 1 camera\n");
		// state = mensagem_de_erro(sem cor ambiente)
	}
	else if (!world->light)
	{
		state = false;
		printf("Error\nPrecisa ter pelo menos 1 luz\n");
		// state = mensagem_de_erro(sem luz);
	}
	else if (!world->shape)
	{
		state = false;
		// state = mensagem_de_erro(sem objetos);
	}
	return (state);
}

bool	parse(int fd, t_world *world)
{
	char	*line;

	line = get_next_line(fd);
	while (line != NULL)
	{
		if (ft_strchr(line, '\n'))
			ft_strchr(line, '\n')[0] = '\0';
		if (!parse_line(line, world))
		{
			free(line);
			return (false);
		}
		free(line);
		line = get_next_line(fd);
	}
	if (!pos_validation(world))
		return (false);
	put_ambient_color(world);
	return (true);
}
