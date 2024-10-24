#include "minirt.h"

bool	parse_ambient(char *line, t_world *world)
{
	double	ambient_ratio;
	t_color	ambient_color;
	char	**splitted;

	splitted = ft_split(line, ' ');
	if (!validate_count(splitted, 3)
		|| !parse_double(splitted[1], &ambient_ratio)
		|| !parse_color(splitted[2], &ambient_color))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	world->ambient_ratio = ambient_ratio;
	world->ambient_color = ambient_color;
	return (true);
}
