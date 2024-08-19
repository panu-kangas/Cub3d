/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_open_door_px_bonus.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:01:52 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/17 13:01:53 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	execute_open_door_drawing(t_data *data, int column, double wall_height)
{
	int		start_coord;

	start_coord = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	start_coord = draw_wall(data, (column * 4), wall_height, start_coord);
	data->found_open_door_vert = 0;
	data->found_open_door_horiz = 0;
}

void	get_open_door_pixels(t_data *data, double dist_to_door, int column)
{
	char		direction;
	int			iterator;
	long long	xy[2];

	direction = get_open_door_direction(data);
	iterator = 2;
	if (data->found_open_door_vert == 1)
	{
		set_open_door_iterator(data, xy, &iterator);
		if (direction == 'W')
			data->pixels = data->d_open_img[iterator][3]->pixels;
		else
			data->pixels = data->d_open_img[iterator][1]->pixels;
		update_wall_dist_list(data, dist_to_door, column, iterator);
	}
	else if (data->found_open_door_horiz == 1)
	{
		set_open_door_iterator(data, xy, &iterator);
		if (direction == 'N')
			data->pixels = data->d_open_img[iterator][0]->pixels;
		else
			data->pixels = data->d_open_img[iterator][2]->pixels;
		update_wall_dist_list(data, dist_to_door, column, iterator);
	}
}

void	draw_open_door_pixels(t_data *data, double dist, double wall_height)
{
	int	column_to_draw;

	data->pixels = data->d_open_img[2][0]->pixels;
	if (data->v_h_flag == 0)
	{
		if (data->found_open_door_vert == 0)
		{
			data->found_open_door_horiz = 0;
			return ;
		}
		get_column_to_draw(data, 'V', &column_to_draw);
		get_open_door_pixels(data, dist, column_to_draw);
	}
	else
	{
		if (data->found_open_door_horiz == 0)
		{
			data->found_open_door_vert = 0;
			return ;
		}
		get_column_to_draw(data, 'H', &column_to_draw);
		get_open_door_pixels(data, dist, column_to_draw);
	}
	execute_open_door_drawing(data, column_to_draw, wall_height);
}
