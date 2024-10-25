#include "minirt.h"

bool	print_error_double(char *str)
{
	ft_putendl_fd(RED "Error!" RESET, 2);
	ft_putstr_fd("Expected " GREEN "double" RESET ", received " GREEN, 2);
	ft_putstr_fd(str, 2);
	ft_putendl_fd(RESET, 2);
	return (false);
}

bool	parse_double(char *str, double *value)
{
	int	i;

	i = 0;
	if (str[i] == '.')
		return (print_error_double(str));
	if (str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '.' && ft_isdigit(str[i + 1]))
		i++;
	else if (str[i] && !ft_isdigit(str[i]))
		return (print_error_double(str));
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (print_error_double(str));
	*value = ft_atof(str);
	return (true);
}

bool	parse_radius_range(char *str, double *radius)
{
	if (!(*radius > 0))
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putstr_fd("Expected " GREEN "value above 0" RESET
			", received " GREEN, 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(RESET, 2);
		return (false);
	}
	return (true);
}

bool	parse_radius(char *str, double *radius)
{
	if (!parse_double(str, radius)
		|| !parse_radius_range(str, radius))
		return (false);
	return (true);
}
