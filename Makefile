NAME	= cub3D
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -g
LIBMLX	= ./lib/MLX42/build/libmlx42.a
LIBFT	= ./lib/libft/libft.a
MAND	= ./srcs/mandatory
B	= ./srcs/bonus/

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

BONSRCS	= $Bmain_bonus.c $Berror_and_exit_bonus.c $Bget_map_bonus.c $Butils_bonus.c \
		$Bdraw_image_bonus.c $Bfind_wall_distance_bonus.c $Bget_images_bonus.c $Bkeyhook_bonus.c \
		$Bget_intersection_x_bonus.c $Bget_intersection_y_bonus.c $Bkey_actions_bonus.c \
		$Bcompare_distance_bonus.c $Bcheck_for_collision_bonus.c \
		$Bdraw_player_icon_bonus.c $Bcheck_map_borders_bonus.c  \
		$Bget_paths_and_colors_bonus.c $Bmap_validation_bonus.c \
		$Bget_map_utils_bonus.c $Bget_map_utils_2_bonus.c $Bmap_validation_utils_bonus.c \
		$Bvalidate_doors_and_enemies_bonus.c $Bdraw_minimap_bonus.c  $Bdraw_wall_bonus.c \
		$Bdraw_open_door_bonus.c \
		$Benemy_draw_bonus.c $Benemy_draw_utils_bonus.c $Benemy_draw_utils_2_bonus.c \
		$Benemy_handler_bonus.c $Benemy_draw_order_bonus.c \
		$Benemy_init_bonus.c \
		$Bget_intersection_door_x_bonus.c $Bfind_wall_dist_utils_bonus.c \
		$Bget_intersection_door_y_bonus.c \
		$Bdoor_animation_bonus.c $Bcount_open_doors_bonus.c $Bdraw_open_door_utils_bonus.c \
		$Bdraw_open_door_px_bonus.c $Bopen_door_action_bonus.c \
		$Banimation_hooks_bonus.c \
		$Bget_animation_images_bonus.c \
		$Brotation_bonus.c \
		$Benemy_put_pixel_bonus.c $Bget_enemy_px_bonus.c \
		$Benemy_movement_bonus.c $Benemy_movement_utils_bonus.c \
		$Bprint_help_bonus.c \
		$Bdeath_exit_bonus.c $Butils_2_bonus.c \
		$Bstart_menu_bonus.c $Bget_images_utils_bonus.c \
		$Bmap_exit_bonus.c

BONOBJS	= ${BONSRCS:.c=.o}

all: $(LIBMLX) $(LIBFT) $(NAME)

$(LIBMLX):
	cmake ./lib/MLX42 -B ./lib/MLX42/build && make -C ./lib/MLX42/build -j4

$(LIBFT):
	make -C ./lib/libft/.

$(NAME): $(OBJS)
	$(CC) $(OBJS) $(LIBS) $(HEADERS) -o $(NAME)

bonus: .bonus

.bonus: $(LIBMLX) $(LIBFT) $(BONOBJS)
	$(CC) $(BONOBJS) $(LIBS) $(HEADERS) -o $(NAME)
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

