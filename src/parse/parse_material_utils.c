/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_material_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:42:50 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/29 23:46:38 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	clear_material_list(t_world *world)
{
	t_material_lst	*current;
	t_material_lst	*next;

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

void	add_material(t_material_lst **mater_lst, t_material mater, char *name)
{
	t_material_lst	*new_material;
	t_material_lst	*last;

	new_material = malloc(sizeof(t_material_lst));
	new_material->material = mater;
	new_material->name = ft_strdup(name);
	new_material->next = NULL;
	if (!*mater_lst)
	{
		*mater_lst = new_material;
		return ;
	}
	last = *mater_lst;
	while (last->next)
		last = last->next;
	last->next = new_material;
}

bool	check_if_material_exists(char *name, t_world *world)
{
	t_material_lst	*current;

	current = world->scene.material_list;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(name)) == 0)
		{
			ft_putendl_fd(RED "Error!" RESET, 2);
			ft_putstr_fd("Material already exists: " GREEN, 2);
			ft_putstr_fd(name, 2);
			ft_putendl_fd(RESET, 2);
			return (false);
		}
		current = current->next;
	}
	return (true);
}
