/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:27:22 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/12 13:54:47 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	rotation(double x_pos, t_data *data)
{
	double	rotation;

	rotation = (x_pos - WINDOW_WIDTH / 2);
	data->player_angle += (rotation * MOUSE_SENS);
	if (data->player_angle >= 360)
		data->player_angle -= 360;
	if (data->player_angle < 0)
		data->player_angle += 360;
	delete_and_init_images(data);
	draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
	mlx_set_mouse_pos(data->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}
