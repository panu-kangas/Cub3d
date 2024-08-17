/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_minimap_bonus.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:01:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/17 13:01:41 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

int	find_minimap_colour(t_data *data, long long *draw_coord)
{
	if (draw_coord[0] < 0 || draw_coord[1] < 0 \
	|| draw_coord[0] >= data->map_width || draw_coord[1] >= data->map_height)
		return (get_rgba(10, 10, 10, 255));
	if (data->map[draw_coord[1]][draw_coord[0]].is_enemy == 1)
		return (get_rgba(227, 16, 16, 255));
	else if (data->map[draw_coord[1]][draw_coord[0]].type == '0' \
	|| data->map[draw_coord[1]][draw_coord[0]].type == 'P'
	|| data->map[draw_coord[1]][draw_coord[0]].type == 'A')
		return (get_rgba(230, 224, 193, 255));
	else if (data->map[draw_coord[1]][draw_coord[0]].is_door == 1)
		return (get_rgba(237, 186, 33, 255));
	else if (data->map[draw_coord[1]][draw_coord[0]].type == '1' \
	|| data->map[draw_coord[1]][draw_coord[0]].type == 'X')
		return (get_rgba(10, 10, 10, 255));
	else
		return (0);
}

int	get_colour_minimap(t_data *data, int x_counter)
{
	int			start_pos;
	static int	y_counter;
	long long	draw_coord[2];
	long long	*p_coord;

	p_coord = data->player_coord;
	start_pos = MINIMAP_TILE_COUNT / 2;
	draw_coord[0] = (p_coord[0] / IMG_SIZE) - (start_pos - x_counter);
	draw_coord[1] = (p_coord[1] / IMG_SIZE) - (start_pos - y_counter);
	if (x_counter == MINIMAP_TILE_COUNT - 1)
		y_counter++;
	if (y_counter == MINIMAP_TILE_COUNT)
		y_counter = 0;
	return (find_minimap_colour(data, draw_coord));
}

void	check_minimap_x_count(int *x_count, int *line_counter)
{
	*x_count = *x_count + 1;
	if (*x_count == MINIMAP_TILE_COUNT)
	{
		*line_counter = *line_counter - 1;
		*x_count = 0;
	}
}

void	draw_minimap(t_data *data)
{
	long long	xy[2];
	int			x_count;
	int			y_count;
	int			line_counter;
	int			colour;

	line_counter = MINIMAP_TILE_COUNT;
	x_count = 0;
	while (line_counter > 0)
	{
		xy[0] = 0 + (MINIMAP_IMG_SIZE * x_count);
		colour = get_colour_minimap(data, x_count);
		while (xy[0] < (MINIMAP_IMG_SIZE * (x_count + 1)))
		{
			xy[1] = WINDOW_HEIGHT - (MINIMAP_IMG_SIZE * line_counter);
			y_count = -1;
			while (++y_count < MINIMAP_IMG_SIZE)
				mlx_put_pixel(data->door_canvas, xy[0], xy[1]++, colour);
			xy[0]++;
		}
		check_minimap_x_count(&x_count, &line_counter);
	}
	draw_player_icon(data);
}
