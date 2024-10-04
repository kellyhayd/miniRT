#include "minirt.h"

t_pattern stripe_pattern(t_color color_a, t_color color_b)
{
	return ((t_pattern){
		.has_pattern = true,
		.color_a = color_a,
		.color_b = color_b,
	});
}

/**
 * @brief Determines the color at a given point in a stripe pattern.
 *
 * This function calculates the color at a specific point in a stripe pattern.
 * It uses the x-coordinate of the point to determine which color to return.
 * If the x-coordinate is an even number, it returns the first color in the
 * pattern. If the x-coordinate is an odd number, it returns the second color.
 *
 * @note The x-coordinate is used to determine the color because the stripe
 * pattern is infinite in the y and z directions.
 *
 * @note fmod was used to calculate the remainder of the division between two
 * doubles because the % operator does not work with doubles.
 *
 * @param pattern The stripe pattern containing the two colors.
 * @param pattern_point The point in the pattern to evaluate.
 * @return The color at the given point in the stripe pattern.
 */
t_color	stripe_at(t_pattern pattern, t_point pattern_point)
{
	t_color	new_color;

	if ((int)floor(pattern_point.x) % 2 == 0)
		new_color = pattern.color_a;
	else
		new_color = pattern.color_b;
	// printf("%f %f\n", pattern_point.x, fmod(pattern_point.x, 2));
	return (new_color);
}
