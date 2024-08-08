/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:27:22 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/07 12:51:11 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void rotation(double x_pos, double y_pos, void *param)
{
	t_data	*data;
	double	rotation;

	data = (t_data *)param;
	(void)y_pos;
	rotation = (x_pos - WINDOW_WIDTH / 2); //how many pixels the mouse moved
	data->player_angle += (rotation * MOUSE_SENS);
	if (data->player_angle >= 360)
		data->player_angle -= 360;
	if (data->player_angle < 0)
		data->player_angle += 360;
	delete_and_init_images(data);
	draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
	mlx_set_mouse_pos(data->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}


