#include "minirt.h"

bool	check_if_material_exists(char *name, t_world *world)
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
		|| !check_if_material_exists(split[1], world)
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

static	t_material_list	*find_material(char *name, t_world *world)
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

bool	parse_material_shape(char **splitted, t_material *material, t_world *world)
{
	bool	status;

	status = true;
	if (splitted[0])
		status = parse_material_name(splitted[0], material, world);
	if (status && splitted[0] && splitted[1])
		status = parse_pattern_name(splitted[1], &material->pattern, world);
	return (status);
}
