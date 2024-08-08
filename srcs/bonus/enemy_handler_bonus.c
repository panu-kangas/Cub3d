#include "cubed_bonus.h"

void	enemy_animation(t_data *data, int *height_dir)
{
	int			i;
	long long	x;
	long long	y;


	if (data->enemy_anim_height_iter == 20)
		*height_dir = -1;
	else if (data->enemy_anim_height_iter == -10)
		*height_dir = 1;
	data->enemy_anim_height_iter += (5 * *height_dir);


//	game->e_count = 0;
//	mlx_delete_image(game->mlx, game->enemy_img[game->enemy_img_i]);
//	game->enemy_img_i += 1;
//	if (game->enemy_img_i == 6)
//		game->enemy_img_i = 0;
//	set_enemy_image(game, game->enemy_img_i);
	i = 0;
	while (i < data->enemy_count)
	{
		x = data->enemy[i].x / IMG_SIZE;
		y = data->enemy[i].y / IMG_SIZE;
		data->map[y][x].is_enemy = 0;
//		if (data->enemy[i].is_dying == 0)
			enemy_movement(data, i);
		x = data->enemy[i].x / IMG_SIZE;
		y = data->enemy[i].y / IMG_SIZE;
		data->map[y][x].is_enemy = 1;
		i++;
	}
}

void	enemy_handler(void *param)
{
	t_data			*data;
	static double	prev_time;
	double			time;
	static int		height_dir;


	data = param;
	time = mlx_get_time();
//	i = 0;
/*	if (time > prev_dead_time + 0.2) // add ending flag here
	{
		new_enemy_img(game);
		while (i < game->enemy_count)
		{
			if (game->enemies[i].is_dying == 1 && game->enemies[i].is_dead == 0)
				enemy_dead_animation(game, i);
			i++;
		}
		prev_dead_time = time;
	} */
	if (time > prev_time + 0.2) // add ending flag here
	{
		enemy_animation(data, &height_dir);
		prev_time = time;
	}
}