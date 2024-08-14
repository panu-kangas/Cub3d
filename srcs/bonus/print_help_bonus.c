/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_help_bonus.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/07 15:13:36 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/07 15:53:25 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static int	is_it_a_door(t_data *data, long long x, long long y)
{
	if (data->map[y][x].is_door == 1 && data->opening_in_action != 1 \
	&& is_player_too_close(data) == 0)
		return (1);
	return (0);
}

static int	check_closeby_door(t_data *data, long long x, long long y)
{
	double	angle;

	angle = data->player_angle;
	if (angle >= 340 || angle <= 20)
		return (is_it_a_door(data, x, y - 1));
	else if (angle >= 70 && angle <= 110)
		return (is_it_a_door(data, x + 1, y));
	else if (angle >= 160 && angle <= 200)
		return (is_it_a_door(data, x, y + 1));
	else if (angle >= 250 && angle <= 290)
		return (is_it_a_door(data, x - 1, y));
	return (0);
}

void	print_to_screen(t_data *data)
{
	long long	x;
	long long	y;

	x = data->player_coord[0] / IMG_SIZE;
	y = data->player_coord[1] / IMG_SIZE;
	if (check_closeby_door(data, x, y) == 1 && !data->text)
		data->text = \
		mlx_put_string(data->mlx, "Press 'E' to open/close.", 2, 2);
	else if (check_closeby_door(data, x, y) == 1 && data->text)
		data->text->enabled = true;
	else if (check_closeby_door(data, x, y) != 1 && data->text)
		data->text->enabled = false;
}
