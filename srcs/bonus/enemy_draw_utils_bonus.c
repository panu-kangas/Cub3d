/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw_utils_bonus.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:02:26 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/17 13:02:27 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

int	get_ray_iterator(double enemy_start_angle, double player_fov_start)
{
	double		addition;

	addition = 60.0 / WINDOW_WIDTH;
	if (player_fov_start < 90 && enemy_start_angle > 270)
		player_fov_start += 360;
	if (player_fov_start > 270 && enemy_start_angle < 90)
		player_fov_start -= 360;
	return ((enemy_start_angle - player_fov_start) / addition);
}

void	set_player_fov(t_data *data, double *player_fov_limits)
{
	player_fov_limits[0] = data->player_angle - 30.0;
	if (player_fov_limits[0] < 0)
		player_fov_limits[0] += 360;
	player_fov_limits[1] = data->player_angle + 30.0;
	if (player_fov_limits[1] > 360)
		player_fov_limits[1] -= 360;
}

void	set_enemy_limits(double *enemy_limits, double enemy_player_angle, \
double dist_to_enemy)
{
	enemy_limits[0] = enemy_player_angle \
	- conv_to_deg(atan((ENEMY_WIDTH / 2) / dist_to_enemy));
	enemy_limits[1] = enemy_player_angle \
	+ conv_to_deg(atan((ENEMY_WIDTH / 2) / dist_to_enemy));
	if (enemy_limits[0] < 0)
		enemy_limits[0] += 360;
	if (enemy_limits[1] > 360)
		enemy_limits[1] -= 360;
}

void	skip_extra_rays(t_data *data, double *ray_angle, double addition)
{
	while (data->ray_iterator < 0)
	{
		*ray_angle = *ray_angle + addition;
		if (*ray_angle > 360)
			*ray_angle -= 360;
		data->ray_iterator++;
	}
}
