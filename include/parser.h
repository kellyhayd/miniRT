/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/30 07:19:55 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/30 08:20:33 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSER_H
# define PARSER_H

#include "minirt.h"

// -------------------------------------------------------------------------- //
//                                 basic                                      //
// -------------------------------------------------------------------------- //
bool		parse(int fd, t_world *new_world);
bool		parse_line(char *line, t_world *world);
int			get_token(char *line);

// -------------------------------------------------------------------------- //
//                                   shapes                                   //
// -------------------------------------------------------------------------- //
bool		parse_plane(char *line, t_world *world);
bool		parse_sphere(char *line, t_world *world);
bool		parse_cone(char *line, t_world *world);
bool		parse_cylinder(char *line, t_world *world);

// -------------------------------------------------------------------------- //
//                                  ambient                                   //
// -------------------------------------------------------------------------- //
bool		parse_camera(char *line, t_world *world);
bool		parse_ambient(char *line, t_world *world);
void		put_ambient_color(t_world *world);
bool		parse_light(char *line, t_world *world);

// -------------------------------------------------------------------------- //
//                                parameteres                                 //
// -------------------------------------------------------------------------- //
bool		parse_coordinates(char *splitted, t_point *position);
bool		parse_brightness(char *splitted, double *brightness);
bool		parse_color(char *splitted, t_color *new_color);
bool		parse_direction(char *str, t_vector *direction);
bool		parse_radius(char *str, double *radius);

bool		parse_pattern(char *line, t_world *world);
bool		parse_pattern_name(char *str, t_pattern *pattern, t_world *world);
bool		check_if_pattern_exists(char *name, t_world *world);
void		add_pattern(t_pattern_list **pattern_list, \
						t_pattern pattern, char *name);
void		clear_pattern_list(t_world *world);

bool		parse_material(char *line, t_world *world);
bool		parse_mater_name(char *str, t_material *material, t_world *world);
bool		parse_mater_shape(char **splitted, t_material *material, \
								t_world *world);
bool		parse_mater_name(char *str, t_material *material, t_world *world);
void		init_default_material(t_world *world);
bool		check_if_material_exists(char *name, t_world *world);
void		add_material(t_material_lst **material_list, \
						t_material material, char *name);
void		clear_material_list(t_world *world);

// -------------------------------------------------------------------------- //
//                                 validation                                 //
// -------------------------------------------------------------------------- //
bool		validate_count(char **split, int count);
bool		validate_double_range(char *str, double value, double min, \
								double max);
bool		validade_optionals(char **splitted);
bool		pos_validation(t_world *world);

// -------------------------------------------------------------------------- //
//                                   utils                                    //
// -------------------------------------------------------------------------- //
bool		parse_double(char *str, double *value);
bool		parse_int(char *str, int *num);
bool		parse_int_color(char *str, int *num);
bool		print_error(char *message);
void		print_line_error(char *line, int count_line);

#endif
