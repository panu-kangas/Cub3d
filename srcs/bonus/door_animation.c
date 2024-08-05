#include "cubed_bonus.h"

void	door_opening_anim(t_data *data, long long x, long long y)
{
	int				iter_dir;
	double			prev_time;
	double			time;

	if (data->map[y][x].is_open == 0)
	{
		data->map[y][x].type = '0';
		data->map[y][x].is_open = 1;
		data->door_open_iter = 0;
		iter_dir = 1;
	}
	else
		iter_dir = -1;

//	printf("x=%lld, y=%lld\n", x, y);
//	printf("BEFORE 1 draw: type: %c, is_open: %d, door_open_iter: %d, iter_dir: %d\n\n", \
//	data->map[y][x].type, data->map[y][x].is_open, data->door_open_iter, iter_dir);

	delete_and_init_images(data);
	draw_image(data, data->player_angle - 30, WINDOW_WIDTH);

	time = mlx_get_time();
	prev_time = time;
	while (time < prev_time + 0.2)
		time = mlx_get_time();

	data->door_open_iter += iter_dir;
	delete_and_init_images(data);
	draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
	prev_time = time;

	while (time < prev_time + 0.2)
		time = mlx_get_time();

	data->door_open_iter += iter_dir;
	delete_and_init_images(data);
	draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
	prev_time = time;

//	data->map[y][x].is_opening = 0;

	while (time < prev_time + 0.3)
		time = mlx_get_time();

	if (data->door_open_iter == 0)
	{
		data->map[y][x].type = '1';
		data->map[y][x].is_open = 0;
		delete_and_init_images(data);
		draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
	}
	data->door_open_iter = 2;

	
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
		delete_and_init_images(data);
		draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
		prev_time = time;
	}
}
