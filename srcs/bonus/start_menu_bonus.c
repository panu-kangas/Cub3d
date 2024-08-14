/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   start_menu_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/08 15:11:23 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/09 11:58:36 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	menu_key_hook(mlx_key_data_t keydata, void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (keydata.key == MLX_KEY_ESCAPE && keydata.action == MLX_PRESS)
		success_exit(data);
}

uint32_t	get_menu_pixel(mlx_image_t *sprite, uint32_t x, uint32_t y)
{
	uint8_t	*px_start;

	if (x > WINDOW_WIDTH || y > WINDOW_HEIGHT)
		return (0xFF000000);
	px_start = sprite->pixels + (y * WINDOW_WIDTH + x) * sizeof(uint32_t);
	return (get_rgba(*(px_start), \
		*(px_start + 1), *(px_start + 2), *(px_start + 3)));
}

void	init_menu_img(t_data *data)
{
	mlx_texture_t	*menu_text;

	menu_text = mlx_load_png("./sprites/menu/startscreen.png");
	if (!menu_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->menu_img = mlx_texture_to_image(data->mlx, menu_text);
	mlx_delete_texture(menu_text);
	if (!data->menu_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	if (mlx_resize_image(data->menu_img, WINDOW_WIDTH, WINDOW_HEIGHT) == false)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	if (mlx_image_to_window(data->mlx, data->menu_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}
