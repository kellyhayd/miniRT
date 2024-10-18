#include "minirt.h"

t_hit	*hit_list_copy(t_hit *hit_list)
{
	t_hit	*copy;
	t_hit	*aux;

	copy = NULL;
	aux = hit_list;
	while (aux)
	{
		add_intersection(&copy, intersection(aux->t, aux->object));
		aux = aux->next;
	}
	return (copy);
}

t_comps	prepare_computations(t_hit hit, t_ray ray, t_hit *hit_list)
{
	t_comps	comps;

	comps.t = hit.t;
	comps.object = hit.object;
	comps.point = position(ray, comps.t);
	comps.inside = false;
	comps.sight.eye = tuple_negate(ray.direction);
	comps.sight.normal = normal_at(comps.object, comps.point);
	comps.sight.in_shadow = false;
	if (dot(comps.sight.normal, comps.sight.eye) < 0)
	{
		comps.inside = true;
		comps.sight.normal = tuple_negate(comps.sight.normal);
	}
	comps.reflectv = reflect(ray.direction, comps.sight.normal);
	comps.over_point = tuple_add(comps.point,
			tuple_multiply(comps.sight.normal, EPSILON));
	comps.under_point = tuple_subtract(comps.point,
			tuple_multiply(comps.sight.normal, EPSILON));
	calculate_refractive_indexes(&comps, hit_list);

	return (comps);
}
