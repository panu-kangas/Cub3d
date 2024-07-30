#include "cubed_bonus.h"

void	set_player_icon_img(t_data *data, int direction)
{
	mlx_texture_t	*player_text;

	if (direction == 0)
		player_text = mlx_load_png("./sprites/minimap_player_0.png");
	else if (direction == 1)
		player_text = mlx_load_png("./sprites/minimap_player_1.png");
	else if (direction == 2)
		player_text = mlx_load_png("./sprites/minimap_player_2.png");
	else if (direction == 3)
		player_text = mlx_load_png("./sprites/minimap_player_3.png");
	else if (direction == 4)
		player_text = mlx_load_png("./sprites/minimap_player_4.png");
	else if (direction == 5)
		player_text = mlx_load_png("./sprites/minimap_player_5.png");
	else if (direction == 6)
		player_text = mlx_load_png("./sprites/minimap_player_6.png");
	else
		player_text = mlx_load_png("./sprites/minimap_player_7.png");
	if (!player_text)
		error_exit(data,mlx_strerror(mlx_errno), 1);
	data->player_icon = mlx_texture_to_image(data->mlx, player_text);
	if (!data->player_icon)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(player_text);
}

int	get_player_direction(double angle)
{
	if (angle > 337.5 || angle <= 22.5)
		return (0);
	else if (angle > 22.5 && angle <= 67.5)
		return (1);
	else if (angle > 67.5 && angle <= 112.5)
		return (2);
	else if (angle > 112.5 && angle <= 157.5)
		return (3);
	else if (angle > 157.5 && angle <= 202.5)
		return (4);
	else if (angle > 202.5 && angle <= 247.5)
		return (5);
	else if (angle > 247.5 && angle <= 292.5)
		return (6);
	else if (angle > 292.5 && angle <= 337.5)
		return (7);
	else
		return (-1);
}

void	draw_player_icon(t_data *data)
{
	int			direction;
	long long	height;

	height = WINDOW_HEIGHT - (MINIMAP_HEIGHT / 2);
	direction = get_player_direction(data->player_angle);
	set_player_icon_img(data, direction);
	mlx_image_to_window(data->mlx, data->player_icon, (MINIMAP_WIDTH / 2) - 8, height - 8);
	mlx_set_instance_depth(&data->player_icon->instances[0], 2);
}