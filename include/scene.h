/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:10:16 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/30 08:22:29 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

#include "minirt.h"



// -------------------------------------------------------------------------- //
//                                  light                                     //
// -------------------------------------------------------------------------- //

t_vector	normal_at(t_shape shape, t_point world_point);
t_light		point_light(t_point position, t_color intensity);
t_color		lighting(t_shape object, t_light light, t_point position, t_sight sight);
void		add_light(t_light **light_list, t_light light_to_add);

// ------------------------------ reflection ------------------------------

t_vector	reflect(t_vector in, t_vector normal);
t_color		reflected_color(t_world world, t_comps comps, int depth);

// ------------------------------ refraction ------------------------------

void		calculate_refractive_indexes(t_comps *comps, t_hit *hit_list);
t_color		refracted_color(t_world w, t_comps comps, int depth);
void		update_containers(t_shape **containers, t_shape object);
int			is_same_object(t_shape shape1, t_shape shape2);

// -------------------------------- shadow --------------------------------

bool		is_shadowed(t_world w, t_point position, t_light *light);

// -------------------------------------------------------------------------- //
//                                   world                                    //
// -------------------------------------------------------------------------- //

t_world		world(void);
t_hit		*intersect_world(t_world w, t_ray ray);

// -------------------------------------------------------------------------- //
//                                  camera                                    //
// -------------------------------------------------------------------------- //

t_camera	camera(double hsize, double vsize, double field_of_view);

#endif
