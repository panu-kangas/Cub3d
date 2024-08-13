#include "cubed_bonus.h"

int	set_return_direction(int direction)
{
	if (direction == 0)
		return (2);
	else if (direction == 1)
		return (3);
	else if (direction == 2)
		return (0);
	else if (direction == 3)
		return (1);
	else
		return (-1);
}

int	check_other_enemies(t_data *data, int direction, int i)
{
	int	k;
	int	check_x;
	int	check_y;

	check_x = data->enemy[i].x / IMG_SIZE;
	check_y = data->enemy[i].y / IMG_SIZE;
	if (direction == 0)
		check_y--;
	else if (direction == 1)
		check_x++;
	else if (direction == 2)
		check_y++;
	else if (direction == 3)
		check_x--;
	k = 0;
	while (k < data->enemy_count)
	{
		if (i != k && \
		(data->enemy[k].x <= check_x + 2 && data->enemy[k].x >= check_x - 2) \
		&& \
		(data->enemy[k].y <= check_y + 2 && data->enemy[k].y >= check_y - 2) \
		&& data->enemy[k].is_dead == 0)
			return (1);
		k++;
	}
	return (0);
}

int	check_enemy_wall(t_data *data, int direction, int i)
{
	int	x_edge[2];
	int	y_edge[2];

	x_edge[0] = (data->enemy[i].x - WALL_LIMIT) / IMG_SIZE;
	x_edge[1] = (data->enemy[i].x + WALL_LIMIT) / IMG_SIZE;
	y_edge[0] = (data->enemy[i].y - WALL_LIMIT) / IMG_SIZE;
	y_edge[1] = (data->enemy[i].y + WALL_LIMIT) / IMG_SIZE;

	if (direction == 0)
		y_edge[0] = (data->enemy[i].y - WALL_LIMIT - 20) / IMG_SIZE;
	else if (direction == 1)
		x_edge[1] = (data->enemy[i].x + WALL_LIMIT + 20) / IMG_SIZE;
	else if (direction == 2)
		y_edge[1] = (data->enemy[i].y + WALL_LIMIT + 20) / IMG_SIZE;
	else if (direction == 3)
		x_edge[0] = (data->enemy[i].x - WALL_LIMIT - 20) / IMG_SIZE;

//	printf("xedge0: %d, x1: %d, y0: %d, y1: %d\n", x_edge[0], x_edge[1], y_edge[0], y_edge[1]);

	if (data->map[y_edge[0]][x_edge[0]].type == '1' \
	|| data->map[y_edge[0]][x_edge[0]].is_closing == 1)
		return (1);
	if (data->map[y_edge[1]][x_edge[0]].type == '1' \
	|| data->map[y_edge[1]][x_edge[0]].is_closing == 1)
		return (1);
	if (data->map[y_edge[0]][x_edge[1]].type == '1' \
	|| data->map[y_edge[0]][x_edge[1]].is_closing == 1)
		return (1);
	if (data->map[y_edge[1]][x_edge[1]].type == '1' \
	|| data->map[y_edge[1]][x_edge[1]].is_closing == 1)
		return (1);
	
	if (check_other_enemies(data, direction, i) == 1)
		return (1);
	else
		return (0);
}

void	change_enemy_coord(t_data *data, int direction, int i)
{
	if (direction == 0)
		data->enemy[i].y -= 20;
	else if (direction == 2)
		data->enemy[i].y += 20;
	else if (direction == 3)
		data->enemy[i].x -= 20;
	else if (direction == 1)
		data->enemy[i].x += 20;
	data->enemy[i].step_count--;
}

int	get_enemy_direction(t_data *data, int return_direction, int i)
{
	int	direction;
	int	counter;

	srand(time(NULL));
	direction = (rand() + i) % 4;
	counter = 0;
	while (1)
	{
		if (check_enemy_wall(data, direction, i) == 0 \
		&& direction != return_direction)
			break ;
		direction++;
		counter++;
		if (direction == 4)
			direction = 0;
		if (counter == 4)
		{
			if (check_enemy_wall(data, return_direction, i) == 0)
				direction = return_direction;
			else
				direction = -1;
			break ;
		}
	}
	return (direction);
}

void	check_for_hit(t_data *data)
{
	int			i;

	i = 0;
	while (i < data->enemy_count)
	{
		if (data->enemy[i].x > data->player_coord[0] - IMG_SIZE \
		&&  data->enemy[i].x < data->player_coord[0] + IMG_SIZE \
		&& data->enemy[i].y > data->player_coord[1] - IMG_SIZE \
		&& data->enemy[i].y < data->player_coord[1] + IMG_SIZE)
		{
			if (data->enemy[i].is_dying == 0)
				death_exit(data);
		}
		i++;
	}
}

void	enemy_movement(t_data *data, int i)
{
	int	direction;
	int	return_direction;
	int	step_count;

	direction = data->enemy[i].direction;
	return_direction = set_return_direction(direction);
	step_count = data->enemy[i].step_count;
	if (step_count == 0 || step_count == -1)
	{
		direction = get_enemy_direction(data, return_direction, i);
		srand(time(NULL));
		step_count = (rand() + 1) % 20 + 1;
		return_direction = set_return_direction(direction);
		data->enemy[i].direction = direction;
		data->enemy[i].step_count = step_count;
	}
	change_enemy_coord(data, direction, i);
	check_for_hit(data);
	if (direction == -1 || check_enemy_wall(data, direction, i) == 1)
		data->enemy[i].step_count = 0;
}
