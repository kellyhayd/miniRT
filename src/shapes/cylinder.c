/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cylinder.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 08:50:59 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/20 18:22:58 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	cylinder(void)
{
	t_shape	new_cylinder;

	new_cylinder = new_shape();
	new_cylinder.shape_type = CYLINDER;
	new_cylinder.cylinder_shape.origin = point(0, 0, 0);
	new_cylinder.cylinder_shape.radius = 1;
	new_cylinder.cylinder_shape.closed = false;
	new_cylinder.cylinder_shape.minimum = -INFINITY;
	new_cylinder.cylinder_shape.maximum = INFINITY;
	return (new_cylinder);
}

static int	check_cap(t_ray r, double t)
{
	double	x;
	double	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return (pow(x, 2) + pow(z, 2) <= 1);
}

static void	intersect_caps(t_hit **hit_list, t_shape s, t_ray r)
{
	double	t;

	if (s.cylinder_shape.closed == false || almost_zero(r.direction.y))
		return ;
	t = (s.cylinder_shape.minimum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
		add_intersection(hit_list, intersection(t, s));
	t = (s.cylinder_shape.maximum - r.origin.y) / r.direction.y;
	if (check_cap(r, t))
		add_intersection(hit_list, intersection(t, s));
}

void	intersect_cylinder(t_hit **hit_list, t_shape s, t_ray r)
{
	double	a;
	double	b;
	double	c;
	double	disc;
	double	y[2];
	t_hit	hits[2];

	intersect_caps(hit_list, s, r);
	a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	if (almost_zero(a))
		return ;
	b = (2 * r.origin.x * r.direction.x) + (2 * r.origin.z * r.direction.z);
	c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - 1.0;
	disc = pow(b, 2) - 4.0 * a * c;
	if (disc < 0)
		return ;
	disc = sqrt(disc);		// Otimização:
							//	Pra não fazer o mesmo cálculo de sqrt 2 vezes
							//	coloquei na mesma variável para não precisar criar mais uma
	hits[0] = intersection((-b - disc) / (2.0 * a), s);
	hits[1] = intersection((-b + disc) / (2.0 * a), s);
	if (hits[0].t > hits[1].t)
		swap(&hits[0].t, &hits[1].t);
	y[0] = r.origin.y + hits[0].t * r.direction.y;
	y[1] = r.origin.y + hits[1].t * r.direction.y;
	if (s.cylinder_shape.minimum < y[0] && y[0] < s.cylinder_shape.maximum)
		add_intersection(hit_list, hits[0]);
	if (s.cylinder_shape.minimum < y[1] && y[1] < s.cylinder_shape.maximum)
		add_intersection(hit_list, hits[1]);
}

t_vector		normal_at_cylinder(t_shape s, t_point obj_point)
{
	double		dist;
	t_vector	normal;

	dist = pow(obj_point.x, 2) + pow(obj_point.z, 2);
	if (dist < 1 && obj_point.y >= s.cylinder_shape.maximum - EPSILON)
		normal = vector(0, 1, 0);
	else if (dist < 1 && obj_point.y <= s.cylinder_shape.minimum + EPSILON)
		normal = vector(0, -1, 0);
	else
		normal = vector(obj_point.x, 0, obj_point.z);
	return (normal);
}
