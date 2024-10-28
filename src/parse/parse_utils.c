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

void	put_ambient_color(t_world *world)
{
	t_color	ambient_color;
	t_shape	*aux;

	ambient_color = color_multiply(world->scene.ambient_color,
		world->scene.ambient_ratio);
	aux = world->shape;
	while (aux)
	{
		aux->material.ambient = color_hadamard(ambient_color,
			aux->material.color);
		aux = aux->next;
	}
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

bool	print_error(char *message)
{
	ft_putendl_fd(RED "Error" RESET, 2);
	ft_putendl_fd(message, 2);
	return (false);
}
