/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tuples_bonus.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 06:05:20 by krocha-h          #+#    #+#             */
/*   Updated: 2024/11/03 16:52:31 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TUPLES_BONUS_H
# define TUPLES_BONUS_H

typedef struct s_tuple	t_tuple;
typedef struct s_tuple	t_point;
typedef struct s_tuple	t_vector;

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

typedef struct s_matrix
{
	double	tab[16];
	int		rows;
	int		cols;
}	t_matrix;

// -------------------------------------------------------------------------- //
//                                   tuple                                    //
// -------------------------------------------------------------------------- //

t_tuple		tuple(double x, double y, double z, double w);
int			tuple_compare(t_tuple tuple1, t_tuple tuple2);
t_tuple		tuple_add(t_tuple tuple1, t_tuple tuple2);
t_tuple		tuple_subtract(t_tuple tuple1, t_tuple tuple2);
t_tuple		tuple_negate(t_tuple tuple);
t_tuple		tuple_multiply(t_tuple tuple, double scalar);
t_tuple		tuple_divide(t_tuple tuple, double scalar);

// -------------------------------------------------------------------------- //
//                                   point                                    //
// -------------------------------------------------------------------------- //

t_point		point(double x, double y, double z);

// -------------------------------------------------------------------------- //
//                                   vector                                   //
// -------------------------------------------------------------------------- //

t_vector	vector(double x, double y, double z);
double		magnitude(t_vector vector1);
t_vector	normalize(t_vector vector1);
double		dot(t_vector vector1, t_vector vector2);
t_tuple		cross(t_vector vector1, t_vector vector2);

// -------------------------------------------------------------------------- //
//                                  colors                                    //
// -------------------------------------------------------------------------- //

t_color		color(double r, double g, double b);
t_color		color_add(t_color color1, t_color color2);
t_color		color_subtract(t_color color1, t_color color2);
t_color		color_multiply(t_color color1, double scalar);
t_color		color_hadamard(t_color color1, t_color color2);
t_color		convert_color(t_color color);

// -------------------------------------------------------------------------- //
//                                   matrix                                   //
// -------------------------------------------------------------------------- //

// ---------------------------------- basic ---------------------------------
t_matrix	matrix_create(double *tab, int rows, int cols);
int			mx_compare(t_matrix matrix1, t_matrix matrix2);
void		mx_set(t_matrix *matrix1, int y, int x, double value);
double		mx_get(t_matrix *matrix1, int y, int x);
t_matrix	identity(void);

// ------------------------------ modification ------------------------------
t_matrix	mx_multiply(t_matrix matrix1, t_matrix matrix2);
t_tuple		mx_multiply_tuple(t_matrix matrix1, t_tuple tuple1);
t_matrix	transpose(t_matrix matrix1);
t_matrix	inverse(t_matrix matrix);

// ------------------------------ determinant -------------------------------
double		determinant(t_matrix matrix1);
t_matrix	submatrix(t_matrix matrix1, int y, int x);
double		minor(t_matrix matrix1, int y, int x);
double		cofactor(t_matrix matrix, int y, int x);

// -------------------------------------------------------------------------- //
//                             transformation                                 //
// -------------------------------------------------------------------------- //

t_matrix	translation(double x, double y, double z);
t_matrix	scaling(double x, double y, double z);
t_matrix	rotation_x(double radians);
t_matrix	rotation_y(double radians);
t_matrix	rotation_z(double radians);
t_matrix	shearing(double *prop_x, double *prop_y, double *prop_z);

#endif
