#include "cubed_bonus.h"

int	colour_the_pixel(t_data *data, long long *start_coord, int px_count, int i)
{
	int		colour;
	int		ray_iter;
	uint8_t	*pixels;

	ray_iter = data->ray_iterator;
	pixels = data->pixels;
	colour = get_rgba(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
	if (data->handling_open_door == 0)
		mlx_put_pixel(data->game_img, ray_iter, *start_coord, colour);
	else if (data->handling_open_door == 1)
		mlx_put_pixel(data->door_canvas, ray_iter, *start_coord, colour);
	*start_coord += 1;
	return (px_count + 1);
}

int	draw_wall(t_data *data, int i, double wall_height, long long start_coord)
{
	int		px_cnt;
	double	pixel_iter;

	px_cnt = 0;
	pixel_iter = 0.0;
	if (start_coord < -1000)
		start_coord = -300;
	while (i < (IMG_SIZE * IMG_SIZE * 4) && px_cnt < WINDOW_HEIGHT)
	{
		if (start_coord < 0)
			start_coord++;
		else
			px_cnt = colour_the_pixel(data, &start_coord, px_cnt, i);
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
