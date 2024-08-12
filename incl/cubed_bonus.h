/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed_bonus.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:18:06 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/09 13:22:33 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_BONUS_H
# define CUBED_BONUS_H

# include <unistd.h> // open
# include <fcntl.h> // open flags
# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc

# include <math.h>
# include <time.h> // just as test

# include <MLX42/MLX42.h>
# include "libft.h"

# define WINDOW_WIDTH 800 // Panu's laptop: 800 // At school: 1600
# define WINDOW_HEIGHT 600 // Panu's laptop: 600 // At school: 1200

# define IMG_SIZE 128 // 64 x 64 pixels --> NOTE: We might need bigger images for school, because on bigger game window the images strech out a lot!
# define PI 3.14159265358979323846 // Not the dessert... sadly
# define PP_DIST 300 // Projection Plane Distance, 255 is recommendation
# define PLAYER_SPEED 8 // VALUE SUGGESTION FOR SCHOOL: 6-8 // move X pixels per keypress
# define PLAYER_TURN_SPEED 3 // VALUE SUGGESTION FOR SCHOOL: 3 // X degrees change to angle per keypress
# define MOUSE_SENS 0.05
# define WALL_LIMIT 40 // you can't get closer to aa wall than WALL_LIMIT -amount of pixels


# define MINIMAP_WIDTH 176 // At school: 275 = MINIMAP_IMG_SIZE * TILE_COUNT (25 * 11) // Panu laptop: 176 = MINIMAP_IMG_SIZE * TILE_COUNT (16 * 11)
# define MINIMAP_HEIGHT	176 // At school: 275 // Panu laptop: 176
# define MINIMAP_IMG_SIZE 16 // At school: 25 // Panu laptop: 16
# define MINIMAP_TILE_COUNT 11

# define ENEMY_WIDTH 	80
# define ENEMY_HEIGHT	80

# define VALIDCHARS "01 NEWSDA"
# define VALIDMAPCHARS "01XNEWSDA"
# define AREACHARS "0NEWSDA"
# define PLAYER "SNEW"

# define WS0 "./sprites/gun/shtg/ws0.png"
# define WS1 "./sprites/gun/shtg/ws1.png"
# define WS2 "./sprites/gun/shtg/ws2.png"
# define WS3 "./sprites/gun/shtg/ws3.png"
# define WS4 "./sprites/gun/shtg/ws4.png"
# define WS5 "./sprites/gun/shtg/ws5.png"
# define W_S_COUNT 6
# define ANIM_DELAY 0.1
# define SP_WIDTH 238
# define SP_HEIGHT 308
// w: 238, h: 308 max

typedef struct s_map
{
	char	type; // wall ('1'), empty space('0'), player ('P') etc
	int		is_door; // 0 or no door, 1 for door
	int		is_open; // 0 for closed, 1 for open
	int		is_opening;
	int		is_closing;
	int		open_img_iter;
	int		is_enemy;
}			t_map;

typedef struct s_enemy
{
	long long	x; // the x and y coordinates
	long long	y;
	int			direction; // for now, 0 north, 1 east, 2 south, 3 west
	int			step_count;
	int			is_dying;
	int			is_dead;
	int			dead_anim_iter;
	double		angle_to_player;
	double		distance_to_player;
	double		prev_time;
	double		prev_dead_time;
	int			enemy_anim_height_iter;
}			t_enemy;

typedef struct s_color
{
	int		r;
	int		g;
	int		b;
}			t_color;

typedef struct s_anim
{
	int			has_shot;
	int			frame_num;
	int			frame_count;
	double		timer;
	double		delay;
	mlx_image_t	*canvas;
	mlx_image_t	**sprites;
}			t_anim;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*game_img;

	mlx_image_t	*wall_img_n; // Northern wall image
	mlx_image_t	*wall_img_e; // etc...
	mlx_image_t	*wall_img_s;
	mlx_image_t	*wall_img_w;

	mlx_image_t	*door_closed_img[4][4];
	mlx_image_t	*door_open_img[3][4];
	mlx_image_t *door_canvas;

	mlx_image_t	*death_img;
	mlx_image_t	*death_text_img;

	int			door_idle_iter;
	int			opening_in_action;
	long long	opening_door_coord[2];

	mlx_image_t *player_icon;
	mlx_image_t *enemy_img[4];
	mlx_image_t	*enemy_dead_img[5];
	mlx_image_t *text;

	uint8_t		*pixels; // pixel data of a single wall
	uint8_t		*pixels_door; // pixel data of a single wall


	t_map		**map;

	t_enemy		*enemy;
	int			*draw_order;
	int			enemy_iter;
//	int			enemy_anim_height_iter;
	int			enemy_anim_img_iter;
	int			shooting;
	int			is_dead;
	double		time;
