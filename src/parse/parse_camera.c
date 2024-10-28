#include "minirt.h"

bool	validade_if_has_camera(t_world *world)
{
	if (!(world->scene.has_camera == 0))
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putendl_fd("Only one camera allowed", 2);
		return (false);
	}
	return (true);
}

bool	parser_fov_range(char *str, int *fov)
{
	if (!(*fov >= 0 && *fov <= 180))
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putstr_fd("Expected " GREEN "value between 0 and 180" RESET
			", received " GREEN, 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(RESET, 2);
		return (false);
	}
	return (true);
}

bool	parse_camera(char *line, t_world *world)
{
	int			fov;
	t_point		position;
	t_vector	direction;
	t_camera	new_camera;
	char		**splitted;

	splitted = ft_split(line, ' ');
	if (!validate_count(splitted, 4) \
		|| !validade_if_has_camera(world) \
		|| !parse_coordinates(splitted[1], &position) \
		|| !parse_direction(splitted[2], &direction) \
		|| !parse_int(splitted[3], &fov)
		|| !parser_fov_range(splitted[3], &fov))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	world->scene.has_camera = 1;
	new_camera = camera(WIDTH, HEIGH, (fov * M_PI) / 180);
	new_camera.transform = view_transform(position, \
		tuple_add(position, direction), vector(0, 1, 0));
	new_camera.inverse = inverse(new_camera.transform);
	world->scene.world_camera = new_camera;
	return (true);
}
