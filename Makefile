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
BUILD_BONUS		= build_bonus
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
SRC_BONUS		= src_bonus/render/mlx_bonus.c \
					src_bonus/render/light_bonus.c \
					src_bonus/render/render_bonus.c \
					src_bonus/render/shadows_bonus.c \
					src_bonus/render/intersect_utils_bonus.c \
					src_bonus/render/ray_bonus.c \
					src_bonus/render/reflection_bonus.c \
					src_bonus/render/intersections_bonus.c \
					src_bonus/render/shading_bonus.c \
					src_bonus/render/light_list_bonus.c \
					src_bonus/world/world_bonus.c \
					src_bonus/world/containers_bonus.c \
					src_bonus/world/refractive_idx_bonus.c \
					src_bonus/world/prepare_computations_bonus.c \
					src_bonus/world/refractions_bonus.c \
					src_bonus/patterns/uv_checkers_bonus.c \
					src_bonus/patterns/ring_bonus.c \
					src_bonus/patterns/patterns_bonus.c \
					src_bonus/patterns/checkers_bonus.c \
					src_bonus/patterns/stripe_bonus.c \
					src_bonus/patterns/gradient_bonus.c \
					src_bonus/matrix/basic_bonus.c \
					src_bonus/matrix/modification_bonus.c \
					src_bonus/matrix/determinant_bonus.c \
					src_bonus/matrix/operations_bonus.c \
					src_bonus/matrix/rotation_matrix_bonus.c \
					src_bonus/matrix/rotation_bonus.c \
					src_bonus/matrix/transformation_bonus.c \
					src_bonus/tuples/tuple_bonus.c \
					src_bonus/tuples/tuple_operations_bonus.c \
					src_bonus/tuples/vector_bonus.c \
					src_bonus/tuples/point_bonus.c \
					src_bonus/camera/camera_bonus.c \
					src_bonus/camera/utils_bonus.c \
					src_bonus/main/utils_bonus.c \
					src_bonus/main/main_bonus.c \
					src_bonus/parse/parse_bonus.c \
					src_bonus/parse/scene/parse_camera_bonus.c \
					src_bonus/parse/scene/parse_lights_bonus.c \
					src_bonus/parse/scene/parse_ambient_bonus.c \
					src_bonus/parse/utils/parse_validations_bonus.c \
					src_bonus/parse/utils/parse_double_bonus.c \
					src_bonus/parse/utils/parse_utils_bonus.c \
					src_bonus/parse/utils/parse_int_bonus.c \
					src_bonus/parse/parameters/parse_material_utils.c \
					src_bonus/parse/parameters/parse_direction_bonus.c \
					src_bonus/parse/parameters/parse_pattern_bonus.c \
					src_bonus/parse/parameters/parse_material_bonus.c \
					src_bonus/parse/parameters/parse_pattern_utils.c \
					src_bonus/parse/parameters/parse_coordinates_bonus.c \
					src_bonus/parse/parameters/parse_color_bonus.c \
					src_bonus/parse/shapes/parse_cylinder_bonus.c \
					src_bonus/parse/shapes/parse_plane_bonus.c \
					src_bonus/parse/shapes/parse_cone_bonus.c \
					src_bonus/parse/shapes/parse_sphere_bonus.c \
					src_bonus/canvas/canvas_bonus.c \
					src_bonus/canvas/utils_bonus.c \
					src_bonus/colors/colors_bonus.c \
					src_bonus/colors/utils_bonus.c \
					src_bonus/materials/material_bonus.c \
					src_bonus/shapes/sphere_bonus.c \
					src_bonus/shapes/plane_bonus.c \
					src_bonus/shapes/cone_bonus.c \
					src_bonus/shapes/cylinder_bonus.c \
					src_bonus/shapes/cone_intersection_bonus.c \
					src_bonus/shapes/cylinder_intersection_bonus.c \
					src_bonus/shapes/shapes_bonus.c

OBJ				= $(SRC:$(SRC_PATH)/%.c=$(BUILD)/%.o)
OBJ_BONUS		= $(SRC_BONUS:$(SRC_PATH_BONUS)/%.c=$(BUILD)/%.o)

#----------------------------------------------- bonus
ifdef WITH_BONUS
	NAME		= $(NAME_BONUS)
	HEADERS		= $(HEADERS_BONUS)
	SRC_PATH	= $(SRC_PATH_BONUS)
	SRC			= $(SRC_BONUS)
	OBJ			= $(OBJ_BONUS)
	BUILD		= $(BUILD_BONUS)
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

$(BUILD)/%.o: $(SRC_PATH)/%.c
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
	@rm -rf $(BUILD) $(BUILD_BONUS)

fclean: clean
	@make -C $(LIBFT_FOLDER) fclean
	@rm -rf $(LIBMLX_FOLDER)/build
	@rm -rf $(NAME) $(NAME_BONUS)

re: fclean all
