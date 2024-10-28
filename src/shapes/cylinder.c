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

void	calculate_cylinder_intersections(t_intersect_cone *inter_cyl)
{
	inter_cyl->disc = sqrt(inter_cyl->disc);
	inter_cyl->hits[0] = intersection((-inter_cyl->disc_b - inter_cyl->disc)
			/ (2.0 * inter_cyl->disc_a), inter_cyl->s);
	inter_cyl->hits[1] = intersection((-inter_cyl->disc_b + inter_cyl->disc)
			/ (2.0 * inter_cyl->disc_a), inter_cyl->s);
	if (inter_cyl->hits[0].t > inter_cyl->hits[1].t)
		swap(&inter_cyl->hits[0].t, &inter_cyl->hits[1].t);
	inter_cyl->y[0] = inter_cyl->r.origin.y
		+ inter_cyl->hits[0].t * inter_cyl->r.direction.y;
	inter_cyl->y[1] = inter_cyl->r.origin.y
		+ inter_cyl->hits[1].t * inter_cyl->r.direction.y;
	if (inter_cyl->s.cylinder_shape.minimum < inter_cyl->y[0]
		&& inter_cyl->y[0] < inter_cyl->s.cylinder_shape.maximum)
		add_intersection(inter_cyl->hit_list, inter_cyl->hits[0]);
	if (inter_cyl->s.cylinder_shape.minimum < inter_cyl->y[1]
		&& inter_cyl->y[1] < inter_cyl->s.cylinder_shape.maximum)
		add_intersection(inter_cyl->hit_list, inter_cyl->hits[1]);
}

void	intersect_cylinder(t_hit **hit_list, t_shape s, t_ray r)
{
	t_intersect_cone	inter_cyl;

	inter_cyl.hit_list = hit_list;
	inter_cyl.s = s;
	inter_cyl.r = r;
	intersect_caps(hit_list, s, r);
	inter_cyl.disc_a = pow(r.direction.x, 2) + pow(r.direction.z, 2);
	if (almost_zero(inter_cyl.disc_a))
		return ;
	inter_cyl.disc_b = (2 * r.origin.x * r.direction.x)
		+ (2 * r.origin.z * r.direction.z);
	inter_cyl.disc_c = pow(r.origin.x, 2) + pow(r.origin.z, 2) - 1.0;
	inter_cyl.disc = pow(inter_cyl.disc_b, 2)
		- 4.0 * inter_cyl.disc_a * inter_cyl.disc_c;
	if (inter_cyl.disc < 0)
		return ;
	calculate_cylinder_intersections(&inter_cyl);
}

t_vector	normal_at_cylinder(t_shape s, t_point obj_point)
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
