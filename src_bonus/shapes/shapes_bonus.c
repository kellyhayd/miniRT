/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes_bonus.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 08:41:23 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:54:53 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt_bonus.h"
#include "shapes_bonus.h"
#include "ray_bonus.h"

t_shape	new_shape(void)
{
	static int	shape_id;
	t_shape		shape;

	shape.id = shape_id++;
	shape.transform = identity();
	shape.inverse = identity();
	shape.transposed_inverse = identity();
	shape.material = material();
	shape.next = NULL;
	return (shape);
}

void	add_shape(t_shape **shape_list, t_shape shape_to_add)
{
	t_shape	*new_shape;
	t_shape	*aux;

	new_shape = malloc(sizeof(t_shape));
	if (!new_shape)
		ft_error("Failed to allocate memory for new shape.");
	*new_shape = shape_to_add;
	aux = *shape_list;
	while (aux && aux->next)
		aux = aux->next;
	if (aux)
		aux->next = new_shape;
	else
		*shape_list = new_shape;
}

void	shape_clear_list(t_shape **shape_list)
{
	if (shape_list && *shape_list)
	{
		shape_clear_list(&((*shape_list)->next));
		free(*shape_list);
		*shape_list = NULL;
	}
}
