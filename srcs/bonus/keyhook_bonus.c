#include "cubed_bonus.h"

void	key_action_left(t_data *data)
{
	data->player_angle -= PLAYER_TURN_SPEED;
	if (data->player_angle < 0)
		data->player_angle = 360 - (data->player_angle * -1);
}

void	key_action_right(t_data *data)
{
	data->player_angle += PLAYER_TURN_SPEED;
	if (data->player_angle >= 360)
		data->player_angle -= 360;
}

void	keyhook(void *param)
{
	t_data		*data;
	int32_t		pos_x;
	int32_t		pos_y;

	data = param;
	if (data->is_dead == 1 || data->show_menu == 1)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_W))
		key_action_w(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_D))
		key_action_d(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_S))
		key_action_s(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_A))
		key_action_a(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_LEFT))
		key_action_left(data);
	if (mlx_is_key_down(data->mlx, MLX_KEY_RIGHT))
		key_action_right(data);
	mlx_get_mouse_pos(data->mlx, &pos_x, &pos_y);
	if (pos_x != WINDOW_WIDTH / 2)
		rotation(pos_x, data);
	delete_and_init_images(data);
	draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
}

void	special_keys(mlx_key_data_t keydata, void *param)
{
	t_data		*data;

	data = (t_data *)param;
	if (data->show_menu == 1 && keydata.action == MLX_PRESS)
	{
		data->menu_img->instances->enabled = false;
		data->show_menu = 0;
	}
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		success_exit(data);
	if (data->is_dead == 1 || data->show_menu == 1)
		return ;
	if (mlx_is_key_down(data->mlx, MLX_KEY_E))
		open_door(data);
	if (keydata.key == MLX_KEY_SPACE && keydata.action == MLX_PRESS)
	{
		data->anim.has_shot = 1;
		data->shooting = 1;
	}
	if (mlx_is_key_down(data->mlx, MLX_KEY_F))
	{
		if (data->exit_rdy == 1)
			success_exit(data);
	}
}
