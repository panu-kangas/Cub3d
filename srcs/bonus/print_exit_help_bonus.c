/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_exit_help_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/14 17:12:44 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/14 17:13:08 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

static int	is_it_a_exit(t_data *data, long long x, long long y)
{
	if (data->map[y][x].is_exit == 1)
		return (1);
	return (0);
}

static int	check_closeby_exit(t_data *data, long long x, long long y)
{
	double	angle;

	angle = data->player_angle;
	if (angle >= 340 || angle <= 20)
		return (is_it_a_exit(data, x, y - 1));
	else if (angle >= 70 && angle <= 110)
		return (is_it_a_exit(data, x + 1, y));
	else if (angle >= 160 && angle <= 200)
		return (is_it_a_exit(data, x, y + 1));
	else if (angle >= 250 && angle <= 290)
		return (is_it_a_exit(data, x - 1, y));
	return (0);
}


void	print_to_screen_exit(t_data *data)
{
	long long	x;
	long long	y;

	x = data->player_coord[0] / IMG_SIZE;
	y = data->player_coord[1] / IMG_SIZE;
	if (check_closeby_exit(data, x, y) == 1 && !data->exit_text)
		data->exit_text = \
		mlx_put_string(data->mlx, "Press 'F' to ESCAPE!!.", 2, 8);
	else if (check_closeby_exit(data, x, y) == 1 && data->exit_text)
	{
		data->exit_text->enabled = true;
		data->exit_rdy = 1;
	}
	else if (check_closeby_exit(data, x, y) != 1 && data->exit_text)
	{
		data->exit_text->enabled = false;
		data->exit_rdy = 1;
	}
}
