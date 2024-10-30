/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 21:45:10 by danbarbo          #+#    #+#             */
/*   Updated: 2024/10/13 14:23:54 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

/**
 * @brief Compares two floating-point numbers for equality.
 *
 * This function compares two double precision floating-point numbers
 * to determine if they are equal within a certain tolerance.
 *
 * @param d1 The first double to compare.
 * @param d2 The second double to compare.
 * @return An integer indicating the result of the comparison:
 *         1 if the numbers are considered equal (minor than EPSILON),
 *         0 otherwise.
 */
int	float_compare(double d1, double d2)
{
	return (fabs(d1 - d2) < EPSILON);
}

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

	extension = ft_strrchr(filename, '.');
	if (!extension || ft_strncmp(extension, ".rt", -1) != 0)
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
