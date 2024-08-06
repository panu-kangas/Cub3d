#include "cubed_bonus.h"

int	colour_the_pixel(t_data *data, long long *start_coord, int pixel_counter, int i)
{
	int		colour;
	uint8_t	*pixels;

	pixels = data->pixels;
	colour = get_rgba(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
	if (data->handling_open_door == 0)
		mlx_put_pixel(data->game_img, data->ray_iterator, *start_coord, colour);
	else if (data->handling_open_door == 1)
		mlx_put_pixel(data->door_canvas, data->ray_iterator, *start_coord, colour);
	*start_coord += 1;
	return (pixel_counter + 1);
}

int	draw_wall(t_data *data, int i, double wall_height, long long start_coord)
{
	int		px_cnt;
	double	pixel_iter;

	printf("START COORD: %lld\n", start_coord);

	px_cnt = 0;
	pixel_iter = 0.0;
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

int		get_colour_minimap(t_data *data, int x_counter)
{
	int			start_pos;
	static int	y_counter;
	long long	draw_coord[2];
	long long	*p_coord;

	p_coord = data->player_coord;
	start_pos = MINIMAP_TILE_COUNT / 2;
	draw_coord[0] = (p_coord[0] / IMG_SIZE) - (start_pos - x_counter);
	draw_coord[1] = (p_coord[1] / IMG_SIZE) - (start_pos - y_counter);
	if (x_counter == MINIMAP_TILE_COUNT - 1)
		y_counter++;
	if (y_counter == MINIMAP_TILE_COUNT)
		y_counter = 0;

	if (draw_coord[0] < 0 || draw_coord[1] < 0 \
	|| draw_coord[0] >= data->map_width || draw_coord[1] >= data->map_height)
		return (get_rgba(10, 10, 10, 255));

	if (data->map[draw_coord[1]][draw_coord[0]].type == '0' \
	|| data->map[draw_coord[1]][draw_coord[0]].type == 'P')
		return (get_rgba(230, 224, 193, 255)); // Floor (brown)
	else if (data->map[draw_coord[1]][draw_coord[0]].is_door == 1)
		return (get_rgba(237, 186, 33, 255)); // Door (sort of yellow...? :D)
	else if (data->map[draw_coord[1]][draw_coord[0]].type == '1' \
	|| data->map[draw_coord[1]][draw_coord[0]].type == 'X')
		return (get_rgba(10, 10, 10, 255)); // Wall (black)
	else
		return (0); // check this
}

// Surround map with a small borderline...?

void	draw_minimap(t_data *data)
{
	long long	x;
	long long	y;
	int			x_counter; // count how many tiles are drawn on one line
	int			y_counter; // count of how many times to draw until end of tile is reached
	int			line_counter; // count of how many lines need to be drawn
	int			colour;

	line_counter = MINIMAP_TILE_COUNT;
	x_counter = 0;
	while (line_counter > 0)
	{
		x = 0 + (MINIMAP_IMG_SIZE * x_counter);
		colour = get_colour_minimap(data, x_counter);
		while (x < (MINIMAP_IMG_SIZE * (x_counter + 1)))
		{
			y = WINDOW_HEIGHT - (MINIMAP_IMG_SIZE * line_counter);
			y_counter = 0;
			while (y_counter < MINIMAP_IMG_SIZE)
			{
				mlx_put_pixel(data->door_canvas, x, y++, colour);
				y_counter++;
			}
			x++;
		}
		x_counter++;
		if (x_counter == MINIMAP_TILE_COUNT)
		{
			line_counter--;
			x_counter = 0;
		}
	}
	draw_player_icon(data);
}
