#include "cubed.h"

void	get_wall_sw_images(t_data *data)
{
	mlx_texture_t	*wall_text;

    wall_text = mlx_load_png("./tiles/wall_s");
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_s = mlx_texture_to_image(data->mlx, wall_text);
	if (!data->wall_img_s)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(wall_text);
    wall_text = mlx_load_png("./tiles/wall_w");
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

	wall_text = mlx_load_png("./tiles/wall_n");
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_n = mlx_texture_to_image(data->mlx, wall_text);
	if (!data->wall_img_n)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(wall_text);
    wall_text = mlx_load_png("./tiles/wall_e");
	if (!wall_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->wall_img_e = mlx_texture_to_image(data->mlx, wall_text);
	if (!data->wall_img_e)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(wall_text);
}

void    get_images(t_data *data)
{
    get_wall_ne_images(data);
    get_wall_sw_images(data);
}