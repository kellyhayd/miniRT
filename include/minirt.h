/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minirt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:01:38 by danbarbo          #+#    #+#             */
/*   Updated: 2024/11/03 15:55:00 by krocha-h         ###   ########.fr       */
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

# define EPSILON        0.00001
# define NUM_THREADS    3
# define PIXEL_SAMPLING 3

# define WIDTH 1280
# define HEIGH 720

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h>
# include <fcntl.h>
# include <math.h>

# include "libft.h"
# include "get_next_line.h"
# include "MLX42/MLX42.h"

// -------------------------------------------------------------------------- //
//                                   utils                                    //
// -------------------------------------------------------------------------- //

int		float_compare(double d1, double d2);
void	ft_error(char *message);
int		almost_zero(float num);
void	swap(double *a, double *b);
void	check_extension(char *filename);
char	*get_file_name(char *file_name_base);

#endif
