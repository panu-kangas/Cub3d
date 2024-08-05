#include "cubed_bonus.h"

int	change_door_stat(t_data *data, long long x, long long y)
{
	if (data->map[y][x].is_door == 1 && data->map[y][x].is_open == 0)
		door_opening_anim(data, x, y);
	else if (data->map[y][x].is_door == 1 && data->map[y][x].is_open == 1) // we don't need this...?
		door_opening_anim(data, x, y);
	return (1);
}

int	check_for_door(t_data *data, long long x, long long y)
{
	double	angle;

	angle = data->player_angle;
	if (angle >= 340 || angle <= 20)
		return (change_door_stat(data, x, y - 1));
	else if (angle >= 70 && angle <= 110)
		return (change_door_stat(data, x + 1, y));
	else if (angle >= 160 && angle <= 200)
		return (change_door_stat(data, x, y + 1));
	else if (angle >= 250 && angle <= 290)
		return (change_door_stat(data, x - 1, y));
	return (0);
}

void	open_door(t_data *data)
{
	long long	x;
	long long	y;

	x = data->player_coord[0] / IMG_SIZE;
	y = data->player_coord[1] / IMG_SIZE;

	if (check_for_door(data, x, y) == 1)
	{
		// delete_and_init_images(data);
		// draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
	}
}

void	key_action_left(t_data *data)
{
	data->player_angle -= PLAYER_TURN_SPEED;
	if (data->player_angle < 0)
		data->player_angle = 360 - (data->player_angle * -1);
	delete_and_init_images(data);
	draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
}

void	key_action_right(t_data *data)
{
	data->player_angle += PLAYER_TURN_SPEED;
	if (data->player_angle >= 360)
		data->player_angle -= 360;
	delete_and_init_images(data);
	draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_data		*data;

	data = param;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		key_action_w(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		key_action_d(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		key_action_s(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		key_action_a(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		key_action_left(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		key_action_right(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_O))
		open_door(data);
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		success_exit(data);
}
