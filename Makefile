
#----------------------------------------------- Basic
NAME			= miniRT
.DEFAULT_GOAL	= all
.PHONY:			all clean fclean re libft libmlx
# .SILENT:

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
FLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -Ofast -g3

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

TEST_FILES		= $(shell find src -iname "*.c" ! -name "main.c") \
					tests/tests_utils.c \
					tests/tests_utils_print.c

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

$(BUILD)/%.o: $(SRC_PATH)/%.c
	@echo "$(CYAN)Compiling $(GREEN)$(notdir $<)$(RESET)"
	@$(CC) $(FLAGS) $(HEADERS) -c $< -o $@

$(NAME): $(LIBFT) $(LIBMLX) $(BUILD) $(OBJ)
	@echo "$(PURPLE)Compiling $(YELLOW)miniRT$(PURPLE)...$(RESET)"
	@$(CC) $(FLAGS) $(HEADERS) $(OBJ) $(LIBS) -o $(NAME)
	@echo "$(GREEN)Done! Let's go!$(RESET)"

clean:
	@echo "$(RED)Removing objects...$(RESET)"
	@rm -rf $(BUILD)

fclean: clean
#	@make -C $(LIBFT_FOLDER) fclean
#	@rm -rf $(LIBMLX_FOLDER)/build
	@rm -rf $(NAME)
	@rm -rf test
	@rm -rf pit

test: all
# 	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_tuples.c $(LIBS) -o test
# 	@./test
#
# 	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_colors.c $(LIBS) -o test
# 	@./test

#	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_matrix.c $(LIBS) -o test
#	@./test

#	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_transformation.c $(LIBS) -o test
#	@./test

	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_ray_intersection.c $(LIBS) -o test
	@./test

pit: all
#	@$(CC) -g3 $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/projectiles.c $(LIBS) -o pit
	@$(CC) -g3 $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/parable.c $(LIBS) -o pit
	./pit

re: fclean all
