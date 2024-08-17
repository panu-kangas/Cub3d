/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   count_open_doors_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:01:15 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/17 13:01:18 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

int	check_invalid_coords(t_data *data, long long *check_coord, char vh_flag)
{
	long long	x;
	long long	y;

	x = check_coord[0];
	y = check_coord[1];
	if (x < 0 || y < 0)
	{
		if (vh_flag == 'V')
			data->invalid_vert = 1;
		else
			data->invalid_horiz = 1;
		return (1);
	}
	else if (data->map[y][x].type == 'X')
	{
		if (vh_flag == 'V')
			data->invalid_vert = 1;
		else
			data->invalid_horiz = 1;
		return (1);
	}
	return (0);
}

int	check_for_open_door_cntr(t_data *data, long long *check_coord, \
char vh_flag, double ray_angle)
{
	long long	x;
	long long	y;

	x = check_coord[0];
	y = check_coord[1];
	if (check_invalid_coords(data, check_coord, vh_flag) == 1)
		return (1);
	if (data->map[y][x].type == '1')
		return (1);
	else if (data->map[y][x].is_open == 1)
	{
		if (vh_flag == 'V' \
		&& check_ray_door_vert(data, ray_angle) == 1)
			data->open_door_count++;
		else if (vh_flag == 'H' \
		&& check_ray_door_horiz(data, ray_angle) == 1)
			data->open_door_count++;
	}
	return (0);
}

void	count_open_doors(t_data *data, double ray_angle, double addition)
{
	int			i;
	long long	vert_coords[2];
	long long	horiz_coords[2];

	data->invalid_vert = 0;
	data->invalid_horiz = 0;
	if (ray_angle == 0.0000 || ray_angle - 90.0000 == 0 \
	|| ray_angle - 180.0000 == 0 || ray_angle - 270.0000 == 0)
		ray_angle += addition;
	data->open_door_count = 0;
	get_vert_intersection(data, ray_angle, vert_coords, 0);
	i = 1;
	while (check_for_open_door_cntr(data, vert_coords, 'V', ray_angle) != 1)
		get_vert_intersection(data, ray_angle, vert_coords, i++);
	get_horizon_intersection(data, ray_angle, horiz_coords, 0);
	i = 1;
	while (check_for_open_door_cntr(data, horiz_coords, 'H', ray_angle) != 1)
		get_horizon_intersection(data, ray_angle, horiz_coords, i++);
}
