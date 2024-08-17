/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_draw_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:02:14 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/17 13:02:15 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	get_enemy_player_angle(t_data *data, double *enemy_player_angle, \
double y_x_ratio, int i)
{
	if (data->enemy[i].x >= data->player_coord[0] \
	&& data->enemy[i].y < data->player_coord[1])
		*enemy_player_angle = 90.0 - conv_to_deg(atan(y_x_ratio));
	else if (data->enemy[i].x >= data->player_coord[0] \
	&& data->enemy[i].y >= data->player_coord[1])
		*enemy_player_angle = 90.0 + conv_to_deg(atan(y_x_ratio));
	else if (data->enemy[i].x < data->player_coord[0] \
	&& data->enemy[i].y >= data->player_coord[1])
		*enemy_player_angle = 270.0 - conv_to_deg(atan(y_x_ratio));
	else
		*enemy_player_angle = 270.0 + conv_to_deg(atan(y_x_ratio));
}

void	draw_enemy(t_data *data, double draw_height, \
double enemy_player_angle, double dist_to_enemy)
{
	double		addition;
	double		enemy_lim[2];
	double		ray_angle;
	long long	start_coord;
	double		p_fov_limits[2];

	set_player_fov(data, p_fov_limits);
	set_enemy_limits(enemy_lim, enemy_player_angle, dist_to_enemy);
	addition = 60.0 / WINDOW_WIDTH;
	data->ray_iterator = get_ray_iterator(enemy_lim[0], p_fov_limits[0]);
	ray_angle = enemy_lim[0];
	skip_extra_rays(data, &ray_angle, addition);
	if (ray_angle > 270 && enemy_lim[1] < 90)
		enemy_lim[1] += 360;
	get_enemy_pixels(data, data->enemy_iter, enemy_player_angle);
	while (data->ray_iterator < WINDOW_WIDTH && ray_angle <= enemy_lim[1])
	{
		start_coord = (WINDOW_HEIGHT / 2) - (draw_height / 2) \
		+ data->enemy[data->enemy_iter].enemy_anim_height_iter;
		if (dist_to_enemy <= data->dist_to_wall_list[data->ray_iterator])
			enemy_draw_execute(data, (get_column(enemy_lim, ray_angle) * 4), \
			draw_height, start_coord);
		ray_angle += addition;
		data->ray_iterator++;
	}
}

double	is_enemy_visible(t_data *data, int i, double *enemy_p_angle)
{
	double		xy_diff[2];
	double		y_x_ratio;
	double		p_fov_limits[2];

	if (data->enemy[i].is_dead == 1)
		return (-1);
	get_xy_diff(data, i, &xy_diff[0], &xy_diff[1]);
	p_fov_limits[0] = data->player_angle - 30;
	p_fov_limits[1] = data->player_angle + 30;
	if (xy_diff[0] == 0 || xy_diff[1] == 0)
		return (handle_exception(data, xy_diff, enemy_p_angle, p_fov_limits));
	y_x_ratio = xy_diff[1] / xy_diff[0];
	get_enemy_player_angle(data, enemy_p_angle, y_x_ratio, i);
	fix_fov_limits(data, enemy_p_angle, p_fov_limits);
	if (p_fov_limits[0] < *enemy_p_angle \
	&& p_fov_limits[1] > *enemy_p_angle)
		return (sqrt(pow(xy_diff[0], 2) + pow(xy_diff[1], 2)));
	else
		return (-1);
}

void	check_enemy_visibility(t_data *data)
{
	int		i;
	double	dist_to_enemy;
	double	enemy_player_angle;

	data->enemy_iter = -1;
	while (++data->enemy_iter < data->enemy_count)
	{
		i = data->enemy_iter;
		dist_to_enemy = is_enemy_visible(data, i, &enemy_player_angle);
		data->enemy[i].angle_to_player = enemy_player_angle;
		data->enemy[i].distance_to_player = dist_to_enemy;
	}
}

void	draw_enemy_loop(t_data *data)
{
	int		i;
	double	dist_to_enemy;
	double	draw_height;
	double	enemy_player_angle;

	enemy_player_angle = 0;
	check_enemy_visibility(data);
	get_draw_order(data);
	data->enemy_iter = -1;
	i = -1;
	while (++i < data->enemy_count)
	{
		data->enemy_iter = data->draw_order[i];
		dist_to_enemy = data->enemy[data->enemy_iter].distance_to_player;
		enemy_player_angle = data->enemy[data->enemy_iter].angle_to_player;
		if (dist_to_enemy != -1 && dist_to_enemy > 100)
		{
			draw_height = (IMG_SIZE / dist_to_enemy) * PP_DIST;
			draw_enemy(data, draw_height, enemy_player_angle, dist_to_enemy);
		}
	}
	free(data->draw_order);
	data->draw_order = NULL;
}
