/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: danbarbo <danbarbo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/26 23:31:21 by danbarbo          #+#    #+#             */
/*   Updated: 2023/11/15 16:16:20 by danbarbo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <unistd.h>
# include <stdlib.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif

typedef enum e_status
{
	FAIL = -1,
	READ,
	BUILD_STRING,
	FINISH
}	t_status;

typedef struct s_list_gnl
{
	char				content;
	struct s_list_gnl	*next;
}	t_list_gnl;

char	*get_next_line(int fd);
char	*build_line(t_list_gnl **line);
char	*read_fd(int fd, t_list_gnl **line);
int		gnl_lst_next_line_size(t_list_gnl *lst);
int		gnl_lstadd_back(t_list_gnl **lst, char c);
int		put_in_list(t_list_gnl **line, char *line_part, int size_readed);
void	gnl_lstclear(t_list_gnl **lst);

#endif
