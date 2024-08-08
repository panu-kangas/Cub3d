#include "cubed_bonus.h"

void  get_xy_diff(t_data *data, double *x_diff, double *y_diff)
{
	*x_diff = data->player_coord[0] - data->enemy[0].x;
	if (*x_diff < 0)
		*x_diff = *x_diff * -1.0;
	*y_diff = data->player_coord[1] - data->enemy[0].y;
	if (*y_diff < 0)
		*y_diff = *y_diff * -1.0;
}

double	handle_xy_exception(t_data *data, double *xy_diff, double *enemy_player_angle, double *p_fov_limits)
{
	if (xy_diff[0] == 0)
	{
		if (data->player_coord[1] > data->enemy[0].y)
		{
			*enemy_player_angle = 0;
			if (data->player_angle < 30 && *enemy_player_angle > 270) // own checker function
			{
				p_fov_limits[0] += 360;
				p_fov_limits[1] += 360;
			}
			if (data->player_angle > 320 && *enemy_player_angle < 60)
			{
				p_fov_limits[0] -= 360;
				p_fov_limits[1] -= 360;
			}
			if (p_fov_limits[0] < *enemy_player_angle && p_fov_limits[1] > *enemy_player_angle)
				return (data->player_coord[1] - data->enemy[0].y);
		}
		else
		{
			*enemy_player_angle = 180;
			if (p_fov_limits[0] < *enemy_player_angle && p_fov_limits[1] > *enemy_player_angle)
				return (data->enemy[0].y - data->player_coord[1]);
		}
	}
	else if (xy_diff[1] == 0)
	{
		if (data->player_coord[0] > data->enemy[0].x)
		{
			*enemy_player_angle = 270;
			if (p_fov_limits[0] < *enemy_player_angle && p_fov_limits[1] > *enemy_player_angle)
				return (data->player_coord[0] - data->enemy[0].x);
		}
		else
		{
			*enemy_player_angle = 90;
			if (p_fov_limits[0] < *enemy_player_angle && p_fov_limits[1] > *enemy_player_angle)
				return (data->enemy[0].x - data->player_coord[0]);
		}
	}
	return (-1);
}

double	is_enemy_visible(t_data *data, int i, double *enemy_player_angle)
{
	double		xy_diff[2];
	double		y_x_ratio;
	double		p_fov_limits[2];

	if (data->enemy[i].is_dead == 1)
		return (-1);

	get_xy_diff(data, &xy_diff[0], &xy_diff[1]);

	p_fov_limits[0] = data->player_angle - 30;
	p_fov_limits[1] = data->player_angle + 30;

	if (xy_diff[0] == 0 || xy_diff[1] == 0)
		return (handle_xy_exception(data, xy_diff, enemy_player_angle, p_fov_limits));
	else
		y_x_ratio = xy_diff[1] / xy_diff[0];

	if (data->enemy[i].x >= data->player_coord[0] && data->enemy[i].y < data->player_coord[1])
		*enemy_player_angle = 90.0 - convert_to_degrees(atan(y_x_ratio));
	else if (data->enemy[i].x >= data->player_coord[0] && data->enemy[i].y >= data->player_coord[1])
		*enemy_player_angle = 90.0 + convert_to_degrees(atan(y_x_ratio));
	else if  (data->enemy[i].x < data->player_coord[0] && data->enemy[i].y >= data->player_coord[1])
		*enemy_player_angle = 270.0 - convert_to_degrees(atan(y_x_ratio));
	else
		*enemy_player_angle = 270.0 + convert_to_degrees(atan(y_x_ratio));

//	check_enemy_start_angle(); 
//	check_enemy_end_angle(); --> with these we could draw enemy, even if just a bit of it is visible

	if (data->player_angle < 90 && *enemy_player_angle > 270)
	{
		p_fov_limits[0] += 360;
		p_fov_limits[1] += 360;
	}
	if (data->player_angle > 270 && *enemy_player_angle < 90)
	{
		p_fov_limits[0] -= 360;
		p_fov_limits[1] -= 360;
	}

	if (p_fov_limits[0] < *enemy_player_angle && p_fov_limits[1] > *enemy_player_angle)
		return (sqrt(pow(xy_diff[0], 2) + pow(xy_diff[1], 2)));
	else
		return (-1);

}

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

void	enemy_to_screen(t_data *data, double drawn_enemy_height, \
double enemy_player_angle, double dist_to_enemy)
{
	double		addition;
	double		enemy_limits[2];
	double		ray_angle;
	long long	start_coord;
	double		player_fov_limits[2];

	player_fov_limits[0] = data->player_angle - 30.0;
	if (player_fov_limits[0] < 0)
		player_fov_limits[0] += 360;
	player_fov_limits[1] = data->player_angle + 30.0;
	if (player_fov_limits[1] > 360)
		player_fov_limits[1] -= 360;

	addition = 60.0 / WINDOW_WIDTH;
	enemy_limits[0] = enemy_player_angle - convert_to_degrees(atan((ENEMY_WIDTH / 2) / dist_to_enemy));
	enemy_limits[1] = enemy_player_angle + convert_to_degrees(atan((ENEMY_WIDTH / 2) / dist_to_enemy));
	if (enemy_limits[0] < 0)
		enemy_limits[0] += 360;
	if (enemy_limits[1] > 360)
		enemy_limits[1] -= 360;

	data->ray_iterator = get_ray_iterator(enemy_limits[0], player_fov_limits[0]);
	ray_angle = enemy_limits[0];
	while (data->ray_iterator < 0)
	{
		ray_angle += addition;
		if (ray_angle > 360)
			ray_angle -= 360;
		data->ray_iterator++;
	}

	if (ray_angle > 270 && enemy_limits[1] < 90)
		enemy_limits[1] += 360;

	get_enemy_pixels(data, 0, enemy_player_angle);
	while (data->ray_iterator < WINDOW_WIDTH && ray_angle <= enemy_limits[1])
	{
		start_coord = (WINDOW_HEIGHT / 2) - (drawn_enemy_height / 2) + data->enemy_anim_height_iter;
		if (dist_to_enemy < data->dist_to_wall_list[data->ray_iterator])
			put_enemy_pixel(data, start_coord, enemy_limits, ray_angle, drawn_enemy_height);
		ray_angle += addition;
		data->ray_iterator++;
	}
}

void    draw_enemy(t_data *data)
{
	int		i;
	double	dist_to_enemy;
	double	drawn_enemy_height;
	double	enemy_player_angle;

	i = 0;
	enemy_player_angle = 0;
//	data->enemy_start_visible = 0;
//	data->enemy_end_visible = 0;
	while (i < data->enemy_count)
	{
		dist_to_enemy = is_enemy_visible(data, i, &enemy_player_angle);
		data->enemy[i].angle_to_player = enemy_player_angle;
		data->enemy[i].distance_to_player = dist_to_enemy;
		if (dist_to_enemy != -1)
		{
			drawn_enemy_height = (IMG_SIZE / dist_to_enemy) * PP_DIST;
			enemy_to_screen(data, drawn_enemy_height, enemy_player_angle, dist_to_enemy);
		}
		i++;
	}
}


