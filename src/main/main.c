/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 20:28:32 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/29 23:51:54 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

int	main(int argc, char **argv)
{
	int		fd;
	int		save_to_file;
	t_world	new_world;

	if (!(argc == 2 || argc == 3))
		return (ft_error("Usage: ./miniRT [scene.rt] (--save-to-file)\n"), 1);
	check_extension(argv[1]);
	new_world = world();
	fd = open(argv[1], O_RDONLY);
	if (fd < 0)
		perror(argv[1]);
	if (fd < 0 || !parse(fd, &new_world))
		ft_error("Invalid map\n");
	else
	{
		if (argv[2])
			save_to_file = ft_strncmp("--save-to-file", argv[2], -1) == 0;
		else
			save_to_file = 0;
		start_render(new_world, save_to_file, get_file_name(argv[1]));
	}
	if (fd != -1)
		close(fd);
	world_clear(&new_world);
	return (0);
}
