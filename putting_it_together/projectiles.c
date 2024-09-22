/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   projectiles.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/11 16:38:28 by krocha-h          #+#    #+#             */
/*   Updated: 2024/09/22 12:55:50 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

typedef struct projectile
{
	t_point		position;
	t_vector	velocity;
}	projectile;

typedef struct environment
{
	t_vector	gravity;
	t_vector	wind;
}	environment;

projectile	tick(environment env, projectile proj)
{
	projectile	new;

	new.position = tuple_add(proj.position, proj.velocity);
	new.velocity = tuple_add(tuple_add(proj.velocity, env.gravity), env.wind);
	return (new);
}

int main(void)
{
	int			ticks = 0;
	projectile	proj;
	projectile	proj_emulation;
	environment	env;

	proj.position = point(0, 1, 0);
	proj.velocity = normalize(vector(1, 1, 0));

	env.gravity = vector(0, -0.1, 0);
	env.wind = vector(-0.01, 0, 0);

	proj_emulation = proj;
	while (proj_emulation.position.y > 0)
	{
		proj_emulation = tick(env, proj_emulation);
		printf("%2d - pos: x = %5.2lf - y = %5.2lf - z = %5.2lf\n", ticks,
			proj_emulation.position.x, proj_emulation.position.y, proj_emulation.position.z);
		ticks++;
	}

	return (0);
}
