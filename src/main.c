/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:28:32 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/15 20:19:57 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	check_extension(char *filename)
{
	char	*extension;
	bool	ok;

	ok = 1;
	extension = ft_strchr(filename, '.') + 1;
	if (!extension)
		ok = 0;
	if (ft_strncmp(extension, "rt", 2) != 0)
		ok = 0;
	if (ok == 0)
	{
		ft_error("Invalid file extension\n");
		exit(EXIT_FAILURE);
	}
}

int	main(int argc, char **argv)
{
	int		fd;
	t_world	new_world;

	if (argc != 2)
		ft_error("Usage: ./miniRT [scene.rt]\n");
	check_extension(argv[1]);
	new_world = world();
	fd = open(argv[1], O_RDONLY);
	parse(fd, &new_world);

	return (0);
}


/*

# The Basic Shapes 01

# Ambient Light
# <intensity: 0-1> <color: red, green, blue>
A   0.1                  255,255,255

# Camera
# <coordinates of camera position: x,y,z> <camera view: x,y,z> <pov:x,y,z>
C   0,15,-5              1,0,0           10

# Error
# K    -40,0,30                  0.7           255,255,255

# Light
# <coordinates: x,y,z> <brightness: 0-1> <color:red,green,blue>
L   10,12,-5             1               255,0,0

# Sphere
# <coordinates: x,y,z> <diameter> <color:red,green,blue>
sp  0,0,0                1               255,51,255*/
