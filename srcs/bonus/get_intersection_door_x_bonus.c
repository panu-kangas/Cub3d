/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_intersection_door_x_bonus.c                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:03:22 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/17 13:03:23 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

long long	get_up_right_door_x(t_data *data, long long *t_crd, \
double *s_crd, double r_ang)
{
	t_crd[0] = s_crd[0] + ((s_crd[1] - t_crd[1]) \
	/ tan(conv_to_rad(90 - r_ang)));
	if (t_crd[0] >= ((data->map_width) * IMG_SIZE))
		return ((data->map_width - 1) * IMG_SIZE);
	else
		return (t_crd[0]);
}

long long	get_down_right_door_x(t_data *data, long long *t_crd, \
double *s_crd, double r_ang)
{
	t_crd[0] = s_crd[0] + ((t_crd[1] - s_crd[1]) \
	/ tan(conv_to_rad(r_ang - 90)));
	if (t_crd[0] >= ((data->map_width) * IMG_SIZE))
		return ((data->map_width - 1) * IMG_SIZE);
	else
		return (t_crd[0]);
}

long long	get_down_left_door_x(long long *t_crd, double *s_crd, double r_ang)
{
	t_crd[0] = s_crd[0] - \
	((t_crd[1] - s_crd[1]) / tan(conv_to_rad(270 - r_ang)));
	if (t_crd[0] < 0)
		return (0);
	else
		return (t_crd[0]);
}

long long	get_up_left_door_x(long long *t_crd, double *s_crd, double r_ang)
{
	t_crd[0] = s_crd[0] - \
	((s_crd[1] - t_crd[1]) / tan(conv_to_rad(r_ang - 270)));
	if (t_crd[0] < 0)
		return (0);
	else
		return (t_crd[0]);
}
