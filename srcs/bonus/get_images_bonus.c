#include "cubed_bonus.h"

void	get_open_door_image_1(t_data *data)
{
	int				i;
	mlx_texture_t	*door_text;

	i = -1;
	while (++i < 4)
	{
		door_text = mlx_load_png("./tiles/door/door_opening_0.png");
		if (!door_text)
			error_exit(data, mlx_strerror(mlx_errno), 1);
		data->d_open_img[0][i] = mlx_texture_to_image(data->mlx, door_text);
		mlx_delete_texture(door_text);
		if (!data->d_open_img[0][i])
			error_exit(data, mlx_strerror(mlx_errno), 1);
	}
	i = -1;
	while (++i < 4)
	{
		door_text = mlx_load_png("./tiles/door/door_opening_1.png");
		if (!door_text)
			error_exit(data, mlx_strerror(mlx_errno), 1);
		data->d_open_img[1][i] = mlx_texture_to_image(data->mlx, door_text);
		mlx_delete_texture(door_text);
		if (!data->d_open_img[1][i])
			error_exit(data, mlx_strerror(mlx_errno), 1);
	}
}

void	init_door_canvas(t_data *data)
{
	int	x;
	int	y;

	y = -1;
	while (++y < WINDOW_HEIGHT)
	{
		x = -1;
		while (++x < WINDOW_WIDTH)
			mlx_put_pixel(data->door_canvas, x, y, 0);
	}
}

void	fix_door_img(mlx_image_t *door_img, mlx_image_t *wall_img, long i)
{
	uint8_t	*wall_px;
	uint8_t	*door_px;
	int		x;
	int		y;
	int		colour;

	wall_px = wall_img->pixels;
	door_px = door_img->pixels;
	y = -1;
	while (++y < IMG_SIZE)
	{
		x = -1;
		while (++x < IMG_SIZE)
		{
			if (door_px[i + 3] < 100 && !(y > 20 && x > 23 && x < 105))
			{
				colour = get_rgba(wall_px[i], wall_px[i + 1], \
				wall_px[i + 2], wall_px[i + 3]);
				mlx_put_pixel(door_img, x, y, colour);
			}
			i += 4;
		}
	}
}

void	fix_all_door_images(t_data *data, int i)
{
	while (++i < 4)
		fix_door_img(data->d_closed_img[i][0], data->wall_img_n, 0);
	i = -1;
	while (++i < 4)
		fix_door_img(data->d_closed_img[i][1], data->wall_img_e, 0);
	i = -1;
	while (++i < 4)
		fix_door_img(data->d_closed_img[i][2], data->wall_img_s, 0);
	i = -1;
	while (++i < 4)
		fix_door_img(data->d_closed_img[i][3], data->wall_img_w, 0);
	i = -1;
	while (++i < 3)
		fix_door_img(data->d_open_img[i][0], data->wall_img_n, 0);
	i = -1;
	while (++i < 3)
		fix_door_img(data->d_open_img[i][1], data->wall_img_e, 0);
	i = -1;
	while (++i < 3)
		fix_door_img(data->d_open_img[i][2], data->wall_img_s, 0);
	i = -1;
	while (++i < 3)
		fix_door_img(data->d_open_img[i][3], data->wall_img_w, 0);
}

void	get_images(t_data *data)
{
	get_wall_ne_images(data);
	get_wall_sw_images(data);
	printf("getting images1\n");
	get_exit_image(data);
	printf("getting images2\n");
	get_closed_door_image_1(data);
	get_closed_door_image_2(data);
	get_open_door_image_1(data);
	get_open_door_image_2(data);
	fix_all_door_images(data, -1);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->door_canvas = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->door_canvas)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	init_door_canvas(data);
	init_menu_img(data);
	data->player_coord[0] = data->player_x_pos * IMG_SIZE + (IMG_SIZE / 2);
	data->player_coord[1] = data->player_y_pos * IMG_SIZE + (IMG_SIZE / 2);
	data->fl_colour = get_rgba(data->floor_color->r, data->floor_color->g, \
	data->floor_color->b, 255);
	data->ceil_colour = get_rgba(data->ceiling_col->r, \
	data->ceiling_col->g, data->ceiling_col->b, 255);
	init_enemies(data);
}
