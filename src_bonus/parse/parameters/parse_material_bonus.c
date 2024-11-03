/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material_bonus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:33:19 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:50:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

bool	parse_material(char *line, t_world *world)
{
	t_material	material;
	char		**split;

	split = ft_split(line, ' ');
	if (!validate_count(split, 5)
		|| !check_if_material_exists(split[1], world)
		|| !parse_double(split[2], &material.reflective)
		|| !validate_double_range(split[2], material.reflective, 0, 1)
		|| !parse_double(split[3], &material.transparency)
		|| !validate_double_range(split[3], material.transparency, 0, 1)
		|| !parse_double(split[4], &material.refractive_index)
		|| !validate_double_range(split[4], material.refractive_index, \
			1, INFINITY))
	{
		ft_free_split(split);
		return (false);
	}
	add_material(&world->scene.material_list, material, split[1]);
	ft_free_split(split);
	return (true);
}

static	t_material_lst	*find_material(char *name, t_world *world)
{
	t_material_lst	*current;

	current = world->scene.material_list;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(current->name)) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

bool	parse_mater_name(char *str, t_material *material, t_world *world)
{
	t_material_lst	*find;

	if (!str)
		return (true);
	find = find_material(str, world);
	if (!find)
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putstr_fd("Material not found: " GREEN, 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(RESET, 2);
		return (false);
	}
	material->reflective = find->material.reflective;
	material->transparency = find->material.transparency;
	material->refractive_index = find->material.refractive_index;
	return (true);
}

bool	parse_mater_shape(char **splitted, t_material *mater, t_world *world)
{
	bool	status;

	status = true;
	if (splitted[0])
		status = parse_mater_name(splitted[0], mater, world);
	if (status && splitted[0] && splitted[1])
		status = parse_pattern_name(splitted[1], &mater->pattern, world);
	return (status);
}
