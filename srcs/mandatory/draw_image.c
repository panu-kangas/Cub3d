#include "cubed.h"

int get_rgba(int r, int g, int b, int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	execute_drawing(t_data *data, uint8_t *pixels, int column, double wall_height)
{
	int	i;
	int	colour;
	int	start_coord;
	int	counter; // TEST

	i = column * 4;
	start_coord = (WINDOW_HEIGHT / 2) - (wall_height / 2);

	counter = 0; // TEST

	while (i < (IMG_SIZE * IMG_SIZE * 4))
	{
		colour = get_rgba(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
		mlx_put_pixel(data->game_img, data->ray_iterator, start_coord++, colour); // error handling...?
		i = i + (IMG_SIZE * 4);
		counter++;
		if (counter > (wall_height - 8)) // TEST
			break ;
	}
}

void	draw_pixels(t_data *data, double wall_height)
{
	uint8_t	*pixels;
	int		column_to_draw;

	if (data->v_h_flag == 0)
	{
		if (data->player_coord[0] > data->vert_intersection_coord[0])
			pixels = data->wall_img_w->pixels;
		else
			pixels = data->wall_img_e->pixels;
		column_to_draw = (int)data->vert_intersection_coord[1] % IMG_SIZE; // is this correct...?
	}
	else
	{
		if (data->player_coord[1] > data->horizon_intersection_coord[1])
			pixels = data->wall_img_n->pixels;
		else
			pixels = data->wall_img_s->pixels;

		column_to_draw = (int)data->horizon_intersection_coord[0] % IMG_SIZE;

	}

	execute_drawing(data, pixels, column_to_draw, wall_height);


}

void    draw_image(t_data *data)
{
    double  ray_angle;
    double  dist_to_wall;
	double	drawn_wall_height;
	double	addition;

    data->player_angle = 320; // TEST
    data->player_coord[0] = 6 * IMG_SIZE - 1; // TEST
    data->player_coord[1] = 6 * IMG_SIZE - 1; // TEST

    ray_angle = data->player_angle - 30;
    if (ray_angle < 0)
		ray_angle = 360 - (ray_angle * -1);

	data->ray_iterator = 0;
	addition = 0.075; // 0.075 = (60 / WINDOW_WIDTH)

	while (data->ray_iterator < WINDOW_WIDTH)
	{
		dist_to_wall = find_wall_distance(data, ray_angle);
		drawn_wall_height = (IMG_SIZE / dist_to_wall) * PP_DIST;
		draw_pixels(data, drawn_wall_height);
		data->ray_iterator++;
		ray_angle = ray_angle + addition;
		if (ray_angle > 360)
			ray_angle = 0;
	}

}

/*
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
*/
