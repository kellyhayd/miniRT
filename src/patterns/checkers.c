#include "minirt.h"

t_pattern	checkers_pattern(t_color color_a, t_color color_b)
{
	return ((t_pattern){
		.pattern_type = CHECKERS,
		.has_pattern = true,
		.color_a = color_a,
		.color_b = color_b,
		.transform = identity(),
		.inverse = identity()
	});
}

t_color	checkers_at(t_pattern pattern, t_point pattern_point)
{
	int		sum_of_coordinates;
	t_color	new_color;

	sum_of_coordinates =
		(int)(pattern_point.x) +
		(int)(pattern_point.y) +
		(int)(pattern_point.z);
	if (sum_of_coordinates % 2 == 0)
		new_color = pattern.color_a;
	else
		new_color = pattern.color_b;
	return (new_color);
}
