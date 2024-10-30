/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_int.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 21:33:16 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/29 21:33:18 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minirt.h"

bool	parse_int(char *str, int *num)
{
	int	i;

	i = 0;
	while (str && str[i] && ft_isdigit(str[i]))
		i++;
	if (!str || str[i] != '\0')
	{
		ft_putendl_fd(RED "Error!" RESET, 2);
		ft_putstr_fd("Expected " GREEN "int" RESET
			", received " GREEN, 2);
		if (str)
			ft_putstr_fd(str, 2);
		else
			ft_putstr_fd("NULL", 2);
		ft_putendl_fd(RESET, 2);
		return (false);
	}
	*num = ft_atoi(str);
	return (true);
}
