#include "cubed_bonus.h"

/*
int check_for_enemy(t_data *data, double ray_angle)
{
    int i;

    i = 0;
    while (i < data->enemy_count)
    {

        i++;
    }
} */

/*
double  find_enemy_distance(t_data *data, double ray_angle, double addition)
{
    if (ray_angle == 0.0000 || ray_angle - 90.0000 == 0 \
	|| ray_angle - 180.0000 == 0 || ray_angle - 270.0000 == 0)
		ray_angle += addition;
    
}

void    draw_enemy(t_data *data)
{

    // TEST

    // TEST

    double	ray_angle;
	double	dist_to_enemy;
	double	drawn_enemy_height;
	double	addition;
	double	window_width;

	ray_angle = data->player_angle - 30;
	if (ray_angle < 0)
		ray_angle = 360 - (ray_angle * -1);
	data->ray_iterator = 0;
	window_width = WINDOW_WIDTH;
	addition = 60.0 / window_width;
	while (data->ray_iterator < WINDOW_WIDTH)
	{
		dist_to_enemy = find_enemy_distance(data, ray_angle, addition);
		drawn_enemy_height = (IMG_SIZE / dist_to_wall) * PP_DIST;
		draw_pixels(data, drawn_wall_height);
		data->ray_iterator++;
		ray_angle = ray_angle + addition;
		if (ray_angle > 360)
			ray_angle = 0;
	}
}

*/