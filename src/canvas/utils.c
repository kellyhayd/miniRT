#include "minirt.h"

void print_ppm_header(int width, int height, int fd)
{
	// dprintf - mais uma função que não poderia usar, mas o bônus deixa
	dprintf(fd, "P3\n%d %d\n255\n", width, height);
}

void print_line_ppm(t_color pixel, int fd)
{
	dprintf(fd, "%d %d %d ", (int)(pixel.r * 255), (int)(pixel.g * 255), (int)(pixel.b * 255));
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
			print_line_ppm(pixel_at(canvas, x, y), fd);
			x++;
		}
		y++;
	}
	close(fd);
}
