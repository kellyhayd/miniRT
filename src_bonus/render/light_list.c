/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light_list.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 22:18:12 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/30 18:36:05 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "scene.h"

void	add_light(t_light **light_list, t_light light_to_add)
{
	t_light	*new_light;
	t_light	*aux;

	new_light = malloc(sizeof(t_light));
	if (!new_light)
		ft_error("Failed to allocate memory for new light.");
	*new_light = light_to_add;
	aux = *light_list;
	while (aux && aux->next)
		aux = aux->next;
	if (aux)
		aux->next = new_light;
	else
		*light_list = new_light;
}

void	light_clear_list(t_light **light_list)
{
	if (light_list && *light_list)
	{
		light_clear_list(&((*light_list)->next));
		free(*light_list);
		*light_list = NULL;
	}
}
