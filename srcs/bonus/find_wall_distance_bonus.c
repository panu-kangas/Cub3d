#include "cubed_bonus.h"

int	handle_found_door(t_data *data, char vh_flag, double r_ang, long long *xy)
{
	if (vh_flag == 'V' && check_ray_door_vert(data, r_ang) == 1)
	{
		data->door_found_vert = 1;
		data->door_coord_v[0] = xy[0];
		data->door_coord_v[1] = xy[1];
		return (1);
	}
	else if (vh_flag == 'H' && check_ray_door_horiz(data, r_ang) == 1)
	{
		data->door_found_horiz = 1;
		data->door_coord_h[0] = xy[0];
		data->door_coord_h[1] = xy[1];
		return (1);
	}
	return (0);
}

int	check_for_wall(t_data *data, long long *check_coord, \
char vh_flag, double r_ang)
{
	long long	xy[2];

	xy[0] = check_coord[0];
	xy[1] = check_coord[1];
	if (check_invalid_coords(data, check_coord, vh_flag) == 1)
		return (1);
	if (data->map[xy[1]][xy[0]].type == '1')
	{
		if (data->map[xy[1]][xy[0]].is_door == 1)
			return (handle_found_door(data, vh_flag, r_ang, xy));
		if (data->map[xy[1]][xy[0]].is_exit == 1)
			data->is_exit = 1;
		return (1);
	}
	return (0);
}

void	get_horizon_intersection(t_data *data, double ray_angle, \
long long *w_coord, int cnt)
{
	long long	*p_crd;
	long long	temp_coord[2];

	p_crd = data->player_coord;
	if (ray_angle < 90 || ray_angle > 270)
	{
		temp_coord[1] = (p_crd[1] - (p_crd[1] % IMG_SIZE)) - (cnt * IMG_SIZE);
		w_coord[1] = (temp_coord[1] - 1) / IMG_SIZE;
	}
	else
	{
		temp_coord[1] = (p_crd[1] + (IMG_SIZE - (p_crd[1] % IMG_SIZE))) \
		+ (cnt * IMG_SIZE);
		w_coord[1] = (temp_coord[1] + 1) / IMG_SIZE;
	}
	if (ray_angle < 90)
		w_coord[0] = get_up_right_x(data, temp_coord, ray_angle);
	else if (ray_angle > 90 && ray_angle < 180)
		w_coord[0] = get_down_right_x(data, temp_coord, ray_angle);
	else if (ray_angle > 180 && ray_angle < 270)
		w_coord[0] = get_down_left_x(data, temp_coord, ray_angle);
	else
		w_coord[0] = get_up_left_x(data, temp_coord, ray_angle);
	data->horiz_inters_crd[0] = temp_coord[0];
	data->horiz_inters_crd[1] = temp_coord[1];
}

void	get_vert_intersection(t_data *data, double ray_angle, \
long long *w_coord, int cnt)
{
	long long	*p_crd;
	long long	temp_coord[2];

	p_crd = data->player_coord;
	if (ray_angle < 180)
	{
		temp_coord[0] = (p_crd[0] + (IMG_SIZE - (p_crd[0] % IMG_SIZE))) \
		+ (cnt * IMG_SIZE);
		w_coord[0] = (temp_coord[0] + 1) / IMG_SIZE;
	}
	else
	{
		temp_coord[0] = (p_crd[0] - (p_crd[0] % IMG_SIZE)) - (cnt * IMG_SIZE);
		w_coord[0] = (temp_coord[0] - 1) / IMG_SIZE;
	}
	if (ray_angle < 90)
		w_coord[1] = get_up_right_y(data, temp_coord, ray_angle);
	else if (ray_angle > 90 && ray_angle < 180)
		w_coord[1] = get_down_right_y(data, temp_coord, ray_angle);
	else if (ray_angle > 180 && ray_angle < 270)
		w_coord[1] = get_down_left_y(data, temp_coord, ray_angle);
	else
		w_coord[1] = get_up_left_y(data, temp_coord, ray_angle);
	data->vert_inters_crd[0] = temp_coord[0];
	data->vert_inters_crd[1] = temp_coord[1];
}

double	find_wall_distance(t_data *data, double ray_angle, double addition)
{
	int			i;
	long long	vert_coords[2];
	long long	horiz_coords[2];

	data->invalid_vert = 0;
	data->invalid_horiz = 0;
	if (ray_angle == 0.0000 || ray_angle - 90.0000 == 0 \
	|| ray_angle - 180.0000 == 0 || ray_angle - 270.0000 == 0)
		ray_angle += addition;
	get_vert_intersection(data, ray_angle, vert_coords, 0);
	i = 1;
	while (check_for_wall(data, vert_coords, 'V', ray_angle) != 1)
		get_vert_intersection(data, ray_angle, vert_coords, i++);
	get_horizon_intersection(data, ray_angle, horiz_coords, 0);
	i = 1;
	while (check_for_wall(data, horiz_coords, 'H', ray_angle) != 1)
		get_horizon_intersection(data, ray_angle, horiz_coords, i++);
	return (compare_distance(data, ray_angle));
}
