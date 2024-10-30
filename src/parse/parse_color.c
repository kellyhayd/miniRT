/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_color.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:33:02 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/29 21:33:03 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	validate_color_range(char *str, int *num)
{
	if (!(*num >= 0 && *num <= 255))
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putstr_fd("Expected " GREEN "value between 0 and 255" RESET
			", received " GREEN, 2);
		ft_putstr_fd(str, 2);
		ft_putendl_fd(RESET, 2);
		return (false);
	}
	return (true);
}

bool	parse_int_color(char *str, int *num)
{
	if (!parse_int(str, num)
		|| !validate_color_range(str, num))
		return (false);
	return (true);
}

/**
 * @brief Parses a color from a string and stores it in a t_color structure.
 *
 * This function takes a string representing a color and parses it into a
 * t_color structure. The string should be in a format that can be correctly
 * interpreted as a color.
 *
 * @param str The string containing the color information to be parsed.
 * @param new_color A pointer to the t_color structure where the parsed color
 *                  will be stored.
 * @return true if the color was successfully parsed and stored, false
 *         otherwise.
 */
bool	parse_color(char *str, t_color *new_color)
{
	int		color_r;
	int		color_g;
	int		color_b;
	char	**splitted;

	splitted = ft_split(str, ',');
	if (!validate_count(splitted, 3)
		|| !parse_int_color(splitted[0], &color_r)
		|| !parse_int_color(splitted[1], &color_g)
		|| !parse_int_color(splitted[2], &color_b))
	{
		ft_free_split(splitted);
		return (false);
	}
	ft_free_split(splitted);
	new_color->r = color_r;
	new_color->g = color_g;
	new_color->b = color_b;
	*new_color = convert_color(*new_color);
	return (true);
}
