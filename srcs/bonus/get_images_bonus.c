#include "cubed_bonus.h"

void	get_wall_sw_images(t_data *data)
{
	mlx_texture_t	*wall_text;

	wall_text = mlx_load_png("./tiles/wall/wall_n.png");
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_s = mlx_texture_to_image(data->mlx, wall_text);
	if (!data->wall_img_s)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(wall_text);
	wall_text = mlx_load_png("./tiles/wall/wall_n.png");
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_w = mlx_texture_to_image(data->mlx, wall_text);
	if (!data->wall_img_w)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(wall_text);
}

void	get_wall_ne_images(t_data *data)
{
	mlx_texture_t	*wall_text;

	wall_text = mlx_load_png("./tiles/wall/wall_n.png");
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_n = mlx_texture_to_image(data->mlx, wall_text);
	if (!data->wall_img_n)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(wall_text);
	wall_text = mlx_load_png("./tiles/wall/wall_n.png");
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_e = mlx_texture_to_image(data->mlx, wall_text);
	if (!data->wall_img_e)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(wall_text);
}

void	get_door_image_1(t_data *data)
{
	mlx_texture_t	*door_text;

	door_text = mlx_load_png("./tiles/door/door_closed_0.png");
	if (!door_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->door_closed_img[0] = mlx_texture_to_image(data->mlx, door_text);
	if (!data->door_closed_img[0])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(door_text);
	door_text = mlx_load_png("./tiles/door/door_open.png");
	if (!door_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->door_open_img = mlx_texture_to_image(data->mlx, door_text);
	if (!data->door_open_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(door_text);
}

void	get_door_image_2(t_data *data)
{
	mlx_texture_t	*door_text;

	door_text = mlx_load_png("./tiles/door/door_closed_1.png");
	if (!door_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->door_closed_img[1] = mlx_texture_to_image(data->mlx, door_text);
	if (!data->door_closed_img[1])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(door_text);
	door_text = mlx_load_png("./tiles/door/door_closed_2.png");
	if (!door_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->door_closed_img[2] = mlx_texture_to_image(data->mlx, door_text);
	if (!data->door_closed_img[2])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(door_text);
	door_text = mlx_load_png("./tiles/door/door_closed_3.png");
	if (!door_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->door_closed_img[3] = mlx_texture_to_image(data->mlx, door_text);
	if (!data->door_closed_img[3])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(door_text);
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

void	fix_open_door_img(t_data *data, mlx_image_t *wall_img)
{
	uint8_t *wall_px;
	uint8_t	*door_px;
	int		x;
	int		y;
	long	i;
	int		colour;

	wall_px = wall_img->pixels;
	door_px = data->door_open_img->pixels;
	i = 0;
	y = 0;
	while (y < IMG_SIZE)
	{
		x = 0;
		while (x < IMG_SIZE)
		{
			if (door_px[i + 3] == 0 && !(y > 20 && x > 23 && x < 105))
			{
				colour = get_rgba(wall_px[i], wall_px[i + 1], wall_px[i + 2], wall_px[i + 3]);
				mlx_put_pixel(data->door_open_img, x, y, colour);
			}
			x++;
			i += 4;
		}
		y++;
	}
}

void	get_images(t_data *data)
{
	get_wall_ne_images(data);
	get_wall_sw_images(data);
	get_door_image_1(data);
	get_door_image_2(data);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->door_canvas = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->door_canvas)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	init_door_canvas(data);
}
