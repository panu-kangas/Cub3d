/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_images.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:11:56 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/02 11:11:57 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

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

void	get_images(t_data *data)
{
	get_wall_ne_images(data);
	get_wall_sw_images(data);
	data->game_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->game_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->player_coord[0] = (data->player_x_pos * IMG_SIZE) + (IMG_SIZE / 2);
	data->player_coord[1] = (data->player_y_pos * IMG_SIZE) + (IMG_SIZE / 2);
	data->fl_colour = get_rgba(data->floor_color->r, data->floor_color->g, \
	data->floor_color->b, 255);
	data->ceil_colour = get_rgba(data->ceiling_col->r, \
	data->ceiling_col->g, data->ceiling_col->b, 255);
}
