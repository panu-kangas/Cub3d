#include "cubed_bonus.h"

int	check_for_door(t_data *data, long long x, long long y)
{
	double	angle;

	angle = data->player_angle;

	if (data->facing_door == 0)
		return (0);
	if (angle >= 340 || angle <= 20)
	{
		if (data->map[y - 1][x].is_door == 1)
			return (1);

	}
	else if (angle >= 70 && angle <= 110)
	{
		if (data->map[y][x + 1].is_door == 1)
			return (1);

	}
	else if (angle >= 160 && angle <= 200)
	{
		if (data->map[y + 1][x].is_door == 1)
			return (1);

	}
	else if (angle >= 250 && angle <= 290)
	{
		if (data->map[y][x - 1].is_door == 1)
			return (1);
	}
	return (0);
}

void	open_door(t_data *data)
{
	long long	x;
	long long	y;

	x = data->player_coord[0] / IMG_SIZE;
	y = data->player_coord[1] / IMG_SIZE;

	printf("HERE\n");

	printf("FACING %d\n", data->facing_door);

	if (check_for_door(data, x, y) == 1)
	{
		printf("HERE in if\n");

		data->map[y - 1][x].type = '0';
		delete_and_init_images(data);
		draw_image(data);
		if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
			error_exit(data, mlx_strerror(mlx_errno), 1);
		mlx_set_instance_depth(&data->game_img->instances[0], 1);	
	}
}

void	key_action_left(t_data *data)
{
	data->player_angle -= PLAYER_TURN_SPEED;
	if (data->player_angle < 0)
		data->player_angle = 360 - (data->player_angle * -1);
	delete_and_init_images(data);
	draw_image(data);
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(&data->game_img->instances[0], 1);
}

void	key_action_right(t_data *data)
{
	data->player_angle += PLAYER_TURN_SPEED;
	if (data->player_angle >= 360)
		data->player_angle -= 360;
	delete_and_init_images(data);
	draw_image(data);
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(&data->game_img->instances[0], 1);
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
