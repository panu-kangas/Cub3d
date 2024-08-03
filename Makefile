NAME	= cub3D
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -g
LIBMLX	= ./lib/MLX42/build/libmlx42.a
LIBFT	= ./lib/libft/libft.a
MAND	= ./srcs/mandatory
BONUS	= ./srcs/bonus

HEADERS	= -I ./lib/MLX42/include -I ./lib/libft -I ./incl
LIBS	= $(LIBMLX) $(LIBFT) -ldl -pthread -lm -lglfw -L"/Users/$(USER)/.brew/opt/glfw/lib/"

SRCS	= $(MAND)/main.c $(MAND)/error_and_exit.c $(MAND)/get_map.c $(MAND)/utils.c \
		$(MAND)/draw_image.c $(MAND)/find_wall_distance.c $(MAND)/get_images.c $(MAND)/keyhook.c \
		$(MAND)/get_intersection_x.c $(MAND)/get_intersection_y.c  \
		$(MAND)/compare_distance.c $(MAND)/check_for_collision.c $(MAND)/check_map_borders.c \
		$(MAND)/get_paths_and_colors.c $(MAND)/map_validation.c \
		$(MAND)/key_actions.c $(MAND)/get_map_utils.c $(MAND)/map_validation_utils.c \
		\
		\
		$(MAND)/debug.c 
OBJS	= ${SRCS:.c=.o}

BONSRCS	= $(BONUS)/main_bonus.c $(BONUS)/error_and_exit_bonus.c $(BONUS)/get_map_bonus.c $(BONUS)/utils_bonus.c \
		$(BONUS)/draw_image_bonus.c $(BONUS)/find_wall_distance_bonus.c $(BONUS)/get_images_bonus.c $(BONUS)/keyhook_bonus.c \
		$(BONUS)/get_intersection_x_bonus.c $(BONUS)/get_intersection_y_bonus.c $(BONUS)/key_actions_bonus.c \
		$(BONUS)/compare_distance_bonus.c $(BONUS)/check_for_collision_bonus.c $(BONUS)/draw_functions_bonus.c \
		$(BONUS)/draw_player_icon_bonus.c $(BONUS)/check_map_borders_bonus.c \
		$(BONUS)/get_paths_and_colors_bonus.c $(BONUS)/map_validation_bonus.c \
		$(BONUS)/get_map_utils_bonus.c $(BONUS)/map_validation_utils_bonus.c \
		$(BONUS)/validate_doors_and_enemies.c \
		\
		\
		$(BONUS)/debug_bonus.c

BONOBJS	= ${BONSRCS:.c=.o}

all: $(LIBMLX) $(LIBFT) $(NAME)

$(LIBMLX):
	cmake ./lib/MLX42 -B ./lib/MLX42/build && make -C ./lib/MLX42/build -j4

$(LIBFT):
	make -C ./lib/libft/.

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME) -fsanitize=address,undefined

bonus: .bonus

.bonus: $(LIBMLX) $(LIBFT) $(BONOBJS)
	$(CC) $(BONOBJS) $(LIBS) $(HEADERS) -o $(NAME) -fsanitize=address,undefined
	touch .bonus

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $< $(HEADERS)

clean:
	rm -f $(OBJS)
	rm -f $(BONOBJS)
	make fclean -C ./lib/libft/.
	rm -rf ./lib/MLX42/build
	rm -f .bonus

fclean: clean
	rm -f $(NAME)

re: clean all

.PHONY: all, clean, fclean, re, bonus

