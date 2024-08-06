#----------------------------------------------- Basic
NAME			= miniRT
.DEFAULT_GOAL	= all
.PHONY:			all clean fclean re libft libmlx
.SILENT:

#----------------------------------------------- Colors
CYAN	= \033[0;36m
PURPLE	= \033[0;35m
GREEN	= \033[0;32m
RESET	= \033[0m

#----------------------------------------------- Compilation
CC		:= cc
CFLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast

#----------------------------------------------- Sources
LIBMLX		= ./lib/MLX42
LIBFT		= ./lib/libft
HEADERS		:= -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include
LIBS		:= $(LIBMLX)/build/libmlx42.a ${LIBFT}/libft.a -ldl -lglfw -pthread -lm
BUILD		= build/
SRC_PATH	= src/
SRC			= $(shell find src -iname "*.c")

OBJ			=$(SRC:%.c=$(BUILD)%.o)

#-----------------------------------------------Rules
all: libft libmlx $(NAME)

libft:
	$(MAKE) -C ./lib/libft
	@echo "$(GREEN)LIBFT is ready!$(RESET)"

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build && make -C $(LIBMLX)/build -j4
	@echo "$(GREEN)LIBMLX is ready!$(RESET)"

$(NAME): $(OBJ)
	@echo "$(PURPLE)Compiling miniRT...$(RESET)"
	@$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)Done! Let's go! $(RESET)"

$(BUILD)%.o: %.c
		mkdir -p $(dir $@)
		$(CC) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -rf $(NAME)

re: fclean all
