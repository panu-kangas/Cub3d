/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate_doors_and_enemies_bonus.c                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/03 15:18:08 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/09 14:42:31 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static int	check_door_is_walled(t_map *map, int j, int map_width)
{
	if (j == 0 || j == map_width - 1)
		return (-1);
	if (map[j - 1].type != '1' || map[j + 1].type != '1')
		return (-1);
	return (0);
}

static int check_door_walled_y(char **door_line, int x_pos)
{
	if (door_line[-1][x_pos] != '1' || door_line[1][x_pos] != '1')
		return (-1);
	return (0);
}

static int	check_enemies_surroundings(char **enemy_tile, int x_pos)
{
	if (ft_strchr("NEWS", enemy_tile[-1][x_pos - 1]) != NULL)
		return (-1);
	if (ft_strchr("NEWS", enemy_tile[-1][x_pos]) != NULL)
		return (-1);
	if (ft_strchr("NEWS", enemy_tile[-1][x_pos + 1]) != NULL)
		return (-1);
	if (ft_strchr("NEWS", enemy_tile[0][x_pos - 1]) != NULL)
		return (-1);
	if (ft_strchr("NEWS", enemy_tile[0][x_pos]) != NULL)
		return (-1);
	if (ft_strchr("NEWS", enemy_tile[0][x_pos + 1]) != NULL)
		return (-1);
	if (ft_strchr("NEWS", enemy_tile[1][x_pos - 1]) != NULL)
		return (-1);
	if (ft_strchr("NEWS", enemy_tile[1][x_pos]) != NULL)
		return (-1);
	if (ft_strchr("NEWS", enemy_tile[1][x_pos + 1]) != NULL)
		return (-1);
	return (0);
}

static int	validate_enemy(char **enemy_line, int x_pos, int map_width)
{
	if (x_pos == 0 || x_pos == map_width - 1)
		return (-1);
	if (check_enemies_surroundings(enemy_line, x_pos) == -1)
		return (-1);

	return (0);
}

void	validate_door_and_enemy_positions(t_data *data, int i, int j)
{
	if (data->map[i][j].type == 'D')
	{
		if (check_door_is_walled(data->map[i], j, data->map_width) == -1
			&& check_door_walled_y(&data->map_lines[i], j) == -1)
			error_exit(data, "Invalid door position", 0);
	}
	else if (data->map[i][j].type == 'A')
	{
		data->map[i][j].is_enemy = 1;
		if (validate_enemy(&data->map_lines[i], j, data->map_width) == -1)
			error_exit(data, "Invalid enemy position", 0);
		data->enemy_count++;
	}
}
