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

int	rgb_atoi(t_color *color, char *rgb, int pos)
{
	int		num;

	num = ft_atoi(rgb);
	if (num < 0 || num > 255)
		return (-1);
	if (pos == 0)
		color->r = num;
	else if (pos == 1)
		color->g = num;
	else if (pos == 2)
		color->b = num;
	if (num % 100 > 0 || num == 100)
		return (2);
	else if (num % 10 > 0 || num == 10)
		return (1);
	else
		return (0);
}
