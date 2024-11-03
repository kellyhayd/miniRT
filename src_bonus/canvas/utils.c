/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:26:50 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/31 08:47:20 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"
#include "tuples.h"
#include "scene.h"

void	print_ppm_header(int width, int height, int fd)
{
	ft_putstr_fd("P3\n", fd);
	ft_putnbr_fd(width, fd);
	ft_putstr_fd(" ", fd);
	ft_putnbr_fd(height, fd);
	ft_putstr_fd("\n255\n", fd);
}

char	*join_colors(t_color pixel)
{
	char	*r;
	char	*g;
	char	*b;
	char	*line;
	char	*tmp;

	r = ft_itoa((int)(pixel.r * 255));
	g = ft_itoa((int)(pixel.g * 255));
	b = ft_itoa((int)(pixel.b * 255));
	tmp = ft_strjoin(r, " ");
	line = ft_strjoin(tmp, g);
	free(tmp);
	tmp = ft_strjoin(line, " ");
	free(line);
	line = ft_strjoin(tmp, b);
	free(tmp);
	tmp = ft_strjoin(line, "\n");
	free(line);
	free(r);
	free(g);
	free(b);
	return (tmp);
}

void	print_line_ppm(t_color pixel, int fd, int flush)
{
	char		*line;
	static int	i;
	static char	saved[BUFFER_SIZE + 20];

	if (flush && i == 0)
		return ;
	line = join_colors(pixel);
	if (i + ft_strlen(line) > BUFFER_SIZE || flush)
	{
		(void)!write(fd, saved, i);
		i = 0;
	}
	i += ft_strlcpy(saved + i, line, ft_strlen(line) + 1);
	if (line)
		free(line);
}

void	canvas_to_ppm(t_canvas canvas, char *filename)
{
	int		y;
	int		x;
	int		fd;

	fd = open(filename, O_CREAT | O_TRUNC | O_WRONLY, 0644);
	if (fd < 0)
	{
		perror(filename);
		return ;
	}
	print_ppm_header(canvas.width, canvas.height, fd);
	y = 0;
	while (y < canvas.height)
	{
		x = 0;
		print_rendering_progress(canvas.width, canvas.height, y);
		while (x < canvas.width)
		{
			print_line_ppm(pixel_at(canvas, x, y), fd, 0);
			x++;
		}
		y++;
	}
	print_line_ppm((t_color){0, 0, 0}, fd, 1);
	close(fd);
}
