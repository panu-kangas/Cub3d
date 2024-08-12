/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:27:22 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/12 16:53:54 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	rotation(double x_pos, t_data *data)
{

	data->player_angle += (x_pos - WINDOW_WIDTH / 2) * MOUSE_SENS;
	if (data->player_angle >= 360)
		data->player_angle -= 360;
	else if (data->player_angle < 0)
		data->player_angle = 360 - (data->player_angle * -1);
	delete_and_init_images(data);
	draw_image(data, data->player_angle - 30, WINDOW_WIDTH);
}
