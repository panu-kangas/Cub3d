/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   compare_distance.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:11:27 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/02 11:11:29 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

double	get_vert_distance(t_data *data, double ray_angle, long long *v_coord)
{
	double		vert_distance;
	long long	*p_coord;

	p_coord = data->player_coord;
	if (ray_angle < 90)
	{
		vert_distance = (((v_coord[0]) * IMG_SIZE) - p_coord[0]) \
		/ cos(convert_to_radians(90 - ray_angle));
	}
	else if (ray_angle > 90 && ray_angle < 180)
	{
		vert_distance = (((v_coord[0]) * IMG_SIZE) - p_coord[0]) \
		/ cos(convert_to_radians(ray_angle - 90));
	}
	else if (ray_angle > 180 && ray_angle < 270)
	{
		vert_distance = (p_coord[0] - ((v_coord[0] + 1) * IMG_SIZE)) \
		/ cos(convert_to_radians(270 - ray_angle));
	}
	else
	{
		vert_distance = (p_coord[0] - ((v_coord[0] + 1) * IMG_SIZE)) \
		/ cos(convert_to_radians(ray_angle - 270));
	}
	return (vert_distance);
}

double	get_horiz_distance(t_data *data, double ray_angle, long long *h_coord)
{
	double		horiz_distance;
	long long	*p_coord;

	p_coord = data->player_coord;
	if (ray_angle < 90)
	{
		horiz_distance = (p_coord[1] - ((h_coord[1] + 1) * IMG_SIZE)) \
		/ sin(convert_to_radians(90 - ray_angle));
	}
	else if (ray_angle > 90 && ray_angle < 180)
	{
		horiz_distance = (((h_coord[1]) * IMG_SIZE) - p_coord[1]) \
		/ sin(convert_to_radians(ray_angle - 90));
	}
	else if (ray_angle > 180 && ray_angle < 270)
	{
		horiz_distance = (((h_coord[1]) * IMG_SIZE) - p_coord[1]) \
		/ sin(convert_to_radians(270 - ray_angle));
	}
	else
	{
		horiz_distance = (p_coord[1] - ((h_coord[1] + 1) * IMG_SIZE)) \
		/ sin(convert_to_radians(ray_angle - 270));
	}
	return (horiz_distance);
}

double	compare_distance(t_data *data, double ray_angle, \
long long *vert_coord, long long *horizon_coord)
{
	double	vert_dist;
	double	horiz_dist;
	double	p_angl;

	p_angl = data->player_angle;
	vert_dist = get_vert_distance(data, ray_angle, vert_coord);
	horiz_dist = get_horiz_distance(data, ray_angle, horizon_coord);
	if (vert_dist < horiz_dist)
	{
		data->v_h_flag = 0;
		return (vert_dist * cos(convert_to_radians (p_angl - ray_angle)));
	}
	else
	{
		data->v_h_flag = 1;
		return (horiz_dist * cos(convert_to_radians (p_angl - ray_angle)));
	}
}
