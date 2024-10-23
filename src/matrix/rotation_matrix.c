#include "minirt.h"

static void	calculate_rotation_angles(t_vector vec, double *x, double *z)
{
	double	ratio;

	ratio = sqrt((vec.x * vec.x) + (vec.y * vec.y));
	if (0.0 == ratio)
		*z = M_PI_2;
	else
		*z = acos(vec.y / ratio);
	*x = acos(ratio);
}

t_matrix	rotation_matrix(t_vector direction)
{
	double		x_angle;
	double		z_angle;
	t_matrix	rotate_z;
	t_matrix	rotate_x;
	t_matrix	full_rotation;

	calculate_rotation_angles(direction, &x_angle, &z_angle);
	rotate_z = rotation_z(z_angle);
	rotate_x = rotation_x(x_angle);
	full_rotation = mx_multiply(rotate_z, rotate_x);
	return (full_rotation);
}
