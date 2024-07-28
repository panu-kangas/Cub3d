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
		$(MAND)/draw_image.c $(MAND)/find_wall_distance.c $(MAND)/get_images.c $(MAND)/keyhook.c
OBJS	= ${SRCS:.c=.o}

BONSRCS	= 
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

