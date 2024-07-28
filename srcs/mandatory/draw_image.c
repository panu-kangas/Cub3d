#include "cubed.h"


int	draw_wall(t_data *data, int i, double wall_height, int start_coord)
{
	int		colour;
	int		pixel_counter;
	double	pixel_iter;
	uint8_t	*pixels;

	pixel_counter = 0;
	pixel_iter = 0.0;
	pixels = data->pixels;

	while (i < (IMG_SIZE * IMG_SIZE * 4) && pixel_counter < WINDOW_HEIGHT)
	{
		if (start_coord < 0)
			start_coord++;
		else
		{
			colour = get_rgba(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
			mlx_put_pixel(data->game_img, data->ray_iterator, start_coord++, colour);
			pixel_counter++;
		}
		pixel_iter += (IMG_SIZE / wall_height);
		if (pixel_iter > 1)
		{
			while (pixel_iter > 1)
			{	
				pixel_iter -= 1;
				i += (IMG_SIZE * 4);
			}
		}
	}
	return (start_coord);
}

void	execute_drawing(t_data *data, int column, double wall_height)
{
	int		i;
	int		start_coord;

	i = 0;
	start_coord = (WINDOW_HEIGHT / 2) - (wall_height / 2);

	while (start_coord > 0 &&  i < start_coord)
		mlx_put_pixel(data->game_img, data->ray_iterator, i++, data->ceiling_colour);
	start_coord = draw_wall(data, (column * 4), wall_height, start_coord);
	while (start_coord < WINDOW_HEIGHT)
		mlx_put_pixel(data->game_img, data->ray_iterator, start_coord++, data->floor_colour);
}

void	draw_pixels(t_data *data, double wall_height)
{
	int		column_to_draw;

	if (data->v_h_flag == 0)
	{
		if (data->player_coord[0] > data->vert_intersection_coord[0])
			data->pixels = data->wall_img_w->pixels;
		else
			data->pixels = data->wall_img_e->pixels;
		column_to_draw = (int)data->vert_intersection_coord[1] % IMG_SIZE; // this might be wrong!
	}
	else
	{
		if (data->player_coord[1] > data->horizon_intersection_coord[1])
			data->pixels = data->wall_img_n->pixels;
		else
			data->pixels = data->wall_img_s->pixels;
		column_to_draw = (int)data->horizon_intersection_coord[0] % IMG_SIZE; // this might be wrong!
	}

	execute_drawing(data, column_to_draw, wall_height);


}

void    draw_image(t_data *data)
{
    double  ray_angle;
    double  dist_to_wall;
	double	drawn_wall_height;
	double	addition;

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