//	int			enemy_start_visible;
//	int			enemy_end_visible;

	int			ceil_colour; // ceiling colour
	int			fl_colour; // floor colour
	int			v_h_flag; // vertical intersection found wall = 0, horizontal intersection = 1 (used in find_wall_distance.c)
	int			invalid_vert;
	int			invalid_horiz;

	int			door_found_vert;
	long long	door_coord_v[2];
	int			door_found_horiz;
	long long	door_coord_h[2];

	long long	open_door_coord_vert[2];
	long long	open_door_coord_horiz[2];
	int			handling_open_door;
	int			found_open_door_vert;
	int			found_open_door_horiz;

	int			ray_iterator;
	double		vert_inters_crd[2];
	double		horiz_inters_crd[2];
	double		checking_door_coord[2];
	double		dist_to_wall_list[WINDOW_WIDTH];

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
	int			enemy_count;
	t_anim		anim;
	int			show_menu;
	mlx_image_t	*menu_img;
	mlx_image_t	*menu_canvas;
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

void    get_images(t_data *data);
void	draw_image(t_data *data, double ray_angle, double window_width);
double	find_wall_distance(t_data *data, double ray_angle, double addition);
void	get_vert_intersection(t_data *data, double ray_angle, \
long long *w_coord, int cnt);
void	get_horizon_intersection(t_data *data, double ray_angle, \
long long *w_coord, int cnt);
double	compare_distance(t_data *data, double ray_angle);
int		draw_wall(t_data *data, int i, double wall_height, long long start_coord);
void	print_to_screen(t_data *data);


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

void		keyhook(void *param);
void		key_action_w(t_data *data);
void		key_action_a(t_data *data);
void		key_action_s(t_data *data);
void		key_action_d(t_data *data);
int			check_for_collision(t_data *data, double direction);
void		special_keys(mlx_key_data_t keydata, void *param);
void		rotation(double x_pos, t_data *data);

// UTILS

double  convert_to_radians(double angle_in_degrees);
double	convert_to_degrees(double angle_in_rad);
void	print_goodbye_message(void);
int 	get_rgba(int r, int g, int b, int a);
void	delete_and_init_images(t_data *data);
void	death_exit(t_data *data);
void	put_images_to_window(t_data *data);

// MINIMAP FUNCTIONS

void	draw_minimap(t_data *data);
void	draw_player_icon(t_data *data);

// ENEMY FUNCTIONS

void	init_enemies(t_data *data);
void	enemy_handler(void *param);
void    draw_enemy_loop(t_data *data);
int		get_column(double *enemy_limits, double ray_angle);
void	enemy_movement(t_data *data, int i);
void	get_enemy_pixels(t_data *data, int i, double enemy_player_angle);
void	enemy_to_screen(t_data *data, double drawn_enemy_height, \
double enemy_player_angle, double dist_to_enemy);
double	handle_exception(t_data *data, double *xy_diff, double *enemy_player_angle, double *p_fov_limits);
int		enemy_draw_execute(t_data *data, int i, \
double drawn_enemy_height, long long start_coord);
void	get_draw_order(t_data *data);


// ENEMY DRAW UTILS

int		get_ray_iterator(double enemy_start_angle, double player_fov_start);
void	set_player_fov(t_data *data, double *player_fov_limits);
void	set_enemy_limits(double *enemy_limits, double enemy_player_angle, \
double dist_to_enemy);
void	skip_extra_rays(t_data *data, double *ray_angle, double addition);
void	get_xy_diff(t_data *data, int i, double *x_diff, double *y_diff);
void	fix_fov_limits(t_data *data, double *enemy_player_angle, \
double *p_fov_limits);
double	handle_y_is_zero(t_data *data, double *enemy_player_angle, \
double *p_fov_limits);
double	handle_xy_exception(t_data *data, double *xy_diff, \
double *enemy_player_angle, double *p_fov_limits);


// DOOR FUNCTIONS

void	door_animation(void *param);
void	init_door_canvas(t_data *data);
void	fix_door_img(mlx_image_t *door_img, mlx_image_t *wall_img);
void	draw_open_door(t_data *data, double ray_angle, double window_width);
int		find_open_door_iter(t_data *data);
int		check_for_door(t_data *data, long long x, long long y);

long long	get_up_right_door_y(long long *t_coord, double *start_coord, double ray_angle);
long long	get_down_right_door_y(t_data *data, long long *t_coord, double *start_coord, double ray_angle);
long long	get_down_left_door_y(t_data *data, long long *t_coord, double *start_coord, double ray_angle);
long long	get_up_left_door_y(long long *t_coord, double *start_coord, double ray_angle);

long long	get_up_right_door_x(t_data *data, long long *t_coord, double *start_coord, double ray_angle);
long long	get_down_right_door_x(t_data *data, long long *t_coord, double *start_coord, double ray_angle);
long long	get_down_left_door_x(long long *t_coord, double *start_coord, double ray_angle);
long long	get_up_left_door_x(long long *t_coord, double *start_coord, double ray_angle);

int		check_if_ray_hits_door_vert(t_data *data, double ray_angle);
int		check_if_ray_hits_door_horiz(t_data *data, double ray_angle);



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

//ANIMATION
void		init_gun_animation(t_anim *anim, t_data *data);
void		animate(void *param);
void		menu_key_hook(mlx_key_data_t keydata, void *param);
void		init_menu_img(t_data *data);
uint32_t	get_pixel(mlx_image_t *sprite, uint32_t x, uint32_t y);

// DEBUGGING REMOVE THESE

void		print_map_lines(t_data *data);
void		print_map(t_data *data);
void		print_info(t_data *data);
void		print_data(t_data *data);

#endif
