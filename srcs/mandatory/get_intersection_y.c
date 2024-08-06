/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection_y.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:49:36 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/02 10:49:38 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
/*
void find_next_wall_from_max(t_data *data, long long *t_coord, char xy_flag)
{
	if (xy_flag == 'Y')
	{
		while (data->map[t_coord[1] / IMG_SIZE][t_coord[0] / IMG_SIZE].type == 'X')
			t_coord[1] -= 1; // maybe IMG_SIZE...?
	}
	else if (xy_flag == 'Y')
	{
		while (data->map[t_coord[1] / IMG_SIZE][t_coord[0] / IMG_SIZE].type == 'X')
			t_coord[0] -= 1; // maybe IMG_SIZE...?
	}
}

void find_next_wall_from_zero(t_data *data, long long *t_coord, char xy_flag)
{

//	printf("coord_x= %lld, coord_y=%lld\n", t_coord[0], t_coord[1]);

	if (xy_flag == 'Y')
	{
		while (data->map[t_coord[1] / IMG_SIZE][t_coord[0] / IMG_SIZE].type == 'X')
			t_coord[1] += 1; // maybe IMG_SIZE...?
	}
	else if (xy_flag == 'X')
	{
		while (data->map[t_coord[1] / IMG_SIZE][t_coord[0] / IMG_SIZE].type == 'X')
			t_coord[0] += 1; // maybe IMG_SIZE...?
	}
}

void check_for_valid_coord(t_data *data, long long *t_coord, char xy_flag)
{
	if (xy_flag == 'Y')
	{
		if (t_coord[1] == 0)
			find_next_wall_from_zero(data, t_coord, 'Y');
		else
			find_next_wall_from_max(data, t_coord, 'Y');
	}
	else if (xy_flag == 'X')
	{
		if (t_coord[0] == 0)
			find_next_wall_from_zero(data, t_coord, 'X');
		else
			find_next_wall_from_max(data, t_coord, 'X');
	}
}



long long	get_up_right_y(t_data *data, long long *t_coord, double ray_angle)
{
	long long	*p_coord;

	p_coord = data->player_coord;
	t_coord[1] = p_coord[1] - ((t_coord[0] - p_coord[0]) \
	* tan(convert_to_radians(90 - ray_angle)));
	if (t_coord[1] < 0)
	{
		t_coord[1] = 0;
		check_for_valid_coord(data, t_coord, 'Y');
	}
	return (t_coord[1] / IMG_SIZE);
}

long long	get_down_right_y(t_data *data, long long *t_coord, double ray_angle)
{
	long long	*p_coord;

	p_coord = data->player_coord;
	t_coord[1] = p_coord[1] + ((t_coord[0] - p_coord[0]) \
	* tan(convert_to_radians(ray_angle - 90)));
	if (t_coord[1] >= ((data->map_height) * IMG_SIZE))
		check_for_valid_coord(data, t_coord, 'Y');
	return (t_coord[1] / IMG_SIZE);
}

long long	get_down_left_y(t_data *data, long long *t_coord, double ray_angle)
{
	long long	*p_coord;

	p_coord = data->player_coord;
	t_coord[1] = p_coord[1] + ((p_coord[0] - t_coord[0]) \
	* tan(convert_to_radians(270 - ray_angle)));
	if (t_coord[1] >= ((data->map_height) * IMG_SIZE))
		check_for_valid_coord(data, t_coord, 'Y');
	return (t_coord[1] / IMG_SIZE);
}

long long	get_up_left_y(t_data *data, long long *t_coord, double ray_angle)
{
	long long	*p_coord;

	p_coord = data->player_coord;
	t_coord[1] = p_coord[1] - ((p_coord[0] - t_coord[0]) \
	* tan(convert_to_radians(ray_angle - 270)));
	if (t_coord[1] < 0)
	{
		t_coord[1] = 0;
		check_for_valid_coord(data, t_coord, 'Y');
	}
	return (t_coord[1] / IMG_SIZE);
}

*/

long long	get_up_right_y(t_data *data, long long *t_coord, double ray_angle)
{
	long long	*p_coord;

	p_coord = data->player_coord;
	t_coord[1] = p_coord[1] - ((t_coord[0] - p_coord[0]) \
	* tan(convert_to_radians(90 - ray_angle)));
	if (t_coord[1] < 0)
		return (0);
	else
		return (t_coord[1] / IMG_SIZE);
}

long long	get_down_right_y(t_data *data, long long *t_coord, double ray_angle)
{
	long long	*p_coord;

	p_coord = data->player_coord;
	t_coord[1] = p_coord[1] + ((t_coord[0] - p_coord[0]) \
	* tan(convert_to_radians(ray_angle - 90)));
	if (t_coord[1] >= ((data->map_height) * IMG_SIZE))
		return (data->map_height - 1);
	else
		return (t_coord[1] / IMG_SIZE);
}

long long	get_down_left_y(t_data *data, long long *t_coord, double ray_angle)
{
	long long	*p_coord;

	p_coord = data->player_coord;
	t_coord[1] = p_coord[1] + ((p_coord[0] - t_coord[0]) \
	* tan(convert_to_radians(270 - ray_angle)));
	if (t_coord[1] >= ((data->map_height) * IMG_SIZE))
		return (data->map_height - 1);
	else
		return (t_coord[1] / IMG_SIZE);
}

long long	get_up_left_y(t_data *data, long long *t_coord, double ray_angle)
{
	long long	*p_coord;

	p_coord = data->player_coord;
	t_coord[1] = p_coord[1] - ((p_coord[0] - t_coord[0]) \
	* tan(convert_to_radians(ray_angle - 270)));
	if (t_coord[1] < 0)
		return (0);
	else
		return (t_coord[1] / IMG_SIZE);
}
