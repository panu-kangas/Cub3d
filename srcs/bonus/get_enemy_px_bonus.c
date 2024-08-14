#include "cubed_bonus.h"

void	get_enemy_px_left(t_data *data, int i)
{
	if (data->enemy[i].direction == 0)
		data->pixels = data->enemy_img[3]->pixels;
	else if (data->enemy[i].direction == 1)
		data->pixels = data->enemy_img[0]->pixels;
	else if (data->enemy[i].direction == 2)
		data->pixels = data->enemy_img[1]->pixels;
	else if (data->enemy[i].direction == 3)
		data->pixels = data->enemy_img[2]->pixels;
}

void	get_enemy_px_down(t_data *data, int i)
{
	if (data->enemy[i].direction == 0)
		data->pixels = data->enemy_img[0]->pixels;
	else if (data->enemy[i].direction == 1)
		data->pixels = data->enemy_img[1]->pixels;
	else if (data->enemy[i].direction == 2)
		data->pixels = data->enemy_img[2]->pixels;
	else if (data->enemy[i].direction == 3)
		data->pixels = data->enemy_img[3]->pixels;
}

void	get_enemy_px_right(t_data *data, int i)
{
	if (data->enemy[i].direction == 0)
		data->pixels = data->enemy_img[1]->pixels;
	else if (data->enemy[i].direction == 1)
		data->pixels = data->enemy_img[2]->pixels;
	else if (data->enemy[i].direction == 2)
		data->pixels = data->enemy_img[3]->pixels;
	else if (data->enemy[i].direction == 3)
		data->pixels = data->enemy_img[0]->pixels;
}

void	get_enemy_px_up(t_data *data, int i)
{
	if (data->enemy[i].direction == 0)
		data->pixels = data->enemy_img[2]->pixels;
	else if (data->enemy[i].direction == 1)
		data->pixels = data->enemy_img[3]->pixels;
	else if (data->enemy[i].direction == 2)
		data->pixels = data->enemy_img[0]->pixels;
	else if (data->enemy[i].direction == 3)
		data->pixels = data->enemy_img[1]->pixels;
}
