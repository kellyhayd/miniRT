/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_validations_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:25:08 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 17:01:32 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser_bonus.h"

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
	while (split && split[i])
		i++;
	if (i != count)
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putendl_fd("Invalid number of elements", 2);
		return (false);
	}
	return (true);
}

bool	validade_optionals(char **splitted)
{
	if (splitted[0] && splitted[1] && splitted[2])
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putendl_fd("Invalid number of elements", 2);
		return (false);
	}
	return (true);
}

bool	pos_validation(t_world *world, int state)
{
	if (!state)
		return (false);
	if (!world->scene.has_ambient_color)
		state = print_error("There must be 1 ambient color");
	if (!world->scene.has_camera)
		state = print_error("There must be 1 camera");
	if (!world->light)
		state = print_error("There must be 1 light");
	if (!world->shape)
		state = print_error("There must be at least 1 object in the scene");
	return (state);
}
