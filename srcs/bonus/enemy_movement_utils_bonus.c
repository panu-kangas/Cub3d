/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_movement_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:02:44 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/17 13:02:45 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

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

void	set_enemy_y_edges(t_data *data, int *y_edge, int dir, int i)
{
	y_edge[0] = (data->enemy[i].y - ENEMY_WALL_LIMIT) / IMG_SIZE;
	y_edge[1] = (data->enemy[i].y + ENEMY_WALL_LIMIT) / IMG_SIZE;
	if (dir == 0)
		y_edge[0] = (data->enemy[i].y - ENEMY_WALL_LIMIT - 20) / IMG_SIZE;
	else if (dir == 2)
		y_edge[1] = (data->enemy[i].y + ENEMY_WALL_LIMIT + 20) / IMG_SIZE;
}

void	set_enemy_x_edges(t_data *data, int *x_edge, int dir, int i)
{
	x_edge[0] = (data->enemy[i].x - ENEMY_WALL_LIMIT) / IMG_SIZE;
	x_edge[1] = (data->enemy[i].x + ENEMY_WALL_LIMIT) / IMG_SIZE;
	if (dir == 1)
		x_edge[1] = (data->enemy[i].x + ENEMY_WALL_LIMIT + 20) / IMG_SIZE;
	else if (dir == 3)
		x_edge[0] = (data->enemy[i].x - ENEMY_WALL_LIMIT - 20) / IMG_SIZE;
}

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
