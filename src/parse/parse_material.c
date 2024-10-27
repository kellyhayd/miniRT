#include "minirt.h"

bool	validade_if_already_exists(char *name, t_world *world)
{
	t_material_list	*current;

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

bool	parse_material(char *line, t_world *world)
{
	t_material	material;
	char		**split;

	split = ft_split(line, ' ');
	if (!validate_count(split, 5)
		|| !validade_if_already_exists(split[1], world)
		|| !parse_double(split[2], &material.reflective)
		|| !validate_double_range(split[2], material.reflective, 0, 1)
		|| !parse_double(split[3], &material.transparency)
		|| !validate_double_range(split[3], material.transparency, 0, 1)
		|| !parse_double(split[4], &material.refractive_index)
		|| !validate_double_range(split[4], material.refractive_index, 1, INFINITY))
	{
		ft_free_split(split);
		return (false);
	}
	add_material(&world->scene.material_list, material, split[1]);
	ft_free_split(split);
	return (true);
}


t_material_list	*find_material(char *name, t_world *world)
{
	t_material_list	*current;

	current = world->scene.material_list;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(current->name)) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

bool	parse_material_name(char *str, t_material *material, t_world *world)
{
	t_material_list	*find;

	if (!str)
		return (true);
	find = find_material(str, world);
	if (!find)
	{
		// ARRUMAR AQUI
		printf("Material not found: %s\n", str);
		return (false);
	}
	material->reflective = find->material.reflective;
	material->transparency = find->material.transparency;
	material->refractive_index = find->material.refractive_index;
	return (true);
}
