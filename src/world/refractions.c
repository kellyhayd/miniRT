#include "minirt.h"

t_color	refracted_color(t_world w, t_comps comps, int depth)
{
	t_color	ref_color;

	(void) w;
	if (comps.object.material.transparency == 0 || depth == 0)
		ref_color = color(0, 0, 0);
	else
		ref_color = color(1, 1, 1);
	return (ref_color);
}
