/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   key_actions.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 10:50:00 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/02 10:50:02 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	key_action_a(t_data *data)
{
	double		direction;

	direction = data->player_angle - 90;
	if (direction >= 360)
		direction -= 360;
	else if (direction < 0)
		direction = 360 - (direction * -1);
	if (check_for_collision(data, direction) == 1)
		return ;
}

void	key_action_s(t_data *data)
{
	double		direction;

	direction = data->player_angle - 180;
	if (direction >= 360)
		direction -= 360;
	else if (direction < 0)
		direction = 360 - (direction * -1);
	if (check_for_collision(data, direction) == 1)
		return ;
}

void	key_action_d(t_data *data)
{
	double		direction;

	direction = data->player_angle + 90;
	if (direction >= 360)
		direction -= 360;
	else if (direction < 0)
		direction = 360 - (direction * -1);
	if (check_for_collision(data, direction) == 1)
		return ;
}

void	key_action_w(t_data *data)
{
	double		direction;

	direction = data->player_angle;
	if (check_for_collision(data, direction) == 1)
		return ;
}
