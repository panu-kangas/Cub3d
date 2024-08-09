#include "cubed_bonus.h"

void	check_for_shot(t_data *data)
{
	int		i;
	double	p_angle;
	double	shot_limits[2];

	if (data->shooting == 0)
		return ;
	i = 0;
	while (i < data->enemy_count)
	{
		p_angle = data->player_angle;
		if (p_angle > 270 && data->enemy[i].angle_to_player < 90)
			p_angle -= 360;
		else if (p_angle < 90 && data->enemy[i].angle_to_player > 270)
			p_angle += 360;

		shot_limits[0] = p_angle - 10.0;
		shot_limits[1] = p_angle + 10.0;

		if (data->enemy[i].distance_to_player > 0.0 \
		&& data->enemy[i].distance_to_player < 600.0 \
		&& data->enemy[i].angle_to_player >= shot_limits[0] \
		&& data->enemy[i].angle_to_player <= shot_limits[1])
			data->enemy[i].is_dying = 1;
		i++;
	}
	data->shooting = 0;
}

void	enemy_animation(t_data *data, int i, int *height_dir)
{
	long long	x;
	long long	y;
	double		height_add;
	double		height_max;
	double		height_min;

	if (data->enemy[i].distance_to_player < 1000.0)
	{
		height_add = 5;
		height_max = 15;
		height_min = -10;
	}
	else
	{
		height_add = 1;
		height_max = 3;
		height_min = -2;
	}

	if (data->enemy_anim_height_iter >= height_max)
		*height_dir = -1;
	else if (data->enemy_anim_height_iter <= height_min)
		*height_dir = 1;
	data->enemy_anim_height_iter += (height_add * *height_dir);
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
	static int		height_dir;
	int				i;

	data = param;
	if (data->is_dead == 1)
		return ;
	data->time = mlx_get_time();
	check_for_shot(data);
	i = -1;
	while (++i < data->enemy_count)
	{
		if (data->time > prev_dead_time + 0.2)
		{
			if (data->enemy[i].is_dying == 1)
				data->enemy[i].dead_anim_iter += 1;
			prev_dead_time = data->time;
		}
		if (data->time > prev_time + 0.15)
		{
			if (data->enemy[i].is_dying == 0 && data->enemy[i].is_dead == 0)
				enemy_animation(data, i, &height_dir);
			prev_time = data->time;
		}
		if (data->enemy[i].dead_anim_iter > 4)
		{
			data->enemy[i].is_dead = 1;
			data->map[data->enemy[i].y / IMG_SIZE][data->enemy[i].x / IMG_SIZE].is_enemy = 0;
		}
	}
}
