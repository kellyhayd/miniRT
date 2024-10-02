#include "minirt.h"

t_shape	cylinder(void)
{
	t_shape	new_cylinder;

	new_cylinder.cylinder_shape.origin = point(0, 0, 0);
	new_cylinder.cylinder_shape.radius = 1;
	new_cylinder.transform = identity();
	new_cylinder.inverse = identity();
	new_cylinder.transposed_inverse = identity();
	new_cylinder.material = material();
	new_cylinder.shape_type = CYLINDER;
	new_cylinder.cylinder_shape.minimum = -INFINITY;
	new_cylinder.cylinder_shape.maximum = INFINITY;
	new_cylinder.next = NULL;
	return (new_cylinder);
}

void	intersect_cylinder(t_hit **hit_list, t_shape s, t_ray r)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	y0;
	double	y1;
	double	tmp;
	t_hit	hit0;
	t_hit	hit1;

	a = pow(r.direction.x, 2) + pow(r.direction.z, 2);

	if (fabs(a) < EPSILON)
		return ;

	b = (2 * r.origin.x * r.direction.x) + (2 * r.origin.z * r.direction.z);
	c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - 1.0;
	disc = pow(b, 2) - 4.0 * a * c;

	if (disc < 0)
		return ;

	disc = sqrt(disc);		// Otimização:
							//	Pra não fazer o mesmo cálculo de sqrt 2 vezes
							//	coloquei na mesma variável para não precisar criar mais uma

	hit0 = intersection((-b - disc) / (2.0 * a), s);
	hit1 = intersection((-b + disc) / (2.0 * a), s);

	if (hit0.t > hit1.t)
	{
		// swap(&hit0.t, &hit1.t);
		tmp = hit0.t;
		hit0.t = hit1.t;
		hit1.t = tmp;
	}

	y0 = r.origin.y + hit0.t * r.direction.y;
	y1 = r.origin.y + hit1.t * r.direction.y;

	if (s.cylinder_shape.minimum < y0 && y0 < s.cylinder_shape.maximum)
		add_intersection(hit_list, hit0);
	if (s.cylinder_shape.minimum < y1 && y1 < s.cylinder_shape.maximum)
		add_intersection(hit_list, hit1);
}

t_vector	normal_at_cylinder(t_shape s, t_point obj_point)
{
	t_vector	normal;

	(void) s;
	normal = vector(obj_point.x, 0, obj_point.z);
	return (normal);
}
