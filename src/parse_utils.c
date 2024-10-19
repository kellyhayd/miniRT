/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:03:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/19 10:03:58 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	is_all_numbers(char **split)
{
	int	i;
	int	j;

	i = 0;
	while (split[i])
	{
		j = 0;
		if (split[i][j] == '-')
			j++;
		while (split[i][j] != '\0' && split[i][j] != '\n')
		{
			if (!ft_isdigit(split[i][j]) && split[i][j] != '.')
				return (false);
			j++;
		}
		i++;
	}
	return (true);
}

bool	validate_count(char **split, int count)
{
	int	i;

	i = 0;
	while (split[i])
		i++;
	if (i != count)
		return (false);
	return (true);
}

bool	validate_color_range(char **str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (ft_atoi(str[i]) < 0 || ft_atoi(str[i]) > 255)
			return (false);
		i++;
	}
	return (true);
}
