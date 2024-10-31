/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:30:44 by danbarbo          #+#    #+#             */
/*   Updated: 2023/11/15 16:36:45 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

int	gnl_lstadd_back(t_list_gnl **lst, char c)
{
	t_list_gnl	*new;
	t_list_gnl	*aux;

	new = malloc(sizeof(t_list_gnl));
	if (!new)
		return (FAIL);
	new->content = c;
	new->next = NULL;
	if (!(*lst))
		*lst = new;
	else
	{
		aux = *lst;
		while (aux->next)
			aux = aux->next;
		aux->next = new;
	}
	return (0);
}

void	gnl_lstclear(t_list_gnl **lst)
{
	t_list_gnl	*aux1;
	t_list_gnl	*aux2;

	if (lst)
	{
		aux1 = *lst;
		while (aux1)
		{
			aux2 = aux1->next;
			free(aux1);
			aux1 = aux2;
		}
		*lst = NULL;
	}
}

char	*read_fd(int fd, t_list_gnl **line)
{
	int		read_status;
	char	*line_part;
	char	*line_to_return;

	read_status = READ;
	line_part = NULL;
	line_to_return = NULL;
	if (!line)
		return (NULL);
	while (read_status == READ)
	{
		line_part = (char *) malloc(BUFFER_SIZE * sizeof(char));
		if (!line_part)
			return (NULL);
		read_status = read(fd, line_part, BUFFER_SIZE);
		if (read_status != FAIL)
			read_status = put_in_list(line, line_part, read_status);
		free(line_part);
		line_part = NULL;
	}
	if (read_status == FAIL)
		return (NULL);
	if (read_status == BUILD_STRING)
		line_to_return = build_line(line);
	return (line_to_return);
}

char	*get_next_line(int fd)
{
	char				*line_to_return;
	static t_list_gnl	*line;

	if (fd < 0 || BUFFER_SIZE <= 0)
	{
		gnl_lstclear(&line);
		return (NULL);
	}
	line_to_return = read_fd(fd, &line);
	if (!line_to_return)
		gnl_lstclear(&line);
	return (line_to_return);
}
