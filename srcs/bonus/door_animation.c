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
		draw_image(data);
		if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
			error_exit(data, mlx_strerror(mlx_errno), 1);
		mlx_set_instance_depth(&data->game_img->instances[0], 1);
		prev_time = time;
	}
}
