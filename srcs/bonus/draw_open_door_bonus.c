#include "cubed_bonus.h"

void	execute_open_door_drawing(t_data *data, int column, double wall_height)
{
	int		start_coord;

	start_coord = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	start_coord = draw_wall(data, (column * 4), wall_height, start_coord);
	data->found_open_door_vert = 0;
	data->found_open_door_horiz = 0;
}

void	get_open_door_pixels(t_data *data)
{
	char		direction;
	int			iterator;
	long long	x;
	long long	y;

	// separate function
	if (data->v_h_flag == 0 && data->player_coord[0] > data->vert_inters_crd[0])
		direction = 'W';
	else if (data->v_h_flag == 0)
		direction = 'E';
	else if (data->v_h_flag == 1 && data->player_coord[1] > data->horiz_inters_crd[1])
		direction = 'N';
	else
		direction = 'S';

	iterator = 2;
	if (data->found_open_door_vert == 1)
	{
		x = data->open_door_coord_vert[0];
		y = data->open_door_coord_vert[1];
		iterator = data->map[y][x].open_img_iter;
		if (direction == 'W')
			data->pixels = data->door_open_img[iterator][3]->pixels;
		else
			data->pixels = data->door_open_img[iterator][1]->pixels;
	}
	else if (data->found_open_door_horiz == 1)
	{
		x = data->open_door_coord_horiz[0];
		y = data->open_door_coord_horiz[1];
		iterator = data->map[y][x].open_img_iter;
		if (direction == 'N')
			data->pixels = data->door_open_img[iterator][0]->pixels;
		else
			data->pixels = data->door_open_img[iterator][2]->pixels;
	}
}

void	draw_open_door_pixels(t_data *data, double wall_height)
{
	int		column_to_draw;
	
	data->pixels = data->door_open_img[2][0]->pixels;
	if (data->v_h_flag == 0)
	{
		if (data->found_open_door_vert == 0)
		{
			data->found_open_door_horiz = 0;
			return ;
		}
		column_to_draw = (int)data->vert_inters_crd[1] % IMG_SIZE;
		get_open_door_pixels(data);
	}
	else
	{
		if (data->found_open_door_horiz == 0)
		{
			data->found_open_door_vert = 0;
			return ;
		}
		column_to_draw = (int)data->horiz_inters_crd[0] % IMG_SIZE;
		get_open_door_pixels(data);
	}
	execute_open_door_drawing(data, column_to_draw, wall_height);
}

int	check_for_open_door(t_data *data, long long *check_coord, char vh_flag, double ray_angle)
{
	long long	x;
	long long	y;

	x = check_coord[0];
	y = check_coord[1];

	if (x < 0 || y < 0)
	{
		if (vh_flag == 'V')
			data->invalid_vert = 1;
		else
			data->invalid_horiz = 1;
		return (1);
	}
	else if (data->map[y][x].type == 'X')
	{
		if (vh_flag == 'V')
			data->invalid_vert = 1;
		else
			data->invalid_horiz = 1;
		return (1);
	}

	/*
Add here a check: if player is in a tile that has open door in it 
--> you should check if ray hits door
Sadly, this needs it's own separate checking function :(
*/

	if (data->map[y][x].type == '1')
		return (1);
	else if (data->map[y][x].is_open == 1)
	{
		if (vh_flag == 'V' && check_if_ray_hits_door_vert(data, ray_angle) == 1)
		{
			data->found_open_door_vert = 1;
			data->open_door_coord_vert[0] = x;
			data->open_door_coord_vert[1] = y;
			return (1);
		}
		else if (vh_flag == 'H' && check_if_ray_hits_door_horiz(data, ray_angle) == 1)
		{
			data->found_open_door_horiz = 1;
			data->open_door_coord_horiz[0] = x;
			data->open_door_coord_horiz[1] = y;
			return (1);
		}
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
	while (check_for_open_door(data, vert_coords, 'V', ray_angle) != 1)
		get_vert_intersection(data, ray_angle, vert_coords, i++);
	get_horizon_intersection(data, ray_angle, horiz_coords, 0);
	i = 1;
	while (check_for_open_door(data, horiz_coords, 'H', ray_angle) != 1)
		get_horizon_intersection(data, ray_angle, horiz_coords, i++);
	return (compare_distance(data, ray_angle));
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
		draw_open_door_pixels(data, drawn_door_height);
		data->ray_iterator++;
		ray_angle = ray_angle + addition;
		if (ray_angle > 360)
			ray_angle = 0;
	}
	data->handling_open_door = 0;
}
