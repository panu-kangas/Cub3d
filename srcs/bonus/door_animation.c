#include "cubed_bonus.h"

void	door_opening_anim(t_data *data)
{
	int				iter_dir;
	long long		x;
	long long		y;

	x = 0;
	y = 0;
	iter_dir = 0;
	x = data->opening_door_coord[0];
	y = data->opening_door_coord[1];

	if (data->map[y][x].is_opening == 1)
	{
		data->map[y][x].type = '0';
		data->map[y][x].is_open = 1;
		iter_dir = 1;
	}
	else if (data->map[y][x].is_closing == 1)
		iter_dir = -1;

	data->map[y][x].open_img_iter += iter_dir;

	if (data->map[y][x].open_img_iter == 2)
	{
		data->opening_in_action = 0;
		data->map[y][x].is_opening = 0;
	}
	else if (data->map[y][x].open_img_iter == -1)
	{
		data->map[y][x].type = '1';
		data->map[y][x].is_open = 0;
		data->opening_in_action = 0;
		data->map[y][x].is_closing = 0;
	}
}

void	door_idle_anim(t_data *data)
{
	static int		iter_dir;

	if (iter_dir == 0)
		iter_dir = 1;
	data->door_idle_iter += iter_dir;
	if (data->door_idle_iter == 4)
	{
		data->door_idle_iter--;
		iter_dir = -1;
	}
	else if (data->door_idle_iter == -1)
	{
		data->door_idle_iter++;
		iter_dir = 1;
	}
}

void	door_animation(void *param)
{
	t_data			*data;
	static double	prev_time;
	double			time;

	data = param;
	time = mlx_get_time();

	if (time > prev_time + 0.2) // add ending flag here
	{
		door_idle_anim(data);
		if (data->opening_in_action == 1)
			door_opening_anim(data);
		delete_and_init_images(data);
		draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
		prev_time = time;
	}
} 
