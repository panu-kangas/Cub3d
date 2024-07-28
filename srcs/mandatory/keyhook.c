#include "cubed.h"

void	change_player_coord(t_data *data, double direction, int speed)
{
	if (direction > 337.5 || direction <= 22.5)
		data->player_coord[1] -= speed;
	else if (direction > 22.5 && direction <= 67.5)
	{
		data->player_coord[0] += speed;
		data->player_coord[1] -= speed;
	}
	else if (direction > 67.5 && direction <= 112.5)
		data->player_coord[0] += speed;
	else if (direction > 112.5 && direction <= 157.5)
	{
		data->player_coord[0] += speed;
		data->player_coord[1] += speed;
	}
	else if (direction > 157.5 && direction <= 202.5)
		data->player_coord[1] += speed;
	else if (direction > 202.5 && direction <= 247.5)
	{
		data->player_coord[0] -= speed;
		data->player_coord[1] += speed;
	}
	else if (direction > 247.5 && direction <= 292.5)
		data->player_coord[0] -= speed;
	else if (direction > 292.5 && direction <= 337.5)
	{
		data->player_coord[0] -= speed;
		data->player_coord[1] -= speed;
	}
}

int		check_for_collision(t_data *data, double direction)
{
	int			i;
	long long	orig_coord[2];
	long long	*p_coord;

	i = PLAYER_SPEED;
	orig_coord[0] = data->player_coord[0];
	orig_coord[1] = data->player_coord[1];
	p_coord = data->player_coord;

	while (i > 0)
	{
		change_player_coord(data, direction, 1);
		if (data->map[p_coord[1] / IMG_SIZE][p_coord[0] / IMG_SIZE].type == '1')
		{
			p_coord[0] = orig_coord[0];
			p_coord[1] = orig_coord[1];
			return (1);
		}
		i--;
	}
	return (0);
}

void	key_action_a(t_data *data)
{
	double		direction;

	direction = data->player_angle - 90;
	if (direction >= 360)
		direction -= 360;
	else if (direction < 0)
		direction = 360 - (direction * -1);

	if (check_for_collision(data, direction) == 1)
		return ;

	mlx_delete_image(data->mlx, data->game_img);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_image(data);
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1); // These need to be tested somehow! That the exit actually works
}

void	key_action_s(t_data *data)
{
	double		direction;

	direction = data->player_angle - 180;
	if (direction >= 360)
		direction -= 360;
	else if (direction < 0)
		direction = 360 - (direction * -1);

	if (check_for_collision(data, direction) == 1)
		return ;

	mlx_delete_image(data->mlx, data->game_img);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_image(data);
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

void	key_action_d(t_data *data)
{
	double		direction;

	direction = data->player_angle + 90;
	if (direction >= 360)
		direction -= 360;
	else if (direction < 0)
		direction = 360 - (direction * -1);

	if (check_for_collision(data, direction) == 1)
		return ;

	mlx_delete_image(data->mlx, data->game_img);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_image(data);
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

void	key_action_w(t_data *data)
{
	double		direction;

	direction = data->player_angle;

	if (check_for_collision(data, direction) == 1)
		return ;

	mlx_delete_image(data->mlx, data->game_img);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_image(data);
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

void	key_action_left(t_data *data)
{
	data->player_angle -= PLAYER_TURN_SPEED;
	if (data->player_angle < 0)
		data->player_angle = 360 - (data->player_angle * -1);

	mlx_delete_image(data->mlx, data->game_img);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_image(data);
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

void	key_action_right(t_data *data)
{
	data->player_angle += PLAYER_TURN_SPEED;
	if (data->player_angle >= 360)
		data->player_angle -= 360;

	mlx_delete_image(data->mlx, data->game_img);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_image(data);
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_data		*data;

	data = param;

	// Should these be if or else if...?

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
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		success_exit(data);

}
