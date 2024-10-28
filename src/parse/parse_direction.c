#include "minirt.h"

bool	validate_direction_range(char *str, double *value)
{
	if (!(*value >= -1 && *value <= 1))
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putstr_fd("Expected " GREEN "value between -1 and 1" RESET
			", received " GREEN, 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(RESET, 2);
		return (false);
	}
	return (true);
}

bool	parse_direction_part(char *str, double *value)
{
	if (!parse_double(str, value)
		|| !validate_direction_range(str, value))
		return (false);
	return (true);
}

bool	validate_if_direction_is_normalized(char *str, t_vector *direction)
{
	if (almost_zero(magnitude(*direction)))
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putstr_fd("Expected " GREEN "non-zero" RESET
			", received " GREEN, 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(RESET, 2);
		return (false);
	}

	return (true);
}

bool	parse_direction(char *str, t_vector *direction)
{
	char	**splitted;

	splitted = ft_split(str, ',');
	if (!validate_count(splitted, 3)
		|| !parse_direction_part(splitted[0], &direction->x)
		|| !parse_direction_part(splitted[1], &direction->y)
		|| !parse_direction_part(splitted[2], &direction->z)
		|| !validate_if_direction_is_normalized(str, direction)
		)
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	direction->w = 0;
	*direction = normalize(*direction);
	return (true);
}
