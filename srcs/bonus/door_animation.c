#include "cubed_bonus.h"

void	door_animation(void *param)
{
	t_data			*data;
	static double	prev_time;
	double			time;
	static int		iter_dir;

	data = param;
	time = mlx_get_time();
	if (iter_dir == 0)
		iter_dir = 1;

	if (time > prev_time + 0.2) // add ending flag here
	{
		data->door_iter += iter_dir;
		if (data->door_iter == 4)
		{
			data->door_iter--;
			iter_dir = -1;
		}
		else if (data->door_iter == -1)
		{
			data->door_iter++;
			iter_dir = +1;
		}
		delete_and_init_images(data);
		draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
		prev_time = time;
	}
}
