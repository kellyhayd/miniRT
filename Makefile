#----------------------------------------------- Basic
NAME			= miniRT
.DEFAULT_GOAL	= all
.PHONY:			all clean fclean re libft libmlx
.SILENT:

#----------------------------------------------- Colors
CYAN	= \033[0;36m
PURPLE	= \033[0;35m
GREEN	= \033[0;32m
RED		= \033[0;31m
BLUE	= \033[0;34m
YELLOW	= \033[0;33m
RESET	= \033[0m

#----------------------------------------------- Compilation
CC		:= cc

FLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -O2 -g3

VALGRIND	:= valgrind -q --leak-check=full --show-leak-kinds=all --track-origins=yes

#----------------------------------------------- Sources
LIBFT_FOLDER	= lib/libft
LIBMLX_FOLDER	= lib/MLX42

HEADERS			= -I include \
					-I $(LIBMLX_FOLDER)/include \
					-I $(LIBFT_FOLDER)/include

LIBFT			= $(LIBFT_FOLDER)/libft.a
LIBMLX			= $(LIBMLX_FOLDER)/build/libmlx42.a
LIBS			= $(LIBMLX) $(LIBFT) -ldl -lglfw -pthread -lm

BUILD			= build
SRC_PATH		= src

SRC				= $(shell find src -iname "*.c")
OBJ				= $(SRC:$(SRC_PATH)/%.c=$(BUILD)/%.o)

#----------------------------------------------- bonus
# define bonus
# 	ifdef WITH_BONUS
# 	NAME		= $(NAME_BONUS)
# 	SRCS		= $(SRCS_BONUS)
# 	OBJS		= $(OBJS_BONUS)
# endif

#----------------------------------------------- Rules
all: $(NAME)

$(LIBFT):
	@$(MAKE) -C $(LIBFT_FOLDER)
	@echo "$(GREEN)LIBFT $(BLUE)is ready!$(RESET)"

$(LIBMLX):
	@cmake $(LIBMLX_FOLDER) -B $(LIBMLX_FOLDER)/build
	@make -C $(LIBMLX_FOLDER)/build -j4
	@echo "$(GREEN)LIBMLX $(BLUE)is ready!$(RESET)"

$(BUILD):
	@mkdir -p $(BUILD)

$(BUILD)/%.o: $(SRC_PATH)/%.c include/minirt.h
	@echo "$(CYAN)Compiling $(GREEN)$(notdir $<)$(RESET)"
	@mkdir -p $(dir $@)
	@$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(LIBFT) $(LIBMLX) $(BUILD) $(OBJ)
	@echo "$(PURPLE)Compiling $(YELLOW)miniRT$(PURPLE)...$(RESET)"
	@$(CC) $(FLAGS) $(HEADERS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Done! Let's go!$(RESET)"

clean:
	@echo "$(RED)Removing objects...$(RESET)"
	@rm -rf $(BUILD)

fclean: clean
	@make -C $(LIBFT_FOLDER) fclean
	@rm -rf $(LIBMLX_FOLDER)/build
	@rm -rf $(NAME)

re: fclean all
