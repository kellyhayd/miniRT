/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refractive_idx.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:49:15 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/29 21:53:06 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	is_same_object(t_shape shape1, t_shape shape2)
{
	return (shape1.id == shape2.id);
}

int	is_same_hit(t_hit *hit_list, t_hit hit)
{
	return (float_compare(hit_list->t, hit.t)
		&& is_same_object(hit_list->object, hit.object));
}

t_shape	get_last_shape(t_shape *shape_list)
{
	t_shape	*aux;

	aux = shape_list;
	while (aux && aux->next)
		aux = aux->next;
	return (*aux);
}

double	get_n1_refract(t_shape *containers)
{
	double	refract;

	if (!containers)
		refract = 1.0;
	else
		refract = get_last_shape(containers).material.refractive_index;
	return (refract);
}

void	calculate_refractive_indexes(t_comps *comps, t_hit *hit_list)
{
	t_hit	*aux_hit;
	t_shape	*cnt;

	aux_hit = hit_list;
	cnt = NULL;
	while (aux_hit)
	{
		if (is_same_hit(aux_hit, intersection(comps->t, comps->object)))
			comps->n1 = get_n1_refract(cnt);
		update_containers(&cnt, aux_hit->object);
		if (is_same_hit(aux_hit, intersection(comps->t, comps->object)))
		{
			if (!cnt)
				comps->n2 = 1.0;
			else
				comps->n2 = get_last_shape(cnt).material.refractive_index;
			break ;
		}
		aux_hit = aux_hit->next;
	}
	shape_clear_list(&cnt);
}
