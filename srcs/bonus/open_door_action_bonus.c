#include "cubed_bonus.h"

int	is_player_too_close(t_data *data)
{
	int			x_edge[2];
	int			y_edge[2];
	long long	*p_coord;

	p_coord = data->player_coord;
	x_edge[0] = (p_coord[0] - WALL_LIMIT) / IMG_SIZE;
	x_edge[1] = (p_coord[0] + WALL_LIMIT) / IMG_SIZE;
	y_edge[0] = (p_coord[1] - WALL_LIMIT) / IMG_SIZE;
	y_edge[1] = (p_coord[1] + WALL_LIMIT) / IMG_SIZE;
	if (data->map[y_edge[0]][x_edge[0]].type == '1' \
	|| data->map[y_edge[0]][x_edge[0]].is_door == 1)
		return (1);
	if (data->map[y_edge[1]][x_edge[0]].type == '1' \
	|| data->map[y_edge[1]][x_edge[0]].is_door == 1)
		return (1);
	if (data->map[y_edge[0]][x_edge[1]].type == '1' \
	|| data->map[y_edge[0]][x_edge[1]].is_door == 1)
		return (1);
	if (data->map[y_edge[1]][x_edge[1]].type == '1' \
	|| data->map[y_edge[1]][x_edge[1]].is_door == 1)
		return (1);
	return (0);
}

int	change_door_stat_open(t_data *data, long long x, long long y)
{
	if (data->map[y][x].is_door == 1 && data->opening_in_action != 1 \
	&& is_player_too_close(data) == 0)
	{
		data->opening_in_action = 1;
		data->opening_door_coord[0] = x;
		data->opening_door_coord[1] = y;
		if (data->map[y][x].is_open == 0)
			data->map[y][x].is_opening = 1;
		else if (data->map[y][x].is_open == 1)
			data->map[y][x].is_closing = 1;
	}
	return (1);
}

int	check_for_door(t_data *data, long long x, long long y)
{
	double	angle;

	angle = data->player_angle;
	if (angle >= 340 || angle <= 20)
		return (change_door_stat_open(data, x, y - 1));
	else if (angle >= 70 && angle <= 110)
		return (change_door_stat_open(data, x + 1, y));
	else if (angle >= 160 && angle <= 200)
		return (change_door_stat_open(data, x, y + 1));
	else if (angle >= 250 && angle <= 290)
		return (change_door_stat_open(data, x - 1, y));
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
		delete_and_init_images(data);
		draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
	}
}
