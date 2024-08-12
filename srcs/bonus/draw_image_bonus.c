#include "cubed_bonus.h"

void	execute_drawing(t_data *data, int column, double wall_height)
{
	int				i;
	long long		start_coord;
	int				ray_iter;
	int				fl_colour;

	i = 0;
	ray_iter = data->ray_iterator;
	fl_colour = data->fl_colour;
	start_coord = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	while (start_coord > 0 && i < start_coord)
		mlx_put_pixel(data->game_img, ray_iter, i++, data->ceil_colour);
	start_coord = draw_wall(data, (column * 4), wall_height, start_coord);
	while (start_coord < WINDOW_HEIGHT)
		mlx_put_pixel(data->game_img, ray_iter, start_coord++, fl_colour);
	data->door_found_vert = 0;
	data->door_found_horiz = 0;
	data->found_open_door_vert = 0;
	data->found_open_door_horiz = 0;
}

char	get_closed_door_direction(t_data *data)
{
	char	direction;

	if (data->v_h_flag == 0 \
	&& data->player_coord[0] > data->vert_inters_crd[0])
		direction = 'W';
	else if (data->v_h_flag == 0)
		direction = 'E';
	else if (data->v_h_flag == 1 \
	&& data->player_coord[1] > data->horiz_inters_crd[1])
		direction = 'N';
	else
		direction = 'S';
	return (direction);
}

void	get_closed_door_pixels(t_data *data)
{
	char	direction;

	direction = get_closed_door_direction(data);
	if (data->door_found_vert == 1)
	{
		if (direction == 'W')
			data->pixels = \
			data->door_closed_img[data->door_idle_iter][3]->pixels;
		else
			data->pixels = \
			data->door_closed_img[data->door_idle_iter][1]->pixels;
	}
	else if (data->door_found_horiz == 1)
	{
		if (direction == 'N')
			data->pixels = \
			data->door_closed_img[data->door_idle_iter][0]->pixels;
		else
			data->pixels = \
			data->door_closed_img[data->door_idle_iter][2]->pixels;
	}
}

void	draw_pixels(t_data *data, double wall_height)
{
	int		column_to_draw;

	if (data->v_h_flag == 0)
	{
		if (data->player_coord[0] > data->vert_inters_crd[0])
			data->pixels = data->wall_img_w->pixels;
		else
			data->pixels = data->wall_img_e->pixels;
		if (data->door_found_vert == 1)
			get_closed_door_pixels(data);
		column_to_draw = (int)data->vert_inters_crd[1] % IMG_SIZE;
	}
	else
	{
		if (data->player_coord[1] > data->horiz_inters_crd[1])
			data->pixels = data->wall_img_n->pixels;
		else
			data->pixels = data->wall_img_s->pixels;
		if (data->door_found_horiz == 1)
			get_closed_door_pixels(data);
		column_to_draw = (int)data->horiz_inters_crd[0] % IMG_SIZE;
	}
	execute_drawing(data, column_to_draw, wall_height);
}

void	draw_image(t_data *data, double ray_angle, double window_width)
{
	double		dist_to_wall;
	double		drawn_wall_height;
	double		addition;

	if (ray_angle < 0)
		ray_angle = 360 - (ray_angle * -1);
	data->ray_iterator = 0;
	addition = 60.0 / window_width;
	while (data->ray_iterator < WINDOW_WIDTH)
	{
		dist_to_wall = find_wall_distance(data, ray_angle, addition);
		data->dist_to_wall_list[data->ray_iterator] = dist_to_wall;
		drawn_wall_height = (IMG_SIZE / dist_to_wall) * PP_DIST;
		draw_pixels(data, drawn_wall_height);
		data->ray_iterator++;
		ray_angle = ray_angle + addition;
		if (ray_angle > 360)
			ray_angle = 0;
	}
	draw_open_door(data, data->player_angle - 30.0, WINDOW_WIDTH);
	draw_minimap(data);
	put_images_to_window(data);
	mlx_set_cursor_mode(data->mlx, MLX_MOUSE_HIDDEN);
	mlx_set_mouse_pos(data->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
	draw_enemy_loop(data);
}
