#include "cubed_bonus.h"

void	get_xy_diff(t_data *data, int i, double *x_diff, double *y_diff)
{
	*x_diff = data->player_coord[0] - data->enemy[i].x;
	if (*x_diff < 0)
		*x_diff = *x_diff * -1.0;
	*y_diff = data->player_coord[1] - data->enemy[i].y;
	if (*y_diff < 0)
		*y_diff = *y_diff * -1.0;
}

void	fix_fov_limits(t_data *data, double *enemy_player_angle, \
double *p_fov_limits)
{
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
}

double	handle_y_is_zero(t_data *data, double *enemy_player_angle, \
double *p_fov_limits)
{
	int	i;

	i = data->enemy_iter;
	if (data->player_coord[0] > data->enemy[i].x)
	{
		*enemy_player_angle = 270;
		if (p_fov_limits[0] < *enemy_player_angle \
		&& p_fov_limits[1] > *enemy_player_angle)
			return (data->player_coord[0] - data->enemy[i].x);
	}
	else
	{
		*enemy_player_angle = 90;
		if (p_fov_limits[0] < *enemy_player_angle \
		&& p_fov_limits[1] > *enemy_player_angle)
			return (data->enemy[i].x - data->player_coord[0]);
	}
	return (-1);
}

double	handle_exception(t_data *data, double *xy_diff, \
double *enemy_player_angle, double *p_fov_limits)
{
	int	i;

	i = data->enemy_iter;
	if (xy_diff[0] == 0)
	{
		if (data->player_coord[1] > data->enemy[i].y)
		{
			*enemy_player_angle = 0;
			fix_fov_limits(data, enemy_player_angle, p_fov_limits);
			if (p_fov_limits[0] < *enemy_player_angle \
			&& p_fov_limits[1] > *enemy_player_angle)
				return (data->player_coord[1] - data->enemy[i].y);
		}
		else
		{
			*enemy_player_angle = 180;
			if (p_fov_limits[0] < *enemy_player_angle \
			&& p_fov_limits[1] > *enemy_player_angle)
				return (data->enemy[i].y - data->player_coord[1]);
		}
	}
	else
		return (handle_y_is_zero(data, enemy_player_angle, p_fov_limits));
	return (-1);
}
