/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:08:09 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/25 21:26:56 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

t_light	point_light(t_point position, t_color intensity)
{
	return ((t_light){.intensity = intensity, .position = position});
}

t_material	material(void)
{
	return ((t_material){.color = color(1, 1, 1), .ambient = 0.1, .diffuse = 0.9, .specular = 0.9, .shininess = 200.0});
}

t_color	lighting(t_material m, t_light light, t_point position, t_vector eye, t_vector normal)
{
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	t_color		effective_color;
	t_vector	lightv;
	t_vector	reflectv;
	double		reflect_dot_eye;
	double		factor;

	effective_color = color_hadamard(m.color, light.intensity);
	lightv = normalize(tuple_subtract(light.position, position));
	ambient = color_multiply(effective_color, m.ambient);
	if(dot(lightv, normal) < 0)
	{
		diffuse = color(0, 0, 0);
		specular = color(0, 0, 0);
	}
	else
	{
		diffuse = color_multiply(effective_color, (m.diffuse * dot(lightv, normal)));
		reflectv = reflect(tuple_negate(lightv), normal);
		reflect_dot_eye = dot(reflectv, eye);
		if(reflect_dot_eye <= 0)
			specular = color(0, 0, 0);
		else
		{
			factor = pow(reflect_dot_eye, m.shininess);
			specular = color_multiply(light.intensity, factor * m.specular);
		}
	}
	return (color_add(color_add(ambient, diffuse), specular));
}
