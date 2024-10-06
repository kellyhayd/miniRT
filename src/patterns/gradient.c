#include "minirt.h"

t_pattern	gradient_pattern(t_color color_a, t_color color_b)
{
	return ((t_pattern){
		.pattern_type = GRADIENT,
		.has_pattern = true,
		.color_a = color_a,
		.color_b = color_b,
		.transform = identity(),
		.inverse = identity()
	});
}

t_color	gradient_at(t_pattern pattern, t_point pattern_point)
{
	double	fraction;
	t_color	distance;
	t_color	new_color;

	distance = color_subtract(pattern.color_b, pattern.color_a);
	if (fmod(fabs(pattern_point.x), 2) >= 1)
		fraction = 1 - fmod(fabs(pattern_point.x), 1);
	else
		fraction = fmod(fabs(pattern_point.x), 1);
	new_color = color_add(color_multiply(distance, fraction), pattern.color_a);
	return (new_color);
}
