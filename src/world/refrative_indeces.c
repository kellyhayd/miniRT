#include "minirt.h"

t_shape	get_last_shape(t_shape *shape_list)
{
	t_shape	*aux;

	aux = shape_list;
	// if (!aux)
	// 	return ((t_shape) {0});
	while (aux && aux->next)
		aux = aux->next;
	return (*aux);
}

int	is_same_object(t_shape shape1, t_shape shape2)
{
	return (shape1.id == shape2.id);
}

int	is_same_hit(t_hit *hit_list, t_hit hit)
{
	return (float_compare(hit_list->t, hit.t)
		&& is_same_object(hit_list->object, hit.object));
}

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

void	calculate_refractive_indexes(t_comps *comps, t_hit *hit_list)
{
	t_hit	*aux_hit;
	t_shape	*containers;

	aux_hit = hit_list;
	containers = NULL;
	while (aux_hit)
	{
		if (is_same_hit(aux_hit, intersection(comps->t, comps->object)))
		{
			if (!containers)
				comps->n1 = 1.0;
			else
				comps->n1 = get_last_shape(containers).material.refractive_index;
			// comps->n1 = fternary(!containers,
			// 	1.0, get_last_shape(containers).material.refractive_index);
		}
		update_containers(&containers, aux_hit->object);
		// if (has_shape(containers, comps->object))
		// 	remove_shape_from_container(&containers, comps->object);
		// else
		// 	add_shape_to_container(&containers, comps->object);
		if (is_same_hit(aux_hit, intersection(comps->t, comps->object)))
		{
			if (!containers)
				comps->n2 = 1.0;
			else
				comps->n2 = get_last_shape(containers).material.refractive_index;
			// comps->n2 = fternary(!containers,
			// 	1.0, get_last_shape(containers).material.refractive_index);
			break ;
		}
		aux_hit = aux_hit->next;
	}
	shape_clear_list(&containers);
}
