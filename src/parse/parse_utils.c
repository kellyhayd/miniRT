/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:03:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/19 10:56:42 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Checks if all strings in the given array are composed entirely of
 * digits.
 *
 * This function iterates through each string in the provided array and
 * verifies whether each string consists solely of numeric characters (0-9).
 * It returns true if all strings are numeric, and false otherwise.
 *
 * @param split An array of strings to be checked.
 * @return true if all strings in the array are numeric, false otherwise.
 */
bool	is_all_numbers(char **split)
{
	int	i;
	int	j;
	int	dot_count;

	i = 0;
	dot_count = 0;
	while (split[i])
	{
		j = 0;
		if (split[i][j] == '-')
			j++;
		while (split[i][j] != '\0' && split[i][j] != '\n')
		{
			if (!ft_isdigit(split[i][j]) && split[i][j] != '.')
				return (false);
			if (split[i][j] == '.')
				dot_count++;
			j++;
		}
		i++;
	}
	if (dot_count > 1)
		return (false);
	return (true);
}

/**
 * @brief Validates the number of elements in a split string array.
 *
 * This function checks if the number of elements in the provided split
 * string array matches the expected count.
 *
 * @param split A pointer to an array of strings (char **), typically the
 *              result of splitting a string.
 * @param count The expected number of elements in the split array.
 * @return true if the number of elements matches the expected count, false
 *         otherwise.
 */
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

/**
 * @brief Validates if all elements in the given array of strings represent
 *        valid color values.
 *
 * This function checks if each string in the provided array represents a
 * valid color value. A valid color value is an integer between 0 and 255.
 *
 * @param str An array of strings to be checked.
 * @return true if all strings represent valid color values, false otherwise.
 */
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

bool	validate_normal_range(char **str)
{
	int	i;

	i = 0;

	// Aqui é pra validar se o vetor normal está normalizado
	// Juntar os 3 (em um vetor x, y e z) e ver se a magnitude é 1

	// OBS: acabei não usado, fiz a parse_direction pra isso

	while (str[i])
	{
		if (ft_atof(str[i]) < -1 || ft_atof(str[i]) > 1)
			return (false);
		i++;
	}
	return (true);
}

bool	parse_double(char *str, double *value)
{
	int	i;

	i = 0;
	if (str[i] == '-')
		i++;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] == '.' && ft_isdigit(str[i + 1]))
		i++;
	else if (str[i] && !ft_isdigit(str[i]))
		return (false);
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (false);
	*value = ft_atof(str);
	return (true);
}

bool	parse_radius(char *str, double *radius)
{
	if (!parse_double(str, radius)
		|| !(*radius > 0))
		return (false);
	return (true);
}

bool	parse_int(char *str, int *num)
{
	int	i;

	i = 0;
	while (str[i] && ft_isdigit(str[i]))
		i++;
	if (str[i] != '\0')
		return (false);
	*num = ft_atoi(str);
	return (true);
}

bool	parse_int_color(char *str, int *num)
{
	if (!parse_int(str, num)
		|| !(*num >= 0 && *num <= 255))
		return (false);
	return (true);
}
