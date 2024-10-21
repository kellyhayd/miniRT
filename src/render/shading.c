#include "minirt.h"

t_color	shade_hit(t_world world, t_comps comps, int depth)
{
	t_color	color_shaded;
	t_color	color_reflected;
	t_color	color_refracted;
	t_light	*aux;

	color_shaded = color(0, 0, 0);
	aux = world.light;
	while (aux)
	{
		comps.sight.in_shadow = is_shadowed(world, comps.over_point, aux);
		color_shaded = color_add(
			color_shaded,
			lighting(
				comps.object,
				*aux,
				comps.point,
				comps.sight
			)
		);
		aux = aux->next;
	}
	color_reflected = reflected_color(world, comps, depth);
	color_refracted = refracted_color(world, comps, depth);
	return (color_add(
		color_add(color_shaded, color_reflected), color_refracted));
}

t_color	color_at(t_world w, t_ray r, int depth)
{
	t_color	color_at_hit;
	t_comps	comps;
	t_hit	*nearest_hit;
	t_hit	*hits;

	color_at_hit = color(0, 0, 0);
	hits = intersect_world(w, r);
	nearest_hit = hit(hits);
	if (nearest_hit)
	{
		comps = prepare_computations(*nearest_hit, r, hits);
		color_at_hit = shade_hit(w, comps, depth);
	}
	hit_clear_list(&hits);
	return (color_at_hit);
}
