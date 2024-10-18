#include "minirt.h"

t_color	refracted_color(t_world w, t_comps comps, int depth)
{
	double	n_ratio;
	double	cos_i;
	double	sin2_t;
	t_color	ref_color;

	(void) w;
	n_ratio = comps.n1 / comps.n2;
	cos_i = dot(comps.sight.eye, comps.sight.normal);
	sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));
	if (comps.object.material.transparency == 0 || depth == 0 || sin2_t > 1)
		ref_color = color(0, 0, 0);
	else
		ref_color = color(1, 1, 1);
	return (ref_color);
}
