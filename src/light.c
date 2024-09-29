/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:08:09 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/28 18:14:51 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Creates a point light source.
 *
 * This function initializes a point light source with a given position and intensity.
 *
 * @param position The position of the point light in the scene.
 * @param intensity The intensity (color) of the light emitted by the point light.
 * @return A t_light structure representing the point light source.
 */
t_light	point_light(t_point position, t_color intensity)
{
	return ((t_light){
		.intensity = intensity,
		.position = position,
		.next = NULL
	});
}

void	add_light(t_light **light_list, t_light light_to_add)
{
	t_light	*new_light;
	t_light	*aux;

	new_light = malloc(sizeof(t_light));
	*new_light = light_to_add;
	aux = *light_list;
	while (aux && aux->next)
		aux = aux->next;
	if (aux)
		aux->next = new_light;
	else
		*light_list = new_light;
}

void	light_clear_list(t_light **light_list)
{
	if (light_list && *light_list)
	{
		light_clear_list(&((*light_list)->next));
		free(*light_list);
		*light_list = NULL;
	}
}

/**
 * @brief Calculates the lighting effect on a material at a given position.
 *
 * This function computes the color resulting from the lighting effect on a material
 * based on the light source, the position of the point being shaded, the eye vector,
 * and the normal vector at that point.
 *
 * @param m The material properties of the object.
 * @param light The light source affecting the material.
 * @param position The position of the point being shaded.
 * @param eye The vector pointing towards the eye or camera.
 * @param normal The normal vector at the point being shaded.
 * @return The resulting color after applying the lighting effect.
 */
t_color	lighting(t_material m, t_light light, t_point position, \
					t_sight sight)
{
	t_color		ambient;
	t_color		diffuse;
	t_color		specular;
	t_exposure	e;

	diffuse = color(0, 0, 0);
	specular = color(0, 0, 0);
	e.effective_color = color_hadamard(m.color, light.intensity);
	e.lightv = normalize(tuple_subtract(light.position, position));
	ambient = color_multiply(e.effective_color, m.ambient);
	e.light_dot_normal = dot(e.lightv, sight.normal);
	if (e.light_dot_normal >= 0)
	{
		diffuse = color_multiply(e.effective_color, \
									m.diffuse * e.light_dot_normal);
		e.reflectv = reflect(tuple_negate(e.lightv), sight.normal);
		e.reflect_dot_eye = dot(e.reflectv, sight.eye);
		if (e.reflect_dot_eye > 0)
		{
			e.factor = pow(e.reflect_dot_eye, m.shininess);
			specular = color_multiply(light.intensity, e.factor * m.specular);
		}
	}
	return (color_add(color_add(ambient, diffuse), specular));
}
