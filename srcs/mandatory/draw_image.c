#include "cubed.h"

void    get_exact_vert_coord(t_data *data, double ray_angle, long long *w_coord)
{
    long long   temp_coord[2];
    long long   *p_coord;

    temp_coord[0] = w_coord[0];
    temp_coord[1] = w_coord[1];
    p_coord = data->player_coord;

    w_coord[0] = (temp_coord[0] + 1) * IMG_SIZE;

    if (ray_angle < 90)
        w_coord[1] = p_coord[1] - ((w_coord[0] - p_coord[0]) * tan(convert_to_radians(90 - ray_angle)));
	else if (ray_angle > 270)
        w_coord[1] = p_coord[1] - ((p_coord[0] - w_coord[0]) * tan(convert_to_radians(ray_angle - 270)));

}

void	draw_pixels(t_data *data, double ray_angle, double wall_height)
{
	uint8_t	*pixels;
	double	x;
	double	y;

	if (data->v_h_flag == 0)
	{
		if (data->player_coord[0] > data->vert_intersection_coord[0])
			pixels = data->wall_img_w->pixels;
		else
			pixels = data->wall_img_e->pixels;
	}
	else
	{
		if (data->player_coord[1] > data->horizon_intersection_coord[1])
			pixels = data->wall_img_n->pixels;
		else
			pixels = data->wall_img_s->pixels;
	}

	// count the right column to be drawn
	// draw pixel by pixel

}


void    draw_image(t_data *data)
{
    double  ray_angle;
    double  dist_to_wall;
	double	drawn_wall_height;

    data->player_angle = 0; // TEST
    data->player_coord[0] = 6 * IMG_SIZE - 1; // TEST
    data->player_coord[1] = 6 * IMG_SIZE - 1; // TEST

    ray_angle = data->player_angle - 30;
    if (ray_angle < 0)
        ray_angle = 360 - (ray_angle * -1);

    // while loop here, ray_angle as the iterator

    dist_to_wall = find_wall_distance(data, ray_angle);
	drawn_wall_height = (IMG_SIZE / dist_to_wall) * PP_DIST;
	draw_pixels(data, ray_angle, drawn_wall_height);


}
