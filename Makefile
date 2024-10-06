
#----------------------------------------------- Basic
NAME			= miniRT
.DEFAULT_GOAL	= all
.PHONY:			all clean fclean re libft libmlx test \
				tests_tuples \
				tests_colors \
				tests_matrix \
				tests_transformation \
				tests_ray_intersection \
				tests_light \
				tests_world \
				tests_camera \
				tests_shadows
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

ifeq ($(PROF), 1)
	FLAGS	:= -pg
else
	FLAGS	:= -Wextra -Wall -Werror -Wunreachable-code -O2 -g3
endif

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

TEST_FILES		= $(shell find src -iname "*.c" ! -name "main.c") \
					tests/tests_utils_compare.c \
					tests/tests_utils_print.c

TESTS 			=	tests_tuples \
					tests_colors \
					tests_matrix \
					tests_transformation \
					tests_ray_intersection \
					tests_light \
					tests_world \
					tests_camera \
					tests_shadows \
					tests_planes \
					tests_cylinder \
					tests_cone \
					tests_patterns

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
#	@make -C $(LIBFT_FOLDER) fclean
#	@rm -rf $(LIBMLX_FOLDER)/build
	@rm -rf $(NAME)
	@rm -rf test
	@rm -rf $(TESTS)
	@rm -rf pit

clear_tests:
	@rm -rf $(TESTS)

test: all $(TESTS)

tests_tuples: all
	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_tuples.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_colors: all
	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_colors.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_matrix: all
	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_matrix.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_transformation: all
	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_transformation.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_ray_intersection: all
	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_ray_intersection.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_light: all
	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_light.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_world: all
	@$(CC) $(FLAGS) $(HEADERS) $(TEST_FILES) tests/tests_world.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_camera: all
	@$(CC) $(FLAGS) $(HEADERS) $(TEST_FILES) tests/tests_camera.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_shadows: all
	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_shadows.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_planes: all
	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_planes.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_cylinder: all
	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_cylinder.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_cone: all
	@$(CC) -g3 $(HEADERS) $(TEST_FILES) tests/tests_cone.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

tests_patterns: all
	@$(CC) $(FLAGS) $(HEADERS) $(TEST_FILES) tests/tests_patterns.c $(LIBS) -o $@
	@$(VALGRIND) ./$@

pit: all
#	@$(CC) $(FLAGS) $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/projectiles.c $(LIBS) -o pit
#	@$(CC) $(FLAGS) $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/parable.c $(LIBS) -o pit
#	@$(CC) $(FLAGS) $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/silhouette.c $(LIBS) -o pit
#	@$(CC) $(FLAGS) $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/sphere.c $(LIBS) -o pit
#	@$(CC) $(FLAGS) $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/many_spheres.c $(LIBS) -o pit
#	@$(CC) $(FLAGS) $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/planes.c $(LIBS) -o pit
	@$(CC) $(FLAGS) $(HEADERS) $(shell find src -iname "*.c" ! -name "main.c") putting_it_together/patterns.c $(LIBS) -o pit
#	@./pit

ifeq ($(PROF), 1)
	@gprof pit gmon.out > prof
	@< prof gprof2dot | dot -Tpng -o output.png
endif


re: fclean all
