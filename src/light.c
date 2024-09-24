/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   light.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/23 23:08:09 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/23 23:23:18 by krocha-h         ###   ########.fr       */
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
