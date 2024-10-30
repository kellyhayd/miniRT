/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:45:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/30 06:57:02 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

void	ft_error(char *message)
{
	ft_putstr_fd(RED, 2);
	ft_putstr_fd("Error: ", 2);
	ft_putstr_fd(RESET, 2);
	ft_putstr_fd(ORANGE, 2);
	ft_putstr_fd(message, 2);
	ft_putstr_fd(RESET, 2);
}

int	almost_zero(float num)
{
	return (num < EPSILON && num > -EPSILON);
}

void	swap(double *a, double *b)
{
	double	tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

void	check_extension(char *filename)
{
	char	*extension;
	bool	ok;

	ok = 1;
	extension = ft_strrchr(filename, '.') + 1;
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

char	*get_file_name(char *file_name_base)
{
	char	*file_name;
	char	*new_name;

	file_name = ft_strdup(file_name_base);
	ft_strrchr(file_name, '.')[0] = '\0';
	new_name = ft_strjoin(file_name, ".ppm");
	free(file_name);
	return (new_name);
}
