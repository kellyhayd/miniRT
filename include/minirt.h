/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:01:38 by danbarbo          #+#    #+#             */
/*   Updated: 2024/08/11 17:45:11 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define RESET  "\001\033[0m\002"
# define R      "\001\033[1;31m\002"
# define G      "\001\033[1;32m\002"
# define Y      "\001\033[1;33m\002"
# define B      "\001\033[1;34m\002"
# define M      "\001\033[1;35m\002"
# define C      "\001\033[1;36m\002"
# define W      "\001\033[1;37m\002"
# define ORANGE "\001\033[38;5;208m\002"
# define BLUE   "\001\033[38;5;27m\002"
# define GREEN  "\001\033[38;5;46m\002"
# define RED    "\001\033[38;5;196m\002"
# define YELLOW "\001\033[38;5;226m\002"
# define CYAN   "\001\033[38;5;51m\002"
# define PURPLE "\001\033[38;5;129m\002"
# define GREY   "\001\033[38;5;240m\002"
# define WHITE  "\001\033[38;5;231m\002"
# define BLACK  "\001\033[38;5;16m\002"
# define BOLD   "\001\033[1m\002"
# define UNDER  "\001\033[4m\002"
# define BLINK  "\001\033[5m\002"
# define REVERSE "\001\033[7m\002"

# define EPSILON 0.00001

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <math.h>

#include "libft.h"
#include "MLX42/MLX42.h"

typedef struct s_tuple t_tuple;
typedef struct s_tuple t_point;
typedef struct s_tuple t_vector;

struct s_tuple
{
	double	x;
	double	y;
	double	z;
	double	w;
};

typedef struct s_color
{
	double	r;
	double	g;
	double	b;
}	t_color;


// -------------------------------------------------------------------------- //
//                                   tuple                                    //
// -------------------------------------------------------------------------- //

int			tuple_compare(t_tuple tuple1, t_tuple tuple2);
t_tuple		tuple(double x, double y, double z, double w);
t_tuple		tuple_adding(t_tuple tuple1, t_tuple tuple2);
t_tuple		tuple_subtracting(t_tuple tuple1, t_tuple tuple2);
t_tuple		tuple_negating(t_tuple tuple);
t_tuple		tuple_multiplying(t_tuple tuple, double scalar);
t_tuple		tuple_dividing(t_tuple tuple, double scalar);

// -------------------------------------------------------------------------- //
//                                   point                                    //
// -------------------------------------------------------------------------- //

t_point		point(double x, double y, double z);

// -------------------------------------------------------------------------- //
//                                   vector                                   //
// -------------------------------------------------------------------------- //

t_vector	vector(double x, double y, double z);
double		vector_magnitude(t_vector vector1);
t_vector	vector_normalize(t_vector vector1);
double		vector_dot_product(t_vector vector1, t_vector vector2);
t_tuple		vector_cross_product(t_vector vector1, t_vector vector2);

// -------------------------------------------------------------------------- //
//                                  colors                                    //
// -------------------------------------------------------------------------- //

t_color		color(double r, double g, double b);
t_color		color_adding(t_color color1, t_color color2);
t_color		color_subtracting(t_color color1, t_color color2);
t_color		color_multiplying(t_color color1, double scalar);
t_color		hadamard_product(t_color color1, t_color color2);

// -------------------------------------------------------------------------- //
//                                   utils                                    //
// -------------------------------------------------------------------------- //

int			float_compare(double d1, double d2);

#endif
