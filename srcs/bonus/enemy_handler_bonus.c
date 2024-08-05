#include "cubed_bonus.h"

void	enemy_animation(t_data *data)
{

	if (data == NULL)
		return ;
/*	int	i;

	i = 0;
//	game->e_count = 0;
	mlx_delete_image(game->mlx, game->enemy_img[game->enemy_img_i]);
	game->enemy_img_i += 1;
	if (game->enemy_img_i == 6)
		game->enemy_img_i = 0;
	set_enemy_image(game, game->enemy_img_i);
	while (i < game->enemy_count)
	{
		if (game->enemies[i].is_dying == 0)
			enemy_movement(game, i);
		i++;
	} */
}

void	enemy_handler(void *param)
{
	t_data			*data;
	static double	prev_time;
//	static double	prev_dead_time;
	double			time;
//	int				i;

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
	if (time > prev_time + 0.4) // add ending flag here
	{
		enemy_animation(data); // or just change enemy_img, and then in draw_functions do the actual drawing pixel by pixel...?
		prev_time = time;
	}
}