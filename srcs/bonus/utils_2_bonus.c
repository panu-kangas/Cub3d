/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_2_bonus.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:04:46 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/17 13:04:47 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

void	get_column_to_draw(t_data *data, char vh_flag, int *column)
{
	if (vh_flag == 'V')
	{
		if (data->player_coord[0] > data->vert_inters_crd[0])
			*column = IMG_SIZE - (int)data->vert_inters_crd[1] % IMG_SIZE;
		else
			*column = (int)data->vert_inters_crd[1] % IMG_SIZE;
	}
	else
	{
		if (data->player_coord[1] > data->horiz_inters_crd[1])
			*column = (int)data->horiz_inters_crd[0] % IMG_SIZE;
		else
			*column = IMG_SIZE - (int)data->horiz_inters_crd[0] % IMG_SIZE;
	}
}
