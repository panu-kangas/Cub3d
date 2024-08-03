/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:18:06 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/03 15:54:51 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_BONUS_H
# define CUBED_BONUS_H

# include <unistd.h> // open
# include <fcntl.h> // open flags
# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc

# include <math.h>

# include <MLX42/MLX42.h>
# include "libft.h"

# define WINDOW_WIDTH 800 // 1920
# define WINDOW_HEIGHT 600 // 1080
# define IMG_SIZE 64 // 64 x 64 pixels
# define PI 3.14159265358979323846 // Not the dessert... sadly
# define PP_DIST 255 // Projection Plane Distance, 255 is recommendation
# define PLAYER_SPEED 14 // move X pixels per keypress
# define PLAYER_TURN_SPEED 9 // X degrees change to angle per keypress

# define MINIMAP_WIDTH 176 // IMG_SIZE * TILE_COUNT (16 * 11)
# define MINIMAP_HEIGHT	176
# define MINIMAP_IMG_SIZE 16
# define MINIMAP_TILE_COUNT 11

# define VALIDCHARS "01 NEWSDA"
# define VALIDMAPCHARS "01XNEWSDA"
# define AREACHARS "0NEWSDA"

typedef struct s_map
{
	char	type; // wall ('1'), empty space('0'), player ('P') etc
	int		is_door;
}			t_map;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*game_img;

	mlx_image_t	*wall_img_n; // Northern wall image
	mlx_image_t	*wall_img_e; // etc...
	mlx_image_t	*wall_img_s;
	mlx_image_t	*wall_img_w;
	mlx_image_t	*player_icon;

	uint8_t		*pixels; // pixel data of a single wall
	t_map		**map;

	int			ceil_colour; // ceiling colour
	int			fl_colour; // floor colour
	int			v_h_flag; // vertical intersection found wall = 0, horizontal intersection = 1 (used in find_wall_distance.c)
	int			ray_iterator;
	double		vert_intersection_coord[2];
	double		horizon_intersection_coord[2];
	int			map_height;
	int			map_width;
	long long	player_coord[2]; // x and y coord of the player in px
	double		player_angle; // 0=N, 90=E, 180=S, 270=W. 360 is again 0.
	char		*map_name;
	int			player_x_pos;
	int			player_y_pos;
	int			player_flag;
	char		*texture_path_n;
	char		*texture_path_e;
	char		*texture_path_s;
	char		*texture_path_w;
	char		**map_lines;
	char		**file;
	int			info_lines_count;
	int			file_height;
	t_color		*ceiling_color;
	t_color		*floor_color;
	int			map_start;
	int			cc;
	int			fc;
}			t_data;

// ERROR HANDLING

void		error_exit(t_data *data, const char *err_str, int init_flag);
void		sys_error_exit(t_data *data, char *err_str, int mlx_flag);
void		success_exit(t_data *data);

// FREE FUNCTIONS

char		*ft_strdup_nonl(const char *s1);
void		free_2d_array_len(char **strs, int len);
void		free_data(t_data *data);
void		free_map(t_data *data);

// MAP HANDLING

void		get_map(t_data *data, char *map_name);
void		change_spaces_to_x(t_data *data);

// IMAGE DRAWING

void		get_images(t_data *data);
void		draw_image(t_data *data);
double		find_wall_distance(t_data *data, double ray_angle, double addition);
double		compare_distance(t_data *data, double ray_angle, \
long long *vert_coord, long long *horizon_coord);
int			draw_wall(t_data *data, int i, double wall_height, int start_coord);

// INTERSECTION MATH HELPERS

long long	get_up_right_x(t_data *data, long long *t_coord, double ray_angle);
long long	get_down_right_x(t_data *data, \
	long long *t_coord, double ray_angle);
long long	get_down_left_x(t_data *data, long long *t_coord, double ray_angle);
long long	get_up_left_x(t_data *data, long long *t_coord, double ray_angle);
long long	get_up_right_y(t_data *data, long long *t_coord, double ray_angle);
long long	get_down_right_y(t_data *data, \
	long long *t_coord, double ray_angle);
long long	get_down_left_y(t_data *data, long long *t_coord, double ray_angle);
long long	get_up_left_y(t_data *data, long long *t_coord, double ray_angle);

// HOOK FUNCTIONS

void		keyhook(mlx_key_data_t keydata, void *param);
void		key_action_w(t_data *data);
void		key_action_a(t_data *data);
void		key_action_s(t_data *data);
void		key_action_d(t_data *data);
int			check_for_collision(t_data *data, double direction);

// UTILS

double		convert_to_radians(double angle_in_degrees);
void		print_goodbye_message(void);
int			get_rgba(int r, int g, int b, int a);
void		delete_and_init_images(t_data *data);

// MINIMAP FUNCTIONS

void		draw_minimap(t_data *data);
void		draw_player_icon(t_data *data);

/* VALIDATION */

int			get_texture_paths(t_data *data);
int			is_map_valid(t_data *data, char *map_name);
int			check_texture_paths(t_data *data);
int			assign_map_contents(t_data *data);
void		allocate_map(t_data *data);
int			check_map_borders(t_data *data);
void		get_widest_width(t_data *data);
void		check_map_syntax(t_data *data);
int			check_path_lines(t_data *data, int i, int no_flag, int so_flag);
int			check_color_lines(t_data *data);
void		validate_door_and_enemy_positions(t_data *data, int i, int j);

// DEBUGGING REMOVE THESE

void		print_map_lines(t_data *data);
void		print_map(t_data *data);
void		print_info(t_data *data);
void		print_data(t_data *data);

#endif
