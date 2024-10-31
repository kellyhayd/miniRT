/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atof.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/13 21:36:16 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/13 21:41:52 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

double	calculate_decimal(const char *str, double dec_place)
{
	double	decimal;

	decimal = 0;
	str++;
	while (ft_isdigit(*str))
	{
		decimal = decimal + (*str - '0') * dec_place;
		dec_place = dec_place / 10;
		str++;
	}
	return (decimal);
}

double	ft_atof(const char *str)
{
	double	result;
	double	sign;
	double	decimal;
	double	dec_place;

	result = 0;
	sign = 1;
	decimal = 0;
	dec_place = 0.1;
	while (ft_isspace(*str))
		str++;
	if (*str == '-')
	{
		sign = -1;
		str++;
	}
	while (ft_isdigit(*str))
	{
		result = result * 10 + (*str - '0');
		str++;
	}
	if (*str == '.')
		decimal = calculate_decimal(str, dec_place);
	return ((result + decimal) * sign);
}
