/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   intersect_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/14 19:46:49 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/31 08:53:12 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "scene.h"
#include "ray.h"

/**
 * @brief Adds an intersection to the hit list.
 *
 * This function takes a pointer to a hit list and an intersection, and adds
 * the intersection to the hit list.
 *
 * @param hit_list A pointer to the list of hits (intersections).
 * @param isect The intersection to be added to the hit list.
 */
void	add_intersection(t_hit **hit_list, t_hit isect)
{
	t_hit	*new;
	t_hit	*aux;
	t_hit	*prev;

	new = malloc(sizeof(t_hit));
	if (!new)
		ft_error("Failed to allocate memory for new intersection.");
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

/**
 * @brief Counts the number of intersections in the hit list.
 *
 * This function iterates through the provided hit list and counts the number
 * of intersections present.
 *
 * @param hit_list A pointer to the head of the hit list.
 * @return The number of intersections in the hit list.
 */
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

/**
 * @brief Clears the list of hit records.
 *
 * This function takes a pointer to a list of hit records and clears the list,
 * freeing any allocated memory associated with the hit records.
 *
 * @param hit_list A double pointer to the head of the list of hit records.
 */
void	hit_clear_list(t_hit **hit_list)
{
	if (hit_list && *hit_list)
	{
		hit_clear_list(&((*hit_list)->next));
		free(*hit_list);
		*hit_list = NULL;
	}
}

/**
 * @brief Retrieves the hit at the specified index from the hit list.
 * For tests use only.
 *
 * This function takes a list of hits and an index, and returns the hit
 * located at that index in the list.
 *
 * @param hit_list A pointer to the list of hits.
 * @param index The index of the hit to retrieve.
 * @return A pointer to the hit at the specified index,
 * or NULL if the index is out of bounds.
 */
t_hit	*hit_index(t_hit *hit_list, int index)
{
	int		i;
	t_hit	*aux;

	i = 0;
	aux = hit_list;
	while (aux && i < index)
	{
		aux = aux->next;
		i++;
	}
	return (aux);
}
