/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_double_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:33:14 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:50:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

bool	print_error_double(char *str)
{
	ft_putendl_fd(RED "Error!" RESET, 2);
	ft_putstr_fd("Expected " GREEN "double" RESET ", received " GREEN, 2);
	if (str)
		ft_putstr_fd(str, 2);
	else
		ft_putstr_fd("NULL", 2);
	ft_putendl_fd(RESET, 2);
	return (false);
}

bool	parse_double(char *str, double *value)
{
	int	i;

	i = 0;
	if (!str)
		return (print_error_double(str));
	if (str[i] == '.')
		return (print_error_double(str));
	if (str[i] == '-' && ft_isdigit(str[i + 1]))
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

bool	validate_double_range(char *str, double value, double min, double max)
{
	if (!(value >= min && value <= max))
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putstr_fd("Expected " GREEN "value between ", 2);
		ft_putnbr_fd(min, 2);
		ft_putstr_fd(" and ", 2);
		if (max == INFINITY)
			ft_putstr_fd("INFINITY", 2);
		else
			ft_putnbr_fd(max, 2);
		ft_putstr_fd(RESET ", received " GREEN, 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(RESET, 2);
		return (false);
	}
	return (true);
}
