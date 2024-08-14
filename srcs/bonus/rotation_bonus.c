/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotation_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/05 11:27:22 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/12 19:53:01 by llitovuo         ###   ########.fr       */
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
	mlx_set_mouse_pos(data->mlx, WINDOW_WIDTH / 2, WINDOW_HEIGHT / 2);
}
