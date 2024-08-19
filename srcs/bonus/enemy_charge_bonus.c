#include "cubed_bonus.h"

int	check_enemy_wall_charge(t_data *data, int direction, int i)
{
	int	x_edge[2];
	int	y_edge[2];

	set_enemy_x_edges(data, x_edge, direction, i);
	set_enemy_y_edges(data, y_edge, direction, i);
	if (data->map[y_edge[0]][x_edge[0]].type == '1' \
	|| data->map[y_edge[0]][x_edge[0]].is_closing == 1)
		return (1);
	if (data->map[y_edge[1]][x_edge[0]].type == '1' \
	|| data->map[y_edge[1]][x_edge[0]].is_closing == 1)
		return (1);
	if (data->map[y_edge[0]][x_edge[1]].type == '1' \
	|| data->map[y_edge[0]][x_edge[1]].is_closing == 1)
		return (1);
	if (data->map[y_edge[1]][x_edge[1]].type == '1' \
	|| data->map[y_edge[1]][x_edge[1]].is_closing == 1)
		return (1);
	return (0);
}

void	set_enemy_fov_limits(t_data *data, int i, \
double *enemy_fov_limits, double en_perspect_ang)
{
	if (data->enemy[i].is_charging == 0)
	{
		enemy_fov_limits[0] = (data->enemy[i].direction * 90.0) - 30;
		enemy_fov_limits[1] = (data->enemy[i].direction * 90.0) + 30;
		if (data->enemy[i].direction == 0 && en_perspect_ang > 270)
		{
			enemy_fov_limits[0] += 360;
			enemy_fov_limits[1] += 360;
		}
	}
	else
	{
		enemy_fov_limits[0] = data->enemy[i].charge_dir - 30;
		enemy_fov_limits[1] = data->enemy[i].charge_dir + 30;
		if (data->enemy[i].charge_dir < 90 && en_perspect_ang > 270)
		{
			enemy_fov_limits[0] += 360;
			enemy_fov_limits[1] += 360;
		}
		else if (data->enemy[i].charge_dir > 270 && en_perspect_ang < 90)
		{
			enemy_fov_limits[0] -= 360;
			enemy_fov_limits[1] -= 360;
		}
	}
}

int	is_player_visible(t_data *data, int i)
{
	double	en_perspect_ang;
	double	enemy_fov_limits[2];
	double	wall_dist;
	double	player_dist;

	player_dist = data->enemy[i].distance_to_player;
	if (player_dist == -1)
		return (0);
	wall_dist = find_wall_distance(data, data->enemy[i].angle_to_player, 0.06);
	en_perspect_ang = data->enemy[i].angle_to_player - 180;
	if (en_perspect_ang < 0)
		en_perspect_ang += 360;
	set_enemy_fov_limits(data, i, enemy_fov_limits, en_perspect_ang);
	if (player_dist < 2000 && en_perspect_ang > enemy_fov_limits[0] \
	&& en_perspect_ang < enemy_fov_limits[1] \
	&& player_dist < wall_dist)
		return (1);
	else
		return (0);
}

void	move_enemy_charge(t_data *data, int i, double en_perspect_ang)
{
	if (en_perspect_ang < 90)
	{
		data->enemy[i].x += (CHARGE_SPEED * sin(conv_to_rad(en_perspect_ang)));
		data->enemy[i].y -= (CHARGE_SPEED * cos(conv_to_rad(en_perspect_ang)));
	}
	else if (en_perspect_ang < 180)
	{
		data->enemy[i].x += (CHARGE_SPEED * cos(conv_to_rad(en_perspect_ang - 90.0)));
		data->enemy[i].y += (CHARGE_SPEED * sin(conv_to_rad(en_perspect_ang - 90.0)));
	}
	else if (en_perspect_ang < 270)
	{
		data->enemy[i].x -= (CHARGE_SPEED * sin(conv_to_rad(en_perspect_ang - 180.0)));
		data->enemy[i].y += (CHARGE_SPEED * cos(conv_to_rad(en_perspect_ang - 180.0)));
	}
	else if (en_perspect_ang < 360)
	{
		data->enemy[i].x -= (CHARGE_SPEED * cos(conv_to_rad(en_perspect_ang - 270.0)));
		data->enemy[i].y -= (CHARGE_SPEED * sin(conv_to_rad(en_perspect_ang - 270.0)));
	}
}

int	get_enemy_dir(double en_perspect_ang)
{
	if (en_perspect_ang > 315 || en_perspect_ang <= 45)
		return (0);
	else if (en_perspect_ang > 45 && en_perspect_ang <= 135)
		return (1);
	else if (en_perspect_ang > 135 && en_perspect_ang <= 225)
		return (2);
	else
		return (3);
}

void	move_along_wall(t_data *data, int i, int enemy_dir)
{
	if (enemy_dir == 0 || enemy_dir == 2)
	{
		if (check_enemy_wall_charge(data, 1, i) == 1 || check_enemy_wall_charge(data, 3, i) == 1)
		{
			if (enemy_dir == 0)
				data->enemy[i].y -= CHARGE_SPEED;
			else
				data->enemy[i].y += CHARGE_SPEED;
		}
		else if (data->player_coord[0] < data->enemy[i].x)
			data->enemy[i].x -= CHARGE_SPEED;
		else if (data->player_coord[0] > data->enemy[i].x)
			data->enemy[i].x += CHARGE_SPEED;
	}
	else
	{
		if (check_enemy_wall_charge(data, 0, i) == 1 || check_enemy_wall_charge(data, 2, i) == 1)
		{
			if (enemy_dir == 1)
				data->enemy[i].x += CHARGE_SPEED;
			else
				data->enemy[i].x -= CHARGE_SPEED;
		}
		else if (data->player_coord[1] < data->enemy[i].y)
			data->enemy[i].y -= CHARGE_SPEED;
		else if (data->player_coord[1] > data->enemy[i].y)
			data->enemy[i].y += CHARGE_SPEED;
	}
}

void	enemy_charge(t_data *data, int i)
{
	double		en_perspect_ang;
	long long	orig_xy[2];
	int	enemy_dir;

	data->enemy[i].is_charging = 1;
	en_perspect_ang = data->enemy[i].angle_to_player - 180;
	if (en_perspect_ang < 0)
		en_perspect_ang += 360;
	if (en_perspect_ang == 0.000 || en_perspect_ang == 90.000 \
	|| en_perspect_ang == 180.000 || en_perspect_ang == 270.000)
		en_perspect_ang += 0.06;
	data->enemy[i].charge_dir = en_perspect_ang;
	orig_xy[0] = data->enemy[i].x;
	orig_xy[1] = data->enemy[i].y;
	enemy_dir = get_enemy_dir(en_perspect_ang);
	move_enemy_charge(data, i, en_perspect_ang);
	if (check_enemy_wall_charge(data, enemy_dir, i) == 1)
	{
		data->enemy[i].x = orig_xy[0];
		data->enemy[i].y = orig_xy[1];
		move_along_wall(data, i, enemy_dir);
	}
}
