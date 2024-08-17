/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   find_wall_dist_utils_bonus.c                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:02:57 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/17 13:02:58 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

int	check_ray_door_horiz(t_data *data, double r_ang)
{
	double		*s_crd;
	long long	temp_coord[2];

	s_crd = data->horiz_inters_crd;
	if (r_ang < 90 || r_ang > 270)
		temp_coord[1] = s_crd[1] - (IMG_SIZE / 2);
	else
		temp_coord[1] = s_crd[1] + (IMG_SIZE / 2);
	if (r_ang < 90)
		temp_coord[0] = get_up_right_door_x(data, temp_coord, s_crd, r_ang);
	else if (r_ang > 90 && r_ang < 180)
		temp_coord[0] = get_down_right_door_x(data, temp_coord, s_crd, r_ang);
	else if (r_ang > 180 && r_ang < 270)
		temp_coord[0] = get_down_left_door_x(temp_coord, s_crd, r_ang);
	else
		temp_coord[0] = get_up_left_door_x(temp_coord, s_crd, r_ang);
	if (temp_coord[0] / IMG_SIZE == (long long)s_crd[0] / IMG_SIZE)
	{
		data->horiz_inters_crd[0] = temp_coord[0];
		data->horiz_inters_crd[1] = temp_coord[1];
		return (1);
	}
	else
		return (0);
}

int	check_ray_door_vert(t_data *data, double r_ang)
{
	double		*s_crd;
	long long	temp_coord[2];

	s_crd = data->vert_inters_crd;
	if (r_ang < 180)
		temp_coord[0] = s_crd[0] + (IMG_SIZE / 2);
	else
		temp_coord[0] = s_crd[0] - (IMG_SIZE / 2);
	if (r_ang < 90)
		temp_coord[1] = get_up_right_door_y(temp_coord, s_crd, r_ang);
	else if (r_ang > 90 && r_ang < 180)
		temp_coord[1] = get_down_right_door_y(data, temp_coord, s_crd, r_ang);
	else if (r_ang > 180 && r_ang < 270)
		temp_coord[1] = get_down_left_door_y(data, temp_coord, s_crd, r_ang);
	else
		temp_coord[1] = get_up_left_door_y(temp_coord, s_crd, r_ang);
	if (temp_coord[1] / IMG_SIZE == (long long)s_crd[1] / IMG_SIZE)
	{
		data->vert_inters_crd[0] = temp_coord[0];
		data->vert_inters_crd[1] = temp_coord[1];
		return (1);
	}
	else
		return (0);
}
