/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 16:06:46 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/05 16:05:57 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	assign_player_position(t_data *data, int x, int y, char type)
{
	data->player_x_pos = x;
	data->player_y_pos = y;
	data->player_flag = 1;
	if (type == 'N')
		data->player_angle = 0;
	else if (type == 'E')
		data->player_angle = 90;
	else if (type == 'S')
		data->player_angle = 180;
	else if (type == 'W')
		data->player_angle = 270;
}

void	check_map_syntax(t_data *data)
{
	int	i;
	int	j;

	i = -1;
	data->player_flag = 0;
	while (++i < data->map_height)
	{
		j = -1;
		while (++j < data->map_width)
		{
			if (ft_strchr(VALIDMAPCHARS, data->map[i][j].type) == NULL)
				error_exit(data, "Invalid map syntax", 0);
			if ((data->map[i][j].type == 'E' || data->map[i][j].type == 'N'
				|| data->map[i][j].type == 'W' || data->map[i][j].type == 'S'))
			{
				if (data->player_flag == 0)
					assign_player_position (data, j, i, data->map[i][j].type);
				else
					error_exit(data, "Too many players", 0);
				data->map[i][j].type = 'P';
			}
			if (data->map[i][j].type == 'D' || data->map[i][j].type == 'A')
				validate_door_and_enemy_positions(data, i, j);
		}
	}
}

void	get_widest_width(t_data *data)
{
	int	i;
	int	j;
	int	width;

	i = 0;
	width = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (data->map_lines[i][j] != '\0')
			j++;
		if (j > width)
			width = j; // TEST, removed -1
		i++;
	}
	data->map_width = width;
}
