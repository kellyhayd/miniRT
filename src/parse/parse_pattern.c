#include "minirt.h"

bool	check_if_pattern_exists(char *name, t_world *world)
{
	t_pattern_list	*current;

	current = world->scene.pattern_list;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(current->name)) == 0)
		{
			// ARRUMAR AQUI
			printf("Pattern already exists: %s\n", name);
			return (false);
		}
		current = current->next;
	}
	return (true);
}

bool	parse_pattern_type(char *type, t_patterns *pattern_type)
{
	if (ft_strncmp(type, "stripe", -1) == 0)
		*pattern_type = STRIPE;
	else if (ft_strncmp(type, "gradient", -1) == 0)
		*pattern_type = GRADIENT;
	else if (ft_strncmp(type, "ring", -1) == 0)
		*pattern_type = RING;
	else if (ft_strncmp(type, "checkers", -1) == 0)
		*pattern_type = CHECKERS;
	else
		return (false);
	return (true);
}

static t_matrix	get_transformation_pattern(t_point scale_factor,
	t_point rotation_factor, t_point translation_factor)
{
	t_matrix	scale_mx;
	t_matrix	rotation_mx;
	t_matrix	translation_mx;

	scale_mx = scaling(scale_factor.x, scale_factor.y, scale_factor.z);
	rotation_mx = mx_multiply(
			mx_multiply(
				rotation_x((rotation_factor.x * M_PI) / 180),
				rotation_y((rotation_factor.y * M_PI) / 180)),
			rotation_z((rotation_factor.z * M_PI) / 180));
	translation_mx = translation(translation_factor.x,
			translation_factor.y,
			translation_factor.z);
	return (mx_multiply(mx_multiply(scale_mx, rotation_mx), translation_mx));
}

void	add_pattern(t_pattern_list **pattern_list,
	t_pattern pattern, char *name)
{
	t_pattern_list	*last;
	t_pattern_list	*new_pattern;

	new_pattern = malloc(sizeof(t_pattern_list));
	new_pattern->name = ft_strdup(name);
	new_pattern->pattern = pattern;
	new_pattern->next = NULL;
	if (*pattern_list == NULL)
		*pattern_list = new_pattern;
	else
	{
		last = *pattern_list;
		while (last->next)
			last = last->next;
		last->next = new_pattern;
	}
}

bool	parse_pattern(char *line, t_world *world)
{
	t_point		scale_factor;
	t_point		rotation_factor;
	t_point		translation_factor;
	t_pattern	pattern;
	char		**split;

	split = ft_split(line, ' ');
	if (!check_if_pattern_exists(split[1], world)
		|| !parse_pattern_type(split[2], &pattern.pattern_type)
		|| !parse_color(split[3], &pattern.color_a)
		|| !parse_color(split[4], &pattern.color_b)
		|| !parse_coordinates(split[5], &scale_factor)
		|| !parse_coordinates(split[6], &rotation_factor)
		|| !parse_coordinates(split[7], &translation_factor)
		|| (split[8]))
		return (ft_free_split(split), false);
	if (pattern.pattern_type == CHECKERS)
		pattern.map = texture_map(uv_checkers(16, 8,
					pattern.color_a, pattern.color_b), spherical_map);
	pattern.has_pattern = true;
	pattern.transform = get_transformation_pattern(scale_factor,
			rotation_factor, translation_factor);
	pattern.inverse = inverse(pattern.transform);
	add_pattern(&world->scene.pattern_list, pattern, split[1]);
	return (ft_free_split(split), true);
}

void	clear_pattern_list(t_world *world)
{
	t_pattern_list	*current;
	t_pattern_list	*next;

	current = world->scene.pattern_list;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current);
		current = next;
	}
	world->scene.pattern_list = NULL;
}

t_pattern_list	*find_pattern(char *name, t_world *world)
{
	t_pattern_list	*current;

	current = world->scene.pattern_list;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(current->name)) == 0)
			return (current);
		current = current->next;
	}
	return (NULL);
}

bool	parse_pattern_name(char *str, t_pattern *pattern, t_world *world)
{
	t_pattern_list	*find;

	if (!str)
		return (true);
	find = find_pattern(str, world);
	if (!find)
	{
		// ARRUMAR AQUI
		printf("Pattern not found: %s\n", str);
		return (false);
	}
	*pattern = find->pattern;
	return (true);
}
