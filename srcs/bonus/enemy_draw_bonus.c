#include "cubed_bonus.h"

void  get_xy_diff(t_data *data, double *x_diff, double *y_diff)
{
	*x_diff = data->player_coord[0] - data->enemy[0].e_coord[0];
	if (*x_diff < 0)
		*x_diff *= -1;
	else if (*x_diff == 0)
		*x_diff += 10;
	*y_diff = data->player_coord[1] - data->enemy[0].e_coord[1];
	if (*y_diff < 0)
		*y_diff *= -1;
	else if (*y_diff == 0)
		*y_diff += 10;
}


double	is_enemy_visible(t_data *data, int i, double *enemy_world_angle)
{
	double		x_diff;
	double		y_diff;

	get_xy_diff(data, &x_diff, &y_diff);

	if (data->enemy[i].e_coord[0] >= data->player_coord[0] && data->enemy[i].e_coord[1] < data->player_coord[1])
		*enemy_world_angle = 90.0 - convert_to_degrees(atan(y_diff / x_diff));
	else if (data->enemy[i].e_coord[0] >= data->player_coord[0] && data->enemy[i].e_coord[1] >= data->player_coord[1])
		*enemy_world_angle = 90.0 + convert_to_degrees(atan(y_diff / x_diff));
	else if  (data->enemy[i].e_coord[0] < data->player_coord[0] && data->enemy[i].e_coord[1] >= data->player_coord[1])
		*enemy_world_angle = 270.0 - convert_to_degrees(atan(y_diff / x_diff));
	else
		*enemy_world_angle = 270.0 + convert_to_degrees(atan(y_diff / x_diff));

	if (data->player_angle - 30 < *enemy_world_angle && data->player_angle + 30 > *enemy_world_angle)
		return (sqrt(pow(x_diff, 2) + pow(y_diff, 2)));
	else
		return (-1);

}
int	get_ray_iterator(double enemy_world_angle, double player_fov_start)
{
	double		addition;

	addition = 60.0 / WINDOW_WIDTH;

	if (player_fov_start < enemy_world_angle)
		return ((enemy_world_angle - player_fov_start) / addition);
	else
	{
		enemy_world_angle += 360;
		return ((enemy_world_angle - player_fov_start) / addition);
	}
}

void	enemy_to_screen(t_data *data, double drawn_enemy_height, \
double enemy_world_angle, double dist_to_enemy)
{
	double		addition;
	double		ray_angle;
	double		enemy_start_angle;
	long long	start_coord;
	long long	orig_start;

	double		player_fov_start;
	double		player_fov_end;

	player_fov_start = data->player_angle - 30.0;
	if (player_fov_start < 0)
		player_fov_start += 360;
	player_fov_end = data->player_angle + 30.0;
	if (player_fov_end > 360)
		player_fov_end -= 360;


	addition = 60.0 / WINDOW_WIDTH;
	ray_angle = enemy_world_angle;
	enemy_start_angle = enemy_world_angle - convert_to_degrees(atan((ENEMY_WIDTH / 2) / dist_to_enemy)); // FIX
	data->ray_iterator = get_ray_iterator(enemy_world_angle, player_fov_start);
	

	while (data->ray_iterator > 0 && ray_angle >= enemy_start_angle)
	{
		start_coord = (WINDOW_HEIGHT / 2) - (drawn_enemy_height / 2);
		orig_start = start_coord;

	//	printf("START FIRST: %lld, ray_iter: %d\n", start_coord, data->ray_iterator);
	//	printf("Drawn_height FIRST: %f\n\n", drawn_enemy_height);

		while (start_coord < (orig_start + drawn_enemy_height))
			mlx_put_pixel(data->door_canvas, data->ray_iterator, start_coord++, get_rgba(255, 255, 255, 255));
		ray_angle -= addition;
		if (ray_angle < 0)
			ray_angle += 360;
		data->ray_iterator--;
	}

	double		enemy_end_angle;

	ray_angle = enemy_world_angle;
	enemy_end_angle = enemy_world_angle + convert_to_degrees(atan((ENEMY_WIDTH / 2) / dist_to_enemy)); // FIX
	data->ray_iterator = get_ray_iterator(enemy_world_angle, player_fov_start);

	while (data->ray_iterator < WINDOW_WIDTH && ray_angle <= enemy_end_angle)
	{
		start_coord = (WINDOW_HEIGHT / 2) - (drawn_enemy_height / 2);
		orig_start = start_coord;

	//	printf("START SECOND: %lld, ray_iter: %d\n", start_coord, data->ray_iterator);
	//	printf("Drawn_height SECOND: %f\n\n", drawn_enemy_height);

		while (start_coord < (orig_start + drawn_enemy_height))
			mlx_put_pixel(data->door_canvas, data->ray_iterator, start_coord++, get_rgba(255, 255, 255, 255));
		ray_angle += addition;
		if (ray_angle > 360)
			ray_angle -= 360;
		data->ray_iterator++;
	}


	if (drawn_enemy_height == 0 || enemy_world_angle == -100 ||  dist_to_enemy == -9 || data == NULL)
		return ;
/*
	int	enemy_start_angle;

	enemy_start_angle = enemy_world_angle - convert_to_degrees(atan((ENEMY_WIDTH / 2) / dist_to_enemy));

	printf("enemy_world: %f, enemy_start: %f\n", enemy_world_angle, enemy_start_angle);

*/

}

void    draw_enemy(t_data *data)
{
	int		i;
	double	dist_to_enemy;
	double	drawn_enemy_height;
	double	enemy_world_angle;
//	double	addition;
//	double	window_width;

/*	ray_angle = data->player_angle - 30;
	if (ray_angle < 0)
		ray_angle = 360 - (ray_angle * -1);
	data->ray_iterator = 0;
	window_width = WINDOW_WIDTH;
	addition = 60.0 / window_width; */

	i = 0;
	enemy_world_angle = 0;
	while (i < data->enemy_count)
	{
		dist_to_enemy = is_enemy_visible(data, i, &enemy_world_angle);

	//	printf("DIST=%f\n", dist_to_enemy);

		if (dist_to_enemy != -1)
		{
			drawn_enemy_height = (IMG_SIZE / dist_to_enemy) * PP_DIST;
			enemy_to_screen(data, drawn_enemy_height, enemy_world_angle, dist_to_enemy);
		}
		i++;
	}
}


