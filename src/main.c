/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:28:32 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/19 10:46:36 by krocha-h         ###   ########.fr       */
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
A   0.2                     255,255,255
# Camera
# <coordinates of camera position: x,y,z> <camera view: x,y,z> <pov:x,y,z>
C            -50,0,20                         0,0,0                70

## Error
## K    -40,0,30                  0.7           255,255,255

# Light
# <coordinates: x,y,z> <brightness: 0-1> <color:red,green,blue>
L     -40,0,30              0.7                255,255,255

# Plane
# <coordinates: x,y,z> <normal: x,y,z> <color:red,green,blue>
pl  0,0,0                0,1.0,0           255,0,225

# Sphere
# <coordinates: x,y,z> <diameter> <color:red,green,blue>
sp  0,0,20                20             255,0,0

#Cylinder
# <coordinates: x,y,z> <normal: x,y,z> <diameter> <height> <color:red,green,blue>
cy  50.0,0.0,20.6         0,0,1.0        14.2       21.42          10,0,255

*/
