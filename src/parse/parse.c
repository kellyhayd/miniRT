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
	else if (ft_strncmp(line, "m", 1) == 0)
		return (MATERIAL);
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

	// Apenas para testes
	printf("token: %d\n", token);

	if (token == AMBIENT)
		return (parse_ambient(line, world));
	else if (token == CAMERA)
		return (parse_camera(line, world));
	else if (token == LIGHT)
		return (parse_light(line, world));
	else if (token == MATERIAL)
		return (parse_material(line, world));
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

bool	print_error(char *message)
{
	ft_putendl_fd(RED "Error" RESET, 2);
	ft_putendl_fd(message, 2);
	return (false);
}

bool	pos_validation(t_world *world)
{
	bool	state;

	state = true;
	if (!world->scene.has_ambient_color)
		state = print_error("There must be 1 ambient color");
	else if (!world->scene.has_camera)
		state = print_error("There must be 1 camera");
	else if (!world->light)
		state = print_error("There must be at least 1 light");
	else if (!world->shape)
		state = print_error("There must be at least 1 object in the scene");
	return (state);
}

void	add_material(t_material_list **material_list, t_material material, char *name)
{
	t_material_list	*new_material;
	t_material_list	*last;

	new_material = malloc(sizeof(t_material_list));
	new_material->material = material;
	new_material->name = ft_strdup(name);
	new_material->next = NULL;
	if (!*material_list)
	{
		*material_list = new_material;
		return ;
	}
	last = *material_list;
	while (last->next)
		last = last->next;
	last->next = new_material;
}

void	init_default_material(t_world *world)
{
	t_material	default_material;
	t_material	glass;
	t_material	transparent;
	t_material	reflective;

	default_material = material();
	glass = material();
	glass.transparency = 1.0;
	glass.refractive_index = 1.5;
	transparent = material();
	transparent.transparency = 1;
	reflective = material();
	reflective.reflective = 1;
	add_material(&world->scene.material_list, default_material, "default");
	add_material(&world->scene.material_list, glass, "glass");
	add_material(&world->scene.material_list, transparent, "transparent");
	add_material(&world->scene.material_list, reflective, "reflective");
}

void	clear_material_list(t_world *world)
{
	t_material_list	*current;
	t_material_list	*next;

	current = world->scene.material_list;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current);
		current = next;
	}
	world->scene.material_list = NULL;
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
	return (state);
}
