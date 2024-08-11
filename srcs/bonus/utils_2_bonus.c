#include "cubed_bonus.h"

void	put_images_to_window(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(&data->game_img->instances[0], 1);
	if (mlx_image_to_window(data->mlx, data->door_canvas, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(&data->door_canvas->instances[0], 2);
}
