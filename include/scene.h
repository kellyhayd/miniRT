/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   scene.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 08:10:16 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/31 08:51:12 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef SCENE_H
# define SCENE_H

# include "minirt.h"
# include "shapes.h"
# include "tuples.h"
# include "ray.h"

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

typedef struct s_comps
{
	double		t;
	double		n1;
	double		n2;
	int			inside;
	t_shape		object;
	t_point		point;
	t_point		over_point;
	t_point		under_point;
	t_sight		sight;
	t_vector	reflectv;
}	t_comps;

typedef struct s_light
{
	t_color			intensity;
	t_point			position;
	struct s_light	*next;
}	t_light;

typedef struct s_camera
{
	double		hsize;
	double		vsize;
	double		field_of_view;
	double		half_width;
	double		half_height;
	double		pixel_size;
	t_matrix	transform;
	t_matrix	inverse;
}	t_camera;

typedef struct s_scene
{
	int				pixel_sampling;
	t_camera		world_camera;
	double			ambient_ratio;
	t_color			ambient_color;
	int				has_ambient_color;
	int				has_camera;
	t_material_lst	*material_list;
	t_pattern_list	*pattern_list;
}	t_scene;

typedef struct s_world
{
	t_shape		*shape;
	t_light		*light;
	t_scene		scene;
}	t_world;

typedef struct s_anti_aliasing
{
	double	pixel_sampling;
	double	sample_x;
	double	sample_y;
}	t_anti_aliasing;

typedef struct s_canvas
{
	int		width;
	int		height;
	t_color	*pixels;
}	t_canvas;

typedef struct s_thread
{
	int			line;
	int			line_size;
	t_canvas	*canvas;
	t_world		world;
	t_camera	camera;
}	t_thread;

// -------------------------------------------------------------------------- //
//                                   canvas                                   //
// -------------------------------------------------------------------------- //

t_canvas	create_canvas(int width, int height);
t_color		pixel_at(t_canvas canvas, int x, int y);
mlx_image_t	*canvas_to_image(t_canvas canvas, mlx_t *mlx);
void		key_hook(mlx_key_data_t keydata, void *param);
void		start_render(t_world world, int save_to_file, char *file_name);
void		write_pixel(mlx_image_t *image, int x, int y, t_color color);
int			color_to_int(t_color color);
void		write_pixel_to_canvas(t_canvas *canvas, int x, int y, \
								t_color color);
void		canvas_to_ppm(t_canvas canvas, char *filename);

// -------------------------------------------------------------------------- //
//                                  light                                     //
// -------------------------------------------------------------------------- //

t_vector	normal_at(t_shape shape, t_point world_point);
t_light		point_light(t_point position, t_color intensity);
t_color		lighting(t_shape object, t_light light, \
					t_point position, t_sight sight);
void		add_light(t_light **light_list, t_light light_to_add);
void		light_clear_list(t_light **light_list);
t_comps		prepare_computations(t_hit hit, t_ray ray, t_hit *hit_list);
t_color		color_at(t_world w, t_ray r, int depth);

// ------------------------------ reflection ------------------------------

t_vector	reflect(t_vector in, t_vector normal);
t_color		reflected_color(t_world world, t_comps comps, int depth);

// ------------------------------ refraction ------------------------------

void		calculate_refractive_indexes(t_comps *comps, t_hit *hit_list);
t_color		refracted_color(t_world w, t_comps comps, int depth);
void		update_containers(t_shape **containers, t_shape object);
int			is_same_object(t_shape shape1, t_shape shape2);

// ------------------------------ shadow ----------------------------------

bool		is_shadowed(t_world w, t_point position, t_light *light);
t_color		shade_hit(t_world world, t_comps comps, int depth);

// -------------------------------------------------------------------------- //
//                                   world                                    //
// -------------------------------------------------------------------------- //

t_world		world(void);
t_hit		*intersect_world(t_world w, t_ray ray);
void		world_clear(t_world *world_to_clear);

// -------------------------------------------------------------------------- //
//                                  camera                                    //
// -------------------------------------------------------------------------- //

t_camera	camera(double hsize, double vsize, double field_of_view);
t_matrix	view_transform(t_point from, t_point to, t_vector up);
t_canvas	render(t_camera c, t_world w);
void		print_rendering_progress(int hsize, int vsize, int y);
t_color		color_average(t_color *colors, int size);
int			reset_threads(pthread_t *threads, int thread_count);
t_ray		ray_for_pixel(t_camera c, int x, int y, t_anti_aliasing aa_data);

#endif
