#include "cubed.h"

void	change_player_coord(t_data *data, double direction)
{
	if (direction > 337.5 || direction <= 22.5)
		data->player_coord[1] -= PLAYER_SPEED;
	else if (direction > 22.5 && direction <= 67.5)
	{
		data->player_coord[0] += PLAYER_SPEED;
		data->player_coord[1] -= PLAYER_SPEED;
	}
	else if (direction > 67.5 && direction <= 112.5)
		data->player_coord[0] += PLAYER_SPEED;
	else if (direction > 112.5 && direction <= 157.5)
	{
		data->player_coord[0] += PLAYER_SPEED;
		data->player_coord[1] += PLAYER_SPEED;
	}
	else if (direction > 157.5 && direction <= 202.5)
		data->player_coord[1] += PLAYER_SPEED;
	else if (direction > 202.5 && direction <= 247.5)
	{
		data->player_coord[0] -= PLAYER_SPEED;
		data->player_coord[1] += PLAYER_SPEED;
	}
	else if (direction > 247.5 && direction <= 292.5)
		data->player_coord[0] -= PLAYER_SPEED;
	else if (direction > 292.5 && direction <= 337.5)
	{
		data->player_coord[0] -= PLAYER_SPEED;
		data->player_coord[1] -= PLAYER_SPEED;
	}
}

void	key_action_a(t_data *data)
{
	double	direction;

	direction = data->player_angle - 90;
	if (direction >= 360)
		direction -= 360;
	else if (direction < 0)
		direction = 360 - (direction * -1);

	change_player_coord(data, direction);

	mlx_delete_image(data->mlx, data->game_img);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_image(data);
	mlx_image_to_window(data->mlx, data->game_img, 0, 0); // error handling
}

void	key_action_s(t_data *data)
{
	double	direction;

	direction = data->player_angle - 180;
	if (direction >= 360)
		direction -= 360;
	else if (direction < 0)
		direction = 360 - (direction * -1);

	change_player_coord(data, direction);
	mlx_delete_image(data->mlx, data->game_img);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_image(data);
	mlx_image_to_window(data->mlx, data->game_img, 0, 0); // error handling
}

void	key_action_d(t_data *data)
{
	double	direction;

	direction = data->player_angle + 90;
	if (direction >= 360)
		direction -= 360;
	else if (direction < 0)
		direction = 360 - (direction * -1);

	change_player_coord(data, direction);

	mlx_delete_image(data->mlx, data->game_img);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_image(data);
	mlx_image_to_window(data->mlx, data->game_img, 0, 0); // error handling
}

void	key_action_w(t_data *data)
{
	double	direction;

	direction = data->player_angle;

	change_player_coord(data, direction);

	mlx_delete_image(data->mlx, data->game_img);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_image(data);
	mlx_image_to_window(data->mlx, data->game_img, 0, 0); // error handling
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
	mlx_image_to_window(data->mlx, data->game_img, 0, 0); // error handling
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
	mlx_image_to_window(data->mlx, data->game_img, 0, 0); // error handling
}

void	keyhook(mlx_key_data_t keydata, void *param)
{
	t_data *data;

	data = param;

	// Should these be if or else if...?

	if (mlx_is_key_down(data->mlx, MLX_KEY_W)) // eventually use mlx_is_key_down()
		key_action_w(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_D)) // eventually use mlx_is_key_down()
		key_action_d(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_S)) // eventually use mlx_is_key_down()
		key_action_s(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_A)) // eventually use mlx_is_key_down()
		key_action_a(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT)) // eventually use mlx_is_key_down()
		key_action_left(data);
	else if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT)) // eventually use mlx_is_key_down()
		key_action_right(data);
	else if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		error_exit(data, "You just pressed ESC", 1); // Change this to succes_exit() 

}