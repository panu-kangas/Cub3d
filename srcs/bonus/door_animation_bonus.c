#include "cubed_bonus.h"

void	door_opening_anim(t_data *data, int iter_dir)
{
	long long		xy[2];

	xy[0] = data->opening_door_coord[0];
	xy[1] = data->opening_door_coord[1];
	if (data->map[xy[1]][xy[0]].is_opening == 1)
	{
		data->map[xy[1]][xy[0]].type = '0';
		data->map[xy[1]][xy[0]].is_open = 1;
		iter_dir = 1;
	}
	else if (data->map[xy[1]][xy[0]].is_closing == 1)
		iter_dir = -1;
	data->map[xy[1]][xy[0]].open_img_iter += iter_dir;
	if (data->map[xy[1]][xy[0]].open_img_iter == 2)
	{
		data->opening_in_action = 0;
		data->map[xy[1]][xy[0]].is_opening = 0;
	}
	else if (data->map[xy[1]][xy[0]].open_img_iter == -1)
	{
		data->map[xy[1]][xy[0]].type = '1';
		data->map[xy[1]][xy[0]].is_open = 0;
		data->opening_in_action = 0;
		data->map[xy[1]][xy[0]].is_closing = 0;
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

	data = param;
	if (data->is_dead == 1)
		return ;
	data->time = mlx_get_time();
	print_to_screen(data);
	if (data->time > prev_time + 0.2)
	{
		door_idle_anim(data);
		if (data->opening_in_action == 1)
			door_opening_anim(data, 0);
		delete_and_init_images(data);
		draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
		prev_time = data->time;
	}
}
