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



void    draw_enemy(t_data *data)
{
    double	ray_angle;
	double	dist_to_enemy;
//	double	drawn_enemy_height;
	double	addition;
	double	window_width;

	ray_angle = data->player_angle - 30;
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
		// TEST	
		if (ray_angle == 0.0000 || ray_angle - 90.0000 == 0 \
		|| ray_angle - 180.0000 == 0 || ray_angle - 270.0000 == 0)
			ray_angle += addition;
	}
}

*/

