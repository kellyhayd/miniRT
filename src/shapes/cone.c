/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cone.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/05 08:48:56 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/05 08:50:26 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_shape	cone(void)
{
	t_shape	new_cone;

	new_cone = new_shape();
	new_cone.shape_type = CONE;
	new_cone.cone_shape.origin = point(0, 0, 0);
	new_cone.cone_shape.radius = 1;
	new_cone.cone_shape.minimum = -INFINITY;
	new_cone.cone_shape.maximum = INFINITY;
	new_cone.cone_shape.closed = false;
	return (new_cone);
}

static int	check_cap(t_ray r, double t, double cap_y_pos)
{
	double	x;
	double	z;

	x = r.origin.x + t * r.direction.x;
	z = r.origin.z + t * r.direction.z;
	return (pow(x, 2) + pow(z, 2) <= pow(cap_y_pos, 2));
}

static void	intersect_caps(t_hit **hit_list, t_shape s, t_ray r)
{
	double	t;

	if (s.cone_shape.closed == false || almost_zero(r.direction.y))
		return ;
	t = (s.cone_shape.minimum - r.origin.y) / r.direction.y;
	if (check_cap(r, t, s.cone_shape.minimum))
		add_intersection(hit_list, intersection(t, s));
	t = (s.cone_shape.maximum - r.origin.y) / r.direction.y;
	if (check_cap(r, t, s.cone_shape.maximum))
		add_intersection(hit_list, intersection(t, s));
}

void	calculate_cone_discriminats(t_intersect_cone *inter_cone)
{
	inter_cone->disc_a = pow(inter_cone->r.direction.x, 2)
		- pow(inter_cone->r.direction.y, 2) + pow(inter_cone->r.direction.z, 2);
	inter_cone->disc_b = (2 * inter_cone->r.origin.x
			* inter_cone->r.direction.x)
		- (2 * inter_cone->r.origin.y * inter_cone->r.direction.y)
		+ (2 * inter_cone->r.origin.z * inter_cone->r.direction.z);
	inter_cone->disc_c = pow(inter_cone->r.origin.x, 2)
		- pow(inter_cone->r.origin.y, 2) + pow(inter_cone->r.origin.z, 2);
}

void	calculate_cone_intersections(t_intersect_cone *inter_cone)
{
	inter_cone->disc = sqrt(inter_cone->disc);
	inter_cone->hits[0] = intersection((-inter_cone->disc_b - inter_cone->disc)
			/ (2.0 * inter_cone->disc_a), inter_cone->s);
	inter_cone->hits[1] = intersection((-inter_cone->disc_b + inter_cone->disc)
			/ (2.0 * inter_cone->disc_a), inter_cone->s);
	if (inter_cone->hits[0].t > inter_cone->hits[1].t)
		swap(&inter_cone->hits[0].t, &inter_cone->hits[1].t);
	inter_cone->y[0] = inter_cone->r.origin.y + inter_cone->hits[0].t
		* inter_cone->r.direction.y;
	inter_cone->y[1] = inter_cone->r.origin.y + inter_cone->hits[1].t
		* inter_cone->r.direction.y;
	if (inter_cone->s.cylinder_shape.minimum < inter_cone->y[0]
		&& inter_cone->y[0] < inter_cone->s.cylinder_shape.maximum)
		add_intersection(inter_cone->hit_list, inter_cone->hits[0]);
	if (inter_cone->s.cylinder_shape.minimum < inter_cone->y[1]
		&& inter_cone->y[1] < inter_cone->s.cylinder_shape.maximum)
		add_intersection(inter_cone->hit_list, inter_cone->hits[1]);
}

void	intersect_cone(t_hit **hit_list, t_shape s, t_ray r)
{
	t_intersect_cone	inter_cone;

	inter_cone.hit_list = hit_list;
	inter_cone.s = s;
	inter_cone.r = r;
	intersect_caps(hit_list, s, r);
	calculate_cone_discriminats(&inter_cone);
	if (almost_zero(inter_cone.disc_a))
	{
		if (almost_zero(inter_cone.disc_b))
			return ;
		add_intersection(hit_list, intersection(-inter_cone.disc_c
				/ (2 * inter_cone.disc_b), s));
		return ;
	}
	inter_cone.disc = pow(inter_cone.disc_b, 2)
		- 4.0 * inter_cone.disc_a * inter_cone.disc_c;
	if (inter_cone.disc < 0)
		return ;
	calculate_cone_intersections(&inter_cone);
}

t_vector	normal_at_cone(t_shape s, t_point obj_point)
{
	double		y;
	double		dist;
	double		max_radius;
	double		min_radius;
	t_vector	normal;

	dist = pow(obj_point.x, 2) + pow(obj_point.z, 2);
	max_radius = pow(s.cone_shape.maximum, 2);
	min_radius = pow(s.cone_shape.minimum, 2);
	if (dist < max_radius
		&& obj_point.y >= s.cylinder_shape.maximum - EPSILON)
		normal = vector(0, 1, 0);
	else if (dist < min_radius
		&& obj_point.y <= s.cylinder_shape.minimum + EPSILON)
		normal = vector(0, -1, 0);
	else
	{
		y = sqrt(dist);
		if (obj_point.y > 0)
			y = -y;
		normal = vector(obj_point.x, y, obj_point.z);
	}
	return (normal);
}
