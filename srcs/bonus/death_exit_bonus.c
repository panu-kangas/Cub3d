/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   death_exit_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/17 13:01:23 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/17 13:01:24 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	get_end_txt_img(t_data *data)
{
	mlx_texture_t	*end_texture;

	end_texture = mlx_load_png("./tiles/end_text.png");
	if (!end_texture)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->death_text_img = mlx_texture_to_image(data->mlx, end_texture);
	mlx_delete_texture(end_texture);
	if (!data->death_text_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	if (mlx_resize_image(data->death_text_img, WINDOW_WIDTH, \
	data->death_text_img->height) == false)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

void	draw_death_img(t_data *data)
{
	int		i;
	int		x;
	int		y;
	int		colour;
	uint8_t	*pixels;

	i = 0;
	y = 0;
	while (y < WINDOW_HEIGHT)
	{
		x = 0;
		while (x < WINDOW_WIDTH)
		{
			pixels = data->game_img->pixels;
			colour = get_rgba(255, pixels[i + 1], pixels[i + 2], pixels[i + 3]);
			mlx_put_pixel(data->death_img, x, y, colour);
			pixels = data->door_canvas->pixels;
			colour = get_rgba(255, pixels[i + 1], pixels[i + 2], pixels[i + 3]);
			if (pixels[i + 3] > 150)
				mlx_put_pixel(data->death_img, x, y, colour);
			x++;
			i += 4;
		}
		y++;
	}
}

void	death_exit(t_data *data)
{
	data->death_img = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!data->death_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	draw_death_img(data);
	delete_and_init_images(data);
	mlx_delete_image(data->mlx, data->anim.canvas);
	get_end_txt_img(data);
	if (mlx_image_to_window(data->mlx, data->death_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(&data->death_img->instances[0], 1);
	if (mlx_image_to_window(data->mlx, data->death_text_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(&data->death_text_img->instances[0], 2);
	mlx_put_string(data->mlx, "Press ESC to exit", 2, 2);
	data->is_dead = 1;
}
