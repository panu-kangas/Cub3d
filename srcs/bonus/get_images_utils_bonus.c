#include "cubed_bonus.h"

void	get_wall_sw_images(t_data *data)
{
	mlx_texture_t	*wall_text;

	wall_text = mlx_load_png(data->texture_path_s);
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_s = mlx_texture_to_image(data->mlx, wall_text);
	mlx_delete_texture(wall_text);
	if (!data->wall_img_s)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	wall_text = mlx_load_png(data->texture_path_w);
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_w = mlx_texture_to_image(data->mlx, wall_text);
	mlx_delete_texture(wall_text);
	if (!data->wall_img_w)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

void	get_wall_ne_images(t_data *data)
{
	mlx_texture_t	*wall_text;

	wall_text = mlx_load_png(data->texture_path_n);
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_n = mlx_texture_to_image(data->mlx, wall_text);
	mlx_delete_texture(wall_text);
	if (!data->wall_img_n)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	wall_text = mlx_load_png(data->texture_path_e);
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_e = mlx_texture_to_image(data->mlx, wall_text);
	mlx_delete_texture(wall_text);
	if (!data->wall_img_e)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

void	get_closed_door_image_1(t_data *data)
{
	int				i;
	mlx_texture_t	*door_text;

	i = -1;
	while (++i < 4)
	{
		door_text = mlx_load_png("./tiles/door/door_closed_0.png");
		if (!door_text)
			error_exit(data, mlx_strerror(mlx_errno), 1);
		data->d_closed_img[0][i] = mlx_texture_to_image(data->mlx, door_text);
		mlx_delete_texture(door_text);
		if (!data->d_closed_img[0][i])
			error_exit(data, mlx_strerror(mlx_errno), 1);
	}
	i = -1;
	while (++i < 4)
	{
		door_text = mlx_load_png("./tiles/door/door_closed_1.png");
		if (!door_text)
			error_exit(data, mlx_strerror(mlx_errno), 1);
		data->d_closed_img[1][i] = mlx_texture_to_image(data->mlx, door_text);
		mlx_delete_texture(door_text);
		if (!data->d_closed_img[1][i])
			error_exit(data, mlx_strerror(mlx_errno), 1);
	}
}

void	get_closed_door_image_2(t_data *data)
{
	int				i;
	mlx_texture_t	*door_text;

	i = -1;
	while (++i < 4)
	{
		door_text = mlx_load_png("./tiles/door/door_closed_2.png");
		if (!door_text)
			error_exit(data, mlx_strerror(mlx_errno), 1);
		data->d_closed_img[2][i] = mlx_texture_to_image(data->mlx, door_text);
		mlx_delete_texture(door_text);
		if (!data->d_closed_img[2][i])
			error_exit(data, mlx_strerror(mlx_errno), 1);
	}
	i = -1;
	while (++i < 4)
	{
		door_text = mlx_load_png("./tiles/door/door_closed_3.png");
		if (!door_text)
			error_exit(data, mlx_strerror(mlx_errno), 1);
		data->d_closed_img[3][i] = mlx_texture_to_image(data->mlx, door_text);
		mlx_delete_texture(door_text);
		if (!data->d_closed_img[3][i])
			error_exit(data, mlx_strerror(mlx_errno), 1);
	}
}

void	get_open_door_image_2(t_data *data)
{
	int				i;
	mlx_texture_t	*door_text;

	i = -1;
	while (++i < 4)
	{
		door_text = mlx_load_png("./tiles/door/door_opening_2.png");
		if (!door_text)
			error_exit(data, mlx_strerror(mlx_errno), 1);
		data->d_open_img[2][i] = mlx_texture_to_image(data->mlx, door_text);
		mlx_delete_texture(door_text);
		if (!data->d_open_img[2][i])
			error_exit(data, mlx_strerror(mlx_errno), 1);
	}
}
