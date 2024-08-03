#include "cubed_bonus.h"

void	execute_open_door_drawing(t_data *data, int column, double wall_height)
{
	int		start_coord;

	start_coord = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	start_coord = draw_wall(data, (column * 4), wall_height, start_coord);

	data->found_open_door_vert = 0;
	data->found_open_door_horiz = 0;
}

void	draw_open_door_pixels(t_data *data, double wall_height)
{
	int		column_to_draw;

	data->pixels = data->door_open_img->pixels;
	if (data->v_h_flag == 0)
	{
		if (data->found_open_door_vert == 0)
		{
			data->found_open_door_horiz = 0;
			return ;
		}
		column_to_draw = (int)data->vert_intersection_coord[1] % IMG_SIZE;
		fix_open_door_img(data, data->wall_img_n); // TEST, change the wall img given based on intersection
	}
	else
	{
		if (data->found_open_door_horiz == 0)
		{
			data->found_open_door_vert = 0;
			return ;
		}
		column_to_draw = (int)data->horizon_intersection_coord[0] % IMG_SIZE;
		fix_open_door_img(data, data->wall_img_n); // TEST, change the wall img given based on intersection
	}
	execute_open_door_drawing(data, column_to_draw, wall_height);
}

int	check_for_open_door(t_data *data, long long *check_coord, char vh_flag)
{
	long long	x;
	long long	y;

	x = check_coord[0];
	y = check_coord[1];
	if (data->map[y][x].type == '1')
		return (1);
	else if (data->map[y][x].is_open == 1)
	{
		if (vh_flag == 'V')
			data->found_open_door_vert = 1;
		else
			data->found_open_door_horiz = 1;
		return (1);
	}
	return (0);
}

double	find_open_door_distance(t_data *data, double ray_angle, double addition)
{
	int			i;
	long long	vert_coords[2];
	long long	horiz_coords[2];

	if (ray_angle == 0.0000 || ray_angle - 90.0000 == 0 \
	|| ray_angle - 180.0000 == 0 || ray_angle - 270.0000 == 0)
		ray_angle += addition;
	get_vert_intersection(data, ray_angle, vert_coords, 0);
	i = 1;
	while (check_for_open_door(data, vert_coords, 'V') != 1)
		get_vert_intersection(data, ray_angle, vert_coords, i++);
	get_horizon_intersection(data, ray_angle, horiz_coords, 0);
	i = 1;
	while (check_for_open_door(data, horiz_coords, 'H') != 1)
		get_horizon_intersection(data, ray_angle, horiz_coords, i++);
	return (compare_distance(data, ray_angle, vert_coords, horiz_coords));
}

void	draw_open_door(t_data *data, double ray_angle, double window_width)
{
	double	dist_to_door;
	double	drawn_door_height;
	double	addition;

	data->handling_open_door = 1;
	if (ray_angle < 0)
		ray_angle = 360 - (ray_angle * -1);
	data->ray_iterator = 0;
	addition = 60.0 / window_width;
	while (data->ray_iterator < WINDOW_WIDTH)
	{
		dist_to_door = find_open_door_distance(data, ray_angle, addition);
		drawn_door_height = (IMG_SIZE / dist_to_door) * PP_DIST;
		drawn_door_height += 30; // TEST
		draw_open_door_pixels(data, drawn_door_height);
		data->ray_iterator++;
		ray_angle = ray_angle + addition;
		if (ray_angle > 360)
			ray_angle = 0;
	}
	data->handling_open_door = 0;

}
