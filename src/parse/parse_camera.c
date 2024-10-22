#include "minirt.h"

bool	parse_camera(char *line, t_world *world)
{
	int			fov;
	t_point		position;
	t_vector	direction;
	t_camera	new_camera;
	char		**splitted;

	splitted = ft_split(line, ' ');
	if (!validate_count(splitted, 4) \
		|| !parse_coordinates(splitted[1], &position) \
		|| !parse_direction(splitted[2], &direction) \
		|| !parse_int(splitted[3], &fov))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	new_camera = camera(WIDTH, HEIGH, fov);
	new_camera.transform = view_transform(
		position,
		tuple_add(
			position,
			normalize(direction)
		),
		vector(0, 1, 1)
	);
	new_camera.inverse = inverse(new_camera.transform);
	world->world_camera = new_camera;
	return (true);
}
