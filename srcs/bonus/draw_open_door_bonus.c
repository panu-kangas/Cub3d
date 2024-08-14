#include "cubed_bonus.h"

int	handle_open_door_found(t_data *data, char vh_flag, \
double ray_angle, long long *xy)
{
	if (vh_flag == 'V' && check_ray_door_vert(data, ray_angle) == 1)
	{
		if (data->open_door_count > 1)
			data->open_door_count--;
		else
		{
			data->found_open_door_vert = 1;
			data->open_door_coord_vert[0] = xy[0];
			data->open_door_coord_vert[1] = xy[1];
			return (1);
		}
	}
	else if (vh_flag == 'H' && check_ray_door_horiz(data, ray_angle) == 1)
	{
		if (data->open_door_count > 1)
			data->open_door_count--;
		else
		{
			data->found_open_door_horiz = 1;
			data->open_door_coord_horiz[0] = xy[0];
			data->open_door_coord_horiz[1] = xy[1];
			return (1);
		}
	}
	return (0);
}

int	check_for_open_door(t_data *data, long long *check_coord, \
char vh_flag, double ray_angle)
{
	long long	xy[2];

	xy[0] = check_coord[0];
	xy[1] = check_coord[1];
	if (check_invalid_coords(data, check_coord, vh_flag) == 1)
		return (1);
	if (data->map[xy[1]][xy[0]].type == '1')
		return (1);
	else if (data->map[xy[1]][xy[0]].is_open == 1)
		return (handle_open_door_found(data, vh_flag, ray_angle, xy));
	return (0);
}

double	find_open_door_distance(t_data *data, double ray_angle, double addit)
{
	int			i;
	long long	vert_coords[2];
	long long	horiz_coords[2];

	data->invalid_vert = 0;
	data->invalid_horiz = 0;
	if (ray_angle == 0.0000 || ray_angle - 90.0000 == 0 \
	|| ray_angle - 180.0000 == 0 || ray_angle - 270.0000 == 0)
		ray_angle += addit;
	get_vert_intersection(data, ray_angle, vert_coords, 0);
	i = 1;
	while (check_for_open_door(data, vert_coords, 'V', ray_angle) != 1)
		get_vert_intersection(data, ray_angle, vert_coords, i++);
	get_horizon_intersection(data, ray_angle, horiz_coords, 0);
	i = 1;
	while (check_for_open_door(data, horiz_coords, 'H', ray_angle) != 1)
		get_horizon_intersection(data, ray_angle, horiz_coords, i++);
	return (compare_distance(data, ray_angle));
}

void	draw_open_door(t_data *data, double ray_angle, \
double window_width, int counter)
{
	double	dist_to_door;
	double	drawn_door_height;
	double	addit;

	data->handling_open_door = 1;
	if (ray_angle < 0)
		ray_angle = 360 - (ray_angle * -1);
	data->ray_iterator = 0;
	addit = 60.0 / window_width;
	while (data->ray_iterator < WINDOW_WIDTH)
	{
		counter = handle_open_door_counter(data, counter, ray_angle, addit);
		data->open_door_count = counter;
		dist_to_door = find_open_door_distance(data, ray_angle, addit);
		drawn_door_height = (IMG_SIZE / dist_to_door) * PP_DIST;
		draw_open_door_pixels(data, dist_to_door, drawn_door_height);
		if (--counter <= 0)
		{
			data->ray_iterator++;
			ray_angle = ray_angle + addit;
			if (ray_angle > 360)
				ray_angle -= 360;
		}
	}
	data->handling_open_door = 0;
}
