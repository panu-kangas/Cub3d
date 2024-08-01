#include "cubed_bonus.h"
/*

double  get_enemy_distance(t_data *data)
{
	long long	x_diff;
	long long	y_diff;

	x_diff = data->player_coord[0] - data->enemy[0].e_coord[0];
	if (x_diff < 0)
		x_diff *= -1;
	y_diff = data->player_coord[1] - data->enemy[0].e_coord[1];
	if (y_diff < 0)
		y_diff *= -1;
	return (sqrt(powl(x_diff, 2) + powl(y_diff, 2)));
}
*/

double	check_if_ray_hits_enemy(t_data *data, double ray_angle)
{
//	double	dist_to_enemy_center;
	double		enemy_slope;
	double		ray_slope;
	long long	enemy_border[2][2]; // coordinates for enemy borders
	long long	intersect_coord[2];
	long long	enemy_line_add;
	long long	ray_line_add;


	if (ray_angle < 90) // up right, just for test
	{

		enemy_slope = tan(convert_to_radians(data->player_angle));
		if ((data->player_angle > 90 && data->player_angle < 180) || data->player_angle > 270)
			enemy_slope *= -1; // ascending line
		enemy_line_add = data->enemy[0].e_coord[1] - (enemy_slope * data->enemy[0].e_coord[0]);

		ray_slope = tan(convert_to_radians(90.0-ray_angle));
		if (data->player_angle < 90 || (data->player_angle > 180 && data->player_angle > 270))
			ray_slope *= -1; // ascending line
		ray_line_add = data->player_coord[1] + (ray_slope * data->player_coord[0]);


		// Only true with up right direction
		enemy_border[0][0] = data->enemy[0].e_coord[0] - ((ENEMY_WIDTH / 2) \
		* cos(convert_to_radians(data->player_angle)));
		enemy_border[0][1] = data->enemy[0].e_coord[1] - ((ENEMY_WIDTH / 2) \
		* sin(convert_to_radians(data->player_angle)));
		enemy_border[1][0] = data->enemy[0].e_coord[0] + ((ENEMY_WIDTH / 2) \
		* cos(convert_to_radians(data->player_angle)));
		enemy_border[1][1] = data->enemy[0].e_coord[1] + ((ENEMY_WIDTH / 2) \
		* sin(convert_to_radians(data->player_angle)));


		intersect_coord[0] = (enemy_line_add - ray_line_add) / (ray_slope - enemy_slope);
		intersect_coord[1] = (enemy_slope * intersect_coord[0]) + enemy_line_add;

		if (intersect_coord[0] < data->player_coord[0] || intersect_coord[1] > data->player_coord[1])
			return (0);
		else if (intersect_coord[0] > enemy_border[0][0] && intersect_coord[0] < enemy_border[1][0])
		{
			int	i;


		//	printf("ENEMY BORDER: first_x: %lld, first_y=%lld, second_x=%lld, second_y=%lld\n", enemy_border[0][0], enemy_border[0][1], enemy_border[1][0], enemy_border[1][1]);

		//	printf("ENEMY: slope=%f, line_add=%lld\n", enemy_slope, enemy_line_add);
		//	printf("RAY: slope=%f, line_add=%lld\n", ray_slope, ray_line_add);
		//	printf("INTERSECT COORD: x=%lld, y=%lld\n\n", intersect_coord[0], intersect_coord[1]);


			i = 0;
			while (i < 60)
			{
				mlx_put_pixel(data->game_img, data->ray_iterator, (WINDOW_HEIGHT / 2) - 40 + i, get_rgba(255, 255, 255, 255));
				i++;
			}
		//	printf("We got a hit!\n");
		}
	}


	return (0);

}

void    draw_enemy(t_data *data)
{
    double	ray_angle;
	double	dist_to_enemy;
//	double	drawn_enemy_height;
	double	addition;
	double	window_width;

	ray_angle = data->player_angle + 10;
	if (ray_angle < 0)
		ray_angle = 360 - (ray_angle * -1);
	data->ray_iterator = 0;
	window_width = WINDOW_WIDTH;
	addition = 60.0 / window_width;
//	printf("\nNEW ROUND\n\n");
	while (data->ray_iterator < WINDOW_WIDTH)
	{
		dist_to_enemy = check_if_ray_hits_enemy(data, ray_angle);

		if (dist_to_enemy == 100000.0)
			break ;
	//	drawn_enemy_height = (IMG_SIZE / dist_to_wall) * PP_DIST;
	//	draw_pixels(data, drawn_wall_height);
		data->ray_iterator++;
		ray_angle = ray_angle + addition;
		if (ray_angle > 360)
			ray_angle = 0;
	}
}

