/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:46:49 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/14 19:49:34 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	add_intersection(t_hit **hit_list, t_hit isect)
{
	t_hit	*new;
	t_hit	*aux;
	t_hit	*prev;

	new = malloc(sizeof(t_hit));
	*new = isect;
	prev = NULL;
	aux = *hit_list;
	while (aux && aux->t < isect.t)
	{
		prev = aux;
		aux = aux->next;
	}
	if (prev == NULL)
	{
		new->next = *hit_list;
		*hit_list = new;
		return ;
	}
	prev->next = new;
	new->next = aux;
}

int	intersection_count(t_hit *hit_list)
{
	int		count;
	t_hit	*aux;

	count = 0;
	aux = hit_list;
	while (aux)
	{
		aux = aux->next;
		count++;
	}
	return (count);
}

void	hit_clear_list(t_hit **hit_list)
{
	if (hit_list && *hit_list)
	{
		hit_clear_list(&((*hit_list)->next));
		free(*hit_list);
		*hit_list = NULL;
	}
}
