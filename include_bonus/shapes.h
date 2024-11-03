/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   shapes.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/31 05:44:00 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/31 08:16:14 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SHAPES_H
# define SHAPES_H

# include "MLX42/MLX42.h"
# include "tuples.h"

typedef enum e_tokens
{
	AMBIENT,
	CAMERA,
	LIGHT,
	MATERIAL,
	PATTERN,
	SPHERE,
	PLANE,
	CYLINDER,
	CONE,
}	t_tokens;

typedef enum e_patterns
{
	STRIPE,
	GRADIENT,
	RING,
	CHECKERS,
}	t_patterns;

typedef struct s_uv_image
{
	int				has_bump_map;
	mlx_texture_t	*texture;
	void			(*map_fn)(t_point, double *, double *);
}	t_uv_image;

typedef struct s_sphere
{
	t_point	origin;
	double	radius;
}	t_sphere;

typedef struct s_plane
{
	t_point	origin;
}	t_plane;

typedef struct s_cylinder
{
	t_point	origin;
	double	radius;
	double	minimum;
	double	maximum;
	int		closed;
}	t_cylinder;

typedef struct s_cone
{
	t_point	origin;
	double	radius;
	double	minimum;
	double	maximum;
	int		closed;
}	t_cone;

typedef struct s_checkers
{
	int		width;
	int		height;
	t_color	color_a;
	t_color	color_b;
}	t_checkers;

typedef struct s_map
{
	t_checkers	checkers;
	void		(*map_fn)(t_point, double *, double *);
}	t_map;

typedef struct s_pattern
{
	int			has_pattern;
	t_color		color_a;
	t_color		color_b;
	t_map		map;
	t_matrix	transform;
	t_matrix	inverse;
	t_patterns	pattern_type;
}	t_pattern;

typedef struct s_material
{
	t_color		ambient;
	double		diffuse;
	double		specular;
	double		shininess;
	double		reflective;
	double		transparency;
	double		refractive_index;
	t_color		color;
	t_pattern	pattern;
	t_uv_image	bump_map;
}	t_material;

typedef struct s_material_lst
{
	char					*name;
	t_material				material;
	struct s_material_lst	*next;
}	t_material_lst;

typedef struct s_pattern_list
{
	char					*name;
	t_pattern				pattern;
	struct s_pattern_list	*next;
}	t_pattern_list;

typedef struct s_shape
{
	int				id;
	union
	{
		t_sphere	sphere_shape;
		t_plane		plane_shape;
		t_cylinder	cylinder_shape;
		t_cone		cone_shape;
	};
	t_matrix		transform;
	t_matrix		inverse;
	t_matrix		transposed_inverse;
	t_material		material;
	t_tokens		shape_type;
	struct s_shape	*next;
}	t_shape;

// -------------------------------------------------------------------------- //
//                                   shapes                                   //
// -------------------------------------------------------------------------- //

t_shape		new_shape(void);
void		add_shape(t_shape **shape_list, t_shape shape);
void		shape_clear_list(t_shape **shape_list);
t_vector	local_normal_at(t_shape s, t_point obj_point);
void		set_transformation(t_shape *shape, t_matrix tranformation);
t_matrix	rotation_matrix(t_point position, \
							t_vector direction, t_shape shape);

// -------------------------------------------------------------------------- //
//                                   sphere                                   //
// -------------------------------------------------------------------------- //

t_shape		sphere(void);
t_vector	normal_at_sphere(t_shape sphere, t_point obj_point);

// -------------------------------------------------------------------------- //
//                                   plane                                    //
// -------------------------------------------------------------------------- //

t_shape		plane(void);
t_vector	normal_at_plane(t_shape plane, t_point obj_point);

// -------------------------------------------------------------------------- //
//                                 cylinder                                   //
// -------------------------------------------------------------------------- //

t_shape		cylinder(void);
t_vector	normal_at_cylinder(t_shape s, t_point obj_point);

// -------------------------------------------------------------------------- //
//                                   plane                                    //
// -------------------------------------------------------------------------- //

t_shape		cone(void);
t_vector	normal_at_cone(t_shape s, t_point obj_point);

// -------------------------------------------------------------------------- //
//                                  texture                                   //
// -------------------------------------------------------------------------- //

t_material	material(void);

// ------------------------------ patterns ----------------------------------

void		set_pattern_transform(t_pattern *pattern, t_matrix transformation);
t_color		pattern_at_shape(t_pattern pattern, t_shape object, \
							t_point world_point);
t_pattern	default_pattern(void);

// ------------------------------ stripe -------------------------------------

t_pattern	stripe_pattern(t_color color_a, t_color color_b);
t_color		stripe_at(t_pattern pattern, t_point pattern_point);

// ------------------------------ gradient -----------------------------------

t_pattern	gradient_pattern(t_color color_a, t_color color_b);
t_color		gradient_at(t_pattern pattern, t_point pattern_point);

// ------------------------------ ring ---------------------------------------

t_pattern	ring_pattern(t_color color_a, t_color color_b);
t_color		ring_at(t_pattern pattern, t_point point);

// ------------------------------ checkers ------------------------------------

t_pattern	checkers_pattern(t_color color_a, t_color color_b);
t_color		checkers_at(t_pattern pattern, t_point pattern_point);

// ------------------------------ texture map ---------------------------------

t_checkers	uv_checkers(int width, int height, \
						t_color color_a, t_color color_b);
t_color		uv_pattern_at(t_checkers checkers, double u, double v);
void		spherical_map(t_point point, double *u, double *v);
t_map		texture_map(t_checkers checkers, \
						void (*map_fn)(t_point, double *, double *));
void		cylindrical_map(t_point point, double *u, double *v);

#endif
