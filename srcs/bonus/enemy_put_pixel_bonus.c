#include "cubed_bonus.h"

void	get_dead_enemy_pixels(t_data *data, int i)
{
	int			k;
	long long	x;
	long long	y;

	x = data->enemy[i].x / IMG_SIZE;
	y = data->enemy[i].y / IMG_SIZE;
	k = data->enemy[i].dead_anim_iter;
	if (k > 4)
		k = 4;
	data->pixels = data->enemy_dead_img[k]->pixels;
	if (k == 4)
	{
		data->map[y][x].is_enemy = 0;
		data->enemy[i].is_dead = 1;
		data->enemy[i].x = -1;
		data->enemy[i].y = -1;
	}
}

void	get_enemy_pixels(t_data *data, int i, double enemy_player_angle)
{
	if (data->enemy[i].is_dying == 1)
	{
		get_dead_enemy_pixels(data, i);
		return ;
	}
	if (enemy_player_angle > 315 || enemy_player_angle <= 45)
		get_enemy_px_up(data, i);
	else if (enemy_player_angle > 45 && enemy_player_angle <= 135)
		get_enemy_px_right(data, i);
	else if (enemy_player_angle > 135 && enemy_player_angle <= 225)
		get_enemy_px_down(data, i);
	else
		get_enemy_px_left(data, i);
}

int	colour_enemy_pixel(t_data *data, long long *s_coord, int px_counter, int i)
{
	int		colour;
	uint8_t	*pixels;

	pixels = data->pixels;
	if (*s_coord < 0)
		*s_coord = 0;
	else if (*s_coord > WINDOW_HEIGHT)
		*s_coord = 0;
	colour = get_rgba(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
	if (pixels[i + 3] > 150)
		mlx_put_pixel(data->door_canvas, data->ray_iterator, *s_coord, colour);
	*s_coord += 1;
	return (px_counter + 1);
}

int	enemy_draw_execute(t_data *data, int i, double e_height, long long s_coord)
{
	int		px_cnt;
	double	pixel_iter;

	px_cnt = 0;
	pixel_iter = 0.0;
	while (i < (ENEMY_WIDTH * ENEMY_HEIGHT * 4) && px_cnt < WINDOW_HEIGHT)
	{
		if (s_coord < 0)
			s_coord++;
		else
			px_cnt = colour_enemy_pixel(data, &s_coord, px_cnt, i);
		pixel_iter += (ENEMY_HEIGHT / e_height);
		if (pixel_iter > 1)
		{
			while (pixel_iter > 1)
			{
				pixel_iter -= 1;
				i += (ENEMY_WIDTH * 4);
			}
		}
	}
	return (s_coord);
}

int	get_column(double *enemy_limits, double ray_angle)
{
	int				column;
	double			column_width;

	column_width = (enemy_limits[1] - enemy_limits[0]) / ENEMY_WIDTH;
	column = (ray_angle - enemy_limits[0]) / column_width;
	return (column);
}
