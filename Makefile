
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
HEADERS		= -I ./include -I $(LIBMLX)/include -I $(LIBFT)/include
LIBS		= $(LIBMLX)/build/libmlx42.a ${LIBFT}/libft.a -ldl -lglfw -pthread -lm
BUILD		= build/
SRC_PATH	= src/
SRC			= $(shell find src -iname "*.c")
TEST_FILES	= $(shell find src -iname "*.c" ! -name "main.c") tests/tests_utils.c tests/tests_utils_print.c

OBJ			=$(SRC:%.c=$(BUILD)%.o)

#----------------------------------------------- Rules
all: libft libmlx $(NAME)

libft:
	$(MAKE) -C ./lib/libft
	@echo "$(GREEN)LIBFT is ready!$(RESET)"

libmlx:
	@cmake $(LIBMLX) -B $(LIBMLX)/build > /dev/null
	@make -C $(LIBMLX)/build -j4 > /dev/null
	@echo "$(GREEN)LIBMLX is ready!$(RESET)"

$(NAME): $(OBJ)
	@echo "$(PURPLE)Compiling miniRT...$(RESET)"
	@$(CC) $(OBJ) $(LIBS) $(HEADERS) -o $(NAME)
	@echo "$(GREEN)Done! Let's go! $(RESET)"

$(BUILD)%.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(CFLAGS) $(HEADERS) -c $< -o $@

clean:
	rm -rf $(BUILD)

fclean: clean
	rm -rf $(NAME)
	rm -rf test
	rm -rf pit

test: all
# 	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_tuples.c $(LIBS) -o test
# 	./test
#
# 	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_colors.c $(LIBS) -o test
# 	./test

#	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_matrix.c $(LIBS) -o test
#	./test

#	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_transformation.c $(LIBS) -o test
#	./test

	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_ray_intersection.c $(LIBS) -o test
	./test

pit: all
#	@$(CC) -g3 $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/projectiles.c $(LIBS) -o pit
	@$(CC) -g3 $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/parable.c $(LIBS) -o pit
	./pit

re: fclean all
