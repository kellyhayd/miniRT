/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ray_bonus.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 08:18:24 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:51:46 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RAY_BONUS_H
# define RAY_BONUS_H

# include "shapes_bonus.h"

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_hit
{
	double			t;
	t_shape			object;
	struct s_hit	*next;
}	t_hit;

typedef struct s_intersect_cone
{
	double	disc_a;
	double	disc_b;
	double	disc_c;
	double	disc;
	double	y[2];
	t_hit	hits[2];
	t_hit	**hit_list;
	t_shape	s;
	t_ray	r;
}	t_intersect_cone;

// -------------------------------------------------------------------------- //
//                                    ray                                     //
// -------------------------------------------------------------------------- //

t_ray		ray(t_point origin, t_vector direction);
t_point		position(t_ray r, double t);
t_ray		ray_transform(t_ray ray, t_matrix matrix);

// -------------------------------------------------------------------------- //
//                                intersection                                //
// -------------------------------------------------------------------------- //

void		intersect(t_hit **hit_list, t_shape s, t_ray r);
t_hit		intersection(double t, t_shape s);
int			intersection_count(t_hit *hit_list);
void		hit_clear_list(t_hit **hit_list);
void		add_intersection(t_hit **hit_list, t_hit isect);
t_hit		*hit(t_hit *hit_list);
void		local_intersect(t_hit **hit_list, t_shape s, t_ray r);
void		intersect_sphere(t_hit **hit_list, t_shape s, t_ray r);
void		intersect_plane(t_hit **hit_list, t_shape s, t_ray r);
void		intersect_cylinder(t_hit **hit_list, t_shape s, t_ray r);
void		intersect_cone(t_hit **hit_list, t_shape s, t_ray r);

#endif
