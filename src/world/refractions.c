/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   refractions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:42:02 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/29 21:42:03 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_color	refracted_color(t_world w, t_comps comps, int depth)
{
	double	n_ratio;
	double	cos_i;
	double	cos_t;
	double	sin2_t;
	t_ray	refract_ray;

	n_ratio = comps.n1 / comps.n2;
	cos_i = dot(comps.sight.eye, comps.sight.normal);
	sin2_t = pow(n_ratio, 2) * (1 - pow(cos_i, 2));
	if (comps.object.material.transparency == 0 || depth == 0 || sin2_t > 1)
		return (color(0, 0, 0));
	cos_t = sqrt(1.0 - sin2_t);
	refract_ray = ray(comps.under_point,
			tuple_subtract(
				tuple_multiply(comps.sight.normal, (n_ratio * cos_i) - cos_t),
				tuple_multiply(comps.sight.eye, n_ratio)));
	return (color_multiply(
			color_at(w, refract_ray, depth - 1),
			comps.object.material.transparency));
}
