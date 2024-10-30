/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pattern_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 23:44:46 by krocha-h          #+#    #+#             */
/*   Updated: 2024/10/30 07:34:41 by krocha-h         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "parser.h"

void	clear_pattern_list(t_world *world)
{
	t_pattern_list	*current;
	t_pattern_list	*next;

	current = world->scene.pattern_list;
	while (current)
	{
		next = current->next;
		free(current->name);
		free(current);
		current = next;
	}
	world->scene.pattern_list = NULL;
}

void	add_pattern(t_pattern_list **pattern_list,
	t_pattern pattern, char *name)
{
	t_pattern_list	*last;
	t_pattern_list	*new_pattern;

	new_pattern = malloc(sizeof(t_pattern_list));
	new_pattern->name = ft_strdup(name);
	new_pattern->pattern = pattern;
	new_pattern->next = NULL;
	if (*pattern_list == NULL)
		*pattern_list = new_pattern;
	else
	{
		last = *pattern_list;
		while (last->next)
			last = last->next;
		last->next = new_pattern;
	}
}

bool	check_if_pattern_exists(char *name, t_world *world)
{
	t_pattern_list	*current;

	current = world->scene.pattern_list;
	while (current)
	{
		if (ft_strncmp(current->name, name, ft_strlen(current->name)) == 0)
		{
			ft_putendl_fd(RED "Error!" RESET, 2);
			ft_putstr_fd("Pattern already exists: " GREEN, 2);
			ft_putstr_fd(name, 2);
			ft_putendl_fd(RESET, 2);
			return (false);
		}
		current = current->next;
	}
	return (true);
}
