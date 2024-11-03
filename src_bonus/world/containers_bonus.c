/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   containers_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:42:05 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:50:01 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene_bonus.h"

int	has_shape(t_shape *containers, t_shape shape)
{
	t_shape	*aux;

	aux = containers;
	while (aux)
	{
		if (is_same_object(*aux, shape))
			return (1);
		aux = aux->next;
	}
	return (0);
}

void	add_shape_to_container(t_shape **containers, t_shape shape)
{
	t_shape	*aux;
	t_shape	*new_shape;

	aux = *containers;
	new_shape = malloc(sizeof(t_shape));
	*new_shape = shape;
	new_shape->next = NULL;
	if (aux)
	{
		while (aux->next)
			aux = aux->next;
		aux->next = new_shape;
	}
	else
		*containers = new_shape;
}

void	remove_shape_from_container(t_shape **containers, t_shape shape)
{
	t_shape	*aux;
	t_shape	*prev;

	aux = *containers;
	prev = NULL;
	while (aux)
	{
		if (is_same_object(*aux, shape))
		{
			if (prev)
				prev->next = aux->next;
			else
				*containers = aux->next;
			free(aux);
			break ;
		}
		prev = aux;
		aux = aux->next;
	}
}

void	update_containers(t_shape **containers, t_shape object)
{
	if (has_shape(*containers, object))
		remove_shape_from_container(containers, object);
	else
		add_shape_to_container(containers, object);
}
