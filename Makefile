#----------------------------------------------- Basic
NAME			= miniRT
NAME_BONUS		= miniRT_bonus
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

HEADERS_BONUS	= -I include_bonus \
					-I $(LIBMLX_FOLDER)/include \
					-I $(LIBFT_FOLDER)/include

LIBFT			= $(LIBFT_FOLDER)/libft.a
LIBMLX			= $(LIBMLX_FOLDER)/build/libmlx42.a
LIBS			= $(LIBMLX) $(LIBFT) -ldl -lglfw -pthread -lm

BUILD			= build
SRC_PATH		= src
SRC_PATH_BONUS	= src_bonus

SRC				= src/render/ray.c \
					src/render/shading.c \
					src/render/render.c \
					src/render/shadows.c \
					src/render/intersections.c \
					src/render/mlx.c \
					src/render/light.c \
					src/render/intersect_utils.c \
					src/render/reflection.c \
					src/render/light_list.c \
					src/world/refractive_idx.c \
					src/world/world.c \
					src/world/refractions.c \
					src/world/containers.c \
					src/world/prepare_computations.c \
					src/patterns/gradient.c \
					src/patterns/patterns.c \
					src/patterns/uv_checkers.c \
					src/patterns/stripe.c \
					src/patterns/ring.c \
					src/patterns/checkers.c \
					src/matrix/operations.c \
					src/matrix/transformation.c \
					src/matrix/rotation_matrix.c \
					src/matrix/determinant.c \
					src/matrix/rotation.c \
					src/matrix/basic.c \
					src/matrix/modification.c \
					src/tuples/tuple.c \
					src/tuples/tuple_operations.c \
					src/tuples/vector.c \
					src/tuples/point.c \
					src/camera/utils.c \
					src/camera/camera.c \
					src/main/main.c \
					src/main/utils.c \
					src/parse/scene/parse_ambient.c \
					src/parse/scene/parse_lights.c \
					src/parse/scene/parse_camera.c \
					src/parse/utils/parse_int.c \
					src/parse/utils/parse_double.c \
					src/parse/utils/parse_utils.c \
					src/parse/utils/parse_validations.c \
					src/parse/parameters/parse_color.c \
					src/parse/parameters/parse_coordinates.c \
					src/parse/parameters/parse_material.c \
					src/parse/parameters/parse_material_utils.c \
					src/parse/parameters/parse_pattern_utils.c \
					src/parse/parameters/parse_direction.c \
					src/parse/parameters/parse_pattern.c \
					src/parse/parse.c \
					src/parse/shapes/parse_cylinder.c \
					src/parse/shapes/parse_cone.c \
					src/parse/shapes/parse_plane.c \
					src/parse/shapes/parse_sphere.c \
					src/canvas/canvas.c \
					src/canvas/utils.c \
					src/colors/colors.c \
					src/colors/utils.c \
					src/materials/material.c \
					src/shapes/plane.c \
					src/shapes/sphere.c \
					src/shapes/shapes.c \
					src/shapes/cone_intersection.c \
					src/shapes/cylinder.c \
					src/shapes/cylinder_intersection.c \
					src/shapes/cone.c
SRC_BONUS		= src_bonus/render/ray.c \
					src_bonus/render/shading.c \
					src_bonus/render/render.c \
					src_bonus/render/shadows.c \
					src_bonus/render/intersections.c \
					src_bonus/render/mlx.c \
					src_bonus/render/light.c \
					src_bonus/render/intersect_utils.c \
					src_bonus/render/reflection.c \
					src_bonus/render/light_list.c \
					src_bonus/world/refractive_idx.c \
					src_bonus/world/world.c \
					src_bonus/world/refractions.c \
					src_bonus/world/containers.c \
					src_bonus/world/prepare_computations.c \
					src_bonus/patterns/gradient.c \
					src_bonus/patterns/patterns.c \
					src_bonus/patterns/uv_checkers.c \
					src_bonus/patterns/stripe.c \
					src_bonus/patterns/ring.c \
					src_bonus/patterns/checkers.c \
					src_bonus/matrix/operations.c \
					src_bonus/matrix/transformation.c \
					src_bonus/matrix/rotation_matrix.c \
					src_bonus/matrix/determinant.c \
					src_bonus/matrix/rotation.c \
					src_bonus/matrix/basic.c \
					src_bonus/matrix/modification.c \
					src_bonus/tuples/tuple.c \
					src_bonus/tuples/tuple_operations.c \
					src_bonus/tuples/vector.c \
					src_bonus/tuples/point.c \
					src_bonus/camera/utils.c \
					src_bonus/camera/camera.c \
					src_bonus/main/main.c \
					src_bonus/main/utils.c \
					src_bonus/parse/scene/parse_ambient.c \
					src_bonus/parse/scene/parse_lights.c \
					src_bonus/parse/scene/parse_camera.c \
					src_bonus/parse/utils/parse_int.c \
					src_bonus/parse/utils/parse_double.c \
					src_bonus/parse/utils/parse_utils.c \
					src_bonus/parse/utils/parse_validations.c \
					src_bonus/parse/parameters/parse_color.c \
					src_bonus/parse/parameters/parse_coordinates.c \
					src_bonus/parse/parameters/parse_material.c \
					src_bonus/parse/parameters/parse_material_utils.c \
					src_bonus/parse/parameters/parse_pattern_utils.c \
					src_bonus/parse/parameters/parse_direction.c \
					src_bonus/parse/parameters/parse_pattern.c \
					src_bonus/parse/parse.c \
					src_bonus/parse/shapes/parse_cylinder.c \
					src_bonus/parse/shapes/parse_cone.c \
					src_bonus/parse/shapes/parse_plane.c \
					src_bonus/parse/shapes/parse_sphere.c \
					src_bonus/canvas/canvas.c \
					src_bonus/canvas/utils.c \
					src_bonus/colors/colors.c \
					src_bonus/colors/utils.c \
					src_bonus/materials/material.c \
					src_bonus/shapes/plane.c \
					src_bonus/shapes/sphere.c \
					src_bonus/shapes/shapes.c \
					src_bonus/shapes/cone_intersection.c \
					src_bonus/shapes/cylinder.c \
					src_bonus/shapes/cylinder_intersection.c \
					src_bonus/shapes/cone.c

OBJ				= $(SRC:$(SRC_PATH)/%.c=$(BUILD)/%.o)
OBJ_BONUS		= $(SRC_BONUS:$(SRC_PATH_BONUS)/%.c=$(BUILD)/%.o)

#----------------------------------------------- bonus
ifdef WITH_BONUS
	NAME		= $(NAME_BONUS)
	HEADERS		= $(HEADERS_BONUS)
	SRC_PATH	= $(SRC_PATH_BONUS)
	SRC			= $(SRC_BONUS)
	OBJ			= $(OBJ_BONUS)
endif

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

bonus:
	$(MAKE) WITH_BONUS=TRUE

clean:
	@echo "$(RED)Removing objects...$(RESET)"
	@rm -rf $(BUILD)

fclean: clean
	@make -C $(LIBFT_FOLDER) fclean
	@rm -rf $(LIBMLX_FOLDER)/build
	@rm -rf $(NAME) $(NAME_BONUS)

re: fclean all
