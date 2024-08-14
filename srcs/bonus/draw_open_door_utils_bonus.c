#include "cubed_bonus.h"

int	handle_open_door_counter(t_data *data, int counter, \
double ray_angle, double addition)
{
	if (counter <= 0)
	{
		count_open_doors(data, ray_angle, addition);
		counter = data->open_door_count;
	}
	return (counter);
}

void	update_wall_dist_list(t_data *data, int dist, int column, int iter)
{
	int	wall_limits[2];

	if (iter == 0)
		data->dist_to_wall_list[data->ray_iterator] = dist;
	else if (iter == 1)
	{
		wall_limits[0] = 43;
		wall_limits[1] = 78;
	}
	else if (iter == 2)
	{
		wall_limits[0] = 29;
		wall_limits[1] = 99;
	}
	if (dist < data->dist_to_wall_list[data->ray_iterator] \
	&& (column < wall_limits[0] || column > wall_limits[1]))
		data->dist_to_wall_list[data->ray_iterator] = dist;
}

char	get_open_door_direction(t_data *data)
{
	char	direction;

	if (data->v_h_flag == 0 && data->player_coord[0] > data->vert_inters_crd[0])
		direction = 'E';
	else if (data->v_h_flag == 0)
		direction = 'W';
	else if (data->v_h_flag == 1 \
	&& data->player_coord[1] > data->horiz_inters_crd[1])
		direction = 'S';
	else
		direction = 'N';
	return (direction);
}

void	set_open_door_iterator(t_data *data, long long *xy, int *iterator)
{
	if (data->found_open_door_vert == 1)
	{
		xy[0] = data->open_door_coord_vert[0];
		xy[1] = data->open_door_coord_vert[1];
		*iterator = data->map[xy[1]][xy[0]].open_img_iter;
	}
	else if (data->found_open_door_horiz == 1)
	{
		xy[0] = data->open_door_coord_horiz[0];
		xy[1] = data->open_door_coord_horiz[1];
		*iterator = data->map[xy[1]][xy[0]].open_img_iter;
	}
}
