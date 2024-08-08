#include "cubed_bonus.h"

void	enemy_animation(t_data *data, int i, int *height_dir)
{
	long long	x;
	long long	y;

	if (data->enemy_anim_height_iter == 20)
		*height_dir = -1;
	else if (data->enemy_anim_height_iter == -10)
		*height_dir = 1;
	data->enemy_anim_height_iter += (5 * *height_dir);
	x = data->enemy[i].x / IMG_SIZE;
	y = data->enemy[i].y / IMG_SIZE;
	data->map[y][x].is_enemy = 0;
	enemy_movement(data, i);
	x = data->enemy[i].x / IMG_SIZE;
	y = data->enemy[i].y / IMG_SIZE;
	data->map[y][x].is_enemy = 1;
}

void	enemy_handler(void *param)
{
	t_data			*data;
	static double	prev_time;
	static double	prev_dead_time;
	double			time;
	static int		height_dir;
	int				i;

	data = param;
	time = mlx_get_time();
	i = -1;
	while (++i < data->enemy_count)
	{
		if (time > prev_dead_time + 0.2)
		{
			if (data->enemy[i].is_dying == 1)
				data->enemy[i].dead_anim_iter += 1;
			prev_dead_time = time;
		}
		if (time > prev_time + 0.15)
		{
			if (data->enemy[i].is_dying == 0 && data->enemy[i].is_dead == 0)
				enemy_animation(data, i, &height_dir);
			prev_time = time;
		}
	}
}
