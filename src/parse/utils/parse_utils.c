/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/19 10:03:33 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/30 07:35:37 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	put_ambient_color(t_world *world)
{
	t_color	ambient_color;
	t_shape	*aux;

	ambient_color = color_multiply(world->scene.ambient_color,
			world->scene.ambient_ratio);
	aux = world->shape;
	while (aux)
	{
		if (aux->material.pattern.has_pattern)
			aux->material.ambient = color_hadamard(ambient_color,
					aux->material.pattern.color_a);
		else
			aux->material.ambient = color_hadamard(ambient_color,
					aux->material.color);
		aux = aux->next;
	}
}

bool	print_error(char *message)
{
	ft_putendl_fd(RED "Error" RESET, 2);
	ft_putendl_fd(message, 2);
	return (false);
}

void	print_line_error(char *line, int count_line)
{
	ft_putstr_fd(BLUE "Line: " RESET, 2);
	if (count_line < 10)
		ft_putchar_fd('0', 2);
	ft_putnbr_fd(count_line, 2);
	ft_putstr_fd(" | ", 2);
	ft_putendl_fd(line, 2);
	free(line);
}
