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

void	get_images(t_data *data)
{
	get_wall_ne_images(data);
	get_wall_sw_images(data);
	get_door_image_1(data);
	get_door_image_2(data);
	data->door = data->door_closed_img[0];
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}
