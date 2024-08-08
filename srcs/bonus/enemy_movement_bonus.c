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
/*
void	move_enemy_img(t_game *game, int enemy_x, int enemy_y, int i)
{
	int	start_x;
	int	start_y;
	int	max_w;
	int	max_h;
	int	draw_coord[2];

	start_x = get_x_start(game);
	start_y = get_y_start(game);
	max_w = start_x + game->window_width / 70;
	max_h = start_y + game->window_height / 70;
	if (enemy_x >= start_x && enemy_x < max_w && \
	enemy_y >= start_y && enemy_y < max_h)
	{
		game->enemies[i].instance = game->e_count;
		draw_coord[0] = (enemy_x - start_x) * 70;
		draw_coord[1] = (enemy_y - start_y) * 70;
		if (mlx_image_to_window(game->mlx, game->enemy_img[game->enemy_img_i], \
		draw_coord[0] + 18, draw_coord[1] + 18) < 0)
			error_exit(game, game->mlx, mlx_strerror(mlx_errno));
		mlx_set_instance_depth(\
		&game->enemy_img[game->enemy_img_i]->instances[game->e_count++], 4);
	}
}
*/

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
		(data->enemy[k].x <= check_x + 1 && data->enemy[k].x >= check_x - 1) \
		&& \
		(data->enemy[k].y <= check_y + 1 && data->enemy[k].y >= check_y - 1))
			return (1);
		k++;
	}
	return (0);
}

int	check_enemy_wall(t_data *data, int direction, int i)
{
	int			enemy_x;
	int			enemy_y;

	enemy_x = data->enemy[i].x;
	enemy_y = data->enemy[i].y;
	if (direction == 0 && data->map[(enemy_y - 20 - ENEMY_WIDTH / 2) / IMG_SIZE][enemy_x / IMG_SIZE].type == '1')
		return (1);
	else if (direction == 2 && data->map[(enemy_y + 20 + ENEMY_WIDTH / 2) / IMG_SIZE][enemy_x / IMG_SIZE].type == '1')
		return (1);
	else if (direction == 3 && data->map[enemy_y / IMG_SIZE][(enemy_x - 20 - ENEMY_WIDTH / 2) / IMG_SIZE].type == '1')
		return (1);
	else if (direction == 1 && data->map[enemy_y / IMG_SIZE][(enemy_x + 20 + ENEMY_WIDTH / 2) / IMG_SIZE].type == '1')
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
	direction = rand() % 4;
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
		step_count = rand() % 10 + 1;
		return_direction = set_return_direction(direction);
		data->enemy[i].direction = direction;
		data->enemy[i].step_count = step_count;
	}
	change_enemy_coord(data, direction, i);
//	check_for_hit(game);
//	move_enemy_img(game, game->enemies[i].x, game->enemies[i].y, i);
	if (direction == -1 || check_enemy_wall(data, direction, i) == 1)
		data->enemy[i].step_count = 0;
}
