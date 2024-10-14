# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: krocha-h <krocha-h@student.42sp.org.br>    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/10 19:29:07 by danbarbo          #+#    #+#              #
#    Updated: 2024/10/13 21:42:52 by krocha-h         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME	= libft.a
CC		= cc
FLAGS	= -Wall -Wextra -Werror
INCLUDE	= include
# .SILENT:

CYAN	= \033[0;36m
RED		= \033[0;31m
GREEN	= \033[0;32m
RESET	= \033[0m

SRC	= ${addprefix src/, \
			ft_array_size.c \
			ft_atof.c \
			ft_atoi.c \
			ft_bzero.c \
			ft_calloc.c \
			ft_isalnum.c \
			ft_isalpha.c \
			ft_isascii.c \
			ft_isdigit.c \
			ft_isprint.c \
			ft_itoa.c \
			ft_memchr.c \
			ft_memcmp.c \
			ft_memcpy.c \
			ft_memmove.c \
			ft_memset.c \
			ft_putchar_fd.c \
			ft_putendl_fd.c \
			ft_putnbr_fd.c \
			ft_putstr_fd.c \
			ft_read_all.c \
			ft_split.c \
			ft_strchr.c \
			ft_strdup.c \
			ft_striteri.c \
			ft_strjoin.c \
			ft_strlcat.c \
			ft_strlcpy.c \
			ft_strlen.c \
			ft_strmapi.c \
			ft_strncmp.c \
			ft_strnstr.c \
			ft_strrchr.c \
			ft_strtrim.c \
			ft_substr.c \
			ft_tolower.c \
			ft_toupper.c \
			ft_lstadd_back_bonus.c \
			ft_lstadd_front_bonus.c \
			ft_lstclear_bonus.c \
			ft_lstdelone_bonus.c \
			ft_lstiter_bonus.c \
			ft_lstlast_bonus.c \
			ft_lstmap_bonus.c \
			ft_lstnew_bonus.c \
			ft_lstsize_bonus.c \
			get_next_line.c \
			get_next_line_utils.c \
		}
OBJ	= ${SRC:src/%.c=obj/%.o}

all: ${NAME}

${NAME}: ${OBJ}
	@ar rcs ${NAME} ${OBJ}

obj/%.o: src/%.c
	@mkdir -p obj
	@${CC} ${FLAGS} -I ${INCLUDE} -c $< -o $@
	@printf "$(CYAN)Compiling $(GREEN)${notdir $<}$(RESET)\n"

clean:
	@rm -rf obj
	@printf "$(RED)Deleting object files$(RESET)\n"

fclean: clean
	@rm -f ${NAME}
	@printf "$(RED)Deleting ${NAME}$(RESET)\n"

re: fclean all

.PHONY: all clean fclean re
