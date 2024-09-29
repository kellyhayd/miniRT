/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:01:38 by danbarbo          #+#    #+#             */
/*   Updated: 2024/09/29 14:45:11 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINIRT_H
# define MINIRT_H

# define RESET  "\001\033[0m\002"
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

# include <stdio.h>
# include <stdlib.h>
# include <unistd.h>
# include <math.h>

# include "libft.h"
# include "MLX42/MLX42.h"

typedef struct s_tuple	t_tuple;
typedef struct s_tuple	t_point;
typedef struct s_tuple	t_vector;

typedef struct s_hit	t_hit;
typedef struct s_shape	t_shape;
// typedef struct s_sphere	t_sphere;
typedef struct s_light	t_light;

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

typedef struct s_ray
{
	t_point		origin;
	t_vector	direction;
}	t_ray;

typedef struct s_sphere
{
	t_point	origin;
	double	radius;
}	t_sphere;

typedef struct s_material
{
	double	ambient;
	double	diffuse;
	double	specular;
	double	shininess;
	t_color	color;
}	t_material;

struct s_shape
{
	union
	{
		t_sphere	sphere_shape;
		// t_plane		plane_shape;
		// t_cylinder	cylinder_shape;
	};
	t_matrix	transform;
	t_matrix	inverse;
	t_matrix	transposed_inverse;
	t_material	material;
	t_shape		*next;
};

struct s_hit
{
	double	t;
	t_shape	object;
	t_hit	*next;
};

struct s_light
{
	t_color	intensity;
	t_point	position;
	t_light	*next;
};

typedef struct s_world
{
	t_shape	*shape;
	t_light	*light;
	mlx_t	*mlx;
}	t_world;

typedef struct s_exposure
{
	t_color		effective_color;
	t_vector	lightv;
	t_vector	reflectv;
	double		reflect_dot_eye;
	double		factor;
	double		light_dot_normal;
}	t_exposure;

typedef struct s_sight
{
	t_vector	eye;
	t_vector	normal;
	bool		in_shadow;
}	t_sight;

typedef struct s_camera
{
	double		hsize;
	double		vsize;
	double		field_of_view;
	double		half_width;
	double		half_height;
	double		pixel_size;
	t_matrix	transform;
}	t_camera;

typedef struct s_comps
{
	double		t;
	t_shape		object;
	t_point		point;
	t_sight		sight;
	int			inside;
}	t_comps;

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

// -------------------------------------------------------------------------- //
//                                   canvas                                   //
// -------------------------------------------------------------------------- //

// void		write_pixel(mlx_image_t *image, int x, int y, int color);
void		write_pixel(mlx_image_t *image, int x, int y, t_color color);
int			color_to_int(t_color color);

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

// -------------------------------------------------------------------------- //
//                                    ray                                     //
// -------------------------------------------------------------------------- //

t_ray		ray(t_point origin, t_vector direction);
t_point		position(t_ray r, double t);
t_ray		ray_transform(t_ray ray, t_matrix matrix);

// -------------------------------------------------------------------------- //
//                                   shapes                                   //
// -------------------------------------------------------------------------- //

t_shape		sphere(void);
void		set_transformation(t_shape *shape, t_matrix tranformation);

// -------------------------------------------------------------------------- //
//                                intersection                                //
// -------------------------------------------------------------------------- //

void		intersect(t_hit **hit_list, t_shape s, t_ray r);
t_hit		intersection(double t, t_shape s);
int			intersection_count(t_hit *hit_list);
void		hit_clear_list(t_hit **hit_list);
void		add_intersection(t_hit **hit_list, t_hit isect);
t_hit		*hit(t_hit *hit_list);

// -------------------------------------------------------------------------- //
//                                  light                                     //
// -------------------------------------------------------------------------- //
t_vector	normal_at(t_shape shape, t_point world_point);
t_vector	reflect(t_vector in, t_vector normal);
t_light		point_light(t_point position, t_color intensity);
t_material	material(void);
t_color		lighting(t_material m, t_light light, t_point position, t_sight sight);

// -------------------------------------------------------------------------- //
//                                  shadow                                    //
// -------------------------------------------------------------------------- //
bool		is_shadowed(t_world w, t_point position);

// -------------------------------------------------------------------------- //
//                                   world                                    //
// -------------------------------------------------------------------------- //
t_world		world(void);
t_world		default_world(void);
t_hit		*intersect_world(t_world w, t_ray ray);

// -------------------------------------------------------------------------- //
//                                  camera                                    //
// -------------------------------------------------------------------------- //
t_camera	camera(double hsize, double vsize, double field_of_view);
t_ray		ray_for_pixel(t_camera c, int x, int y);

// -------------------------------------------------------------------------- //
//                                   utils                                    //
// -------------------------------------------------------------------------- //

int			float_compare(double d1, double d2);
void		ft_error(char *message);

// NÃO SEI ONDE POR
void	add_shape(t_shape **shape_list, t_shape shape);
void	world_clear(t_world *world_to_clear);
void	shape_clear_list(t_shape **shape_list);
void	add_light(t_light **light_list, t_light light_to_add);
void	light_clear_list(t_light **light_list);
t_comps	prepare_computations(t_hit hit, t_ray ray);
t_color	shade_hit(t_world world, t_comps comps);
t_color	color_at(t_world w, t_ray r);

#endif
