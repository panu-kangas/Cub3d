/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   enemy_charge_utils_bonus.c                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/19 15:37:22 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/19 15:37:25 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	get_enemy_img_4(t_data *data)
{
	mlx_texture_t	*enemy_text;

	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/idle1.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_charge_img[0] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_charge_img[0])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/idle2.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_charge_img[1] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_charge_img[1])
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

int	get_enemy_dir(double en_perspect_ang)
{
	if (en_perspect_ang > 315 || en_perspect_ang <= 45)
		return (0);
	else if (en_perspect_ang > 45 && en_perspect_ang <= 135)
		return (1);
	else if (en_perspect_ang > 135 && en_perspect_ang <= 225)
		return (2);
	else
		return (3);
}

void	move_along_wall_2(t_data *data, int i, int enemy_dir)
{
	if (check_enemy_wall_charge(data, 0, i) == 1 \
	|| check_enemy_wall_charge(data, 2, i) == 1)
	{
		if (enemy_dir == 1)
			data->enemy[i].x += C_SPEED;
		else
			data->enemy[i].x -= C_SPEED;
	}
	else if (data->player_coord[1] < data->enemy[i].y)
		data->enemy[i].y -= C_SPEED;
	else if (data->player_coord[1] > data->enemy[i].y)
		data->enemy[i].y += C_SPEED;
}

void	move_along_wall(t_data *data, int i, int enemy_dir)
{
	if (enemy_dir == 0 || enemy_dir == 2)
	{
		if (check_enemy_wall_charge(data, 1, i) == 1 \
		|| check_enemy_wall_charge(data, 3, i) == 1)
		{
			if (enemy_dir == 0)
				data->enemy[i].y -= C_SPEED;
			else
				data->enemy[i].y += C_SPEED;
		}
		else if (data->player_coord[0] < data->enemy[i].x)
			data->enemy[i].x -= C_SPEED;
		else if (data->player_coord[0] > data->enemy[i].x)
			data->enemy[i].x += C_SPEED;
	}
	else
		move_along_wall_2(data, i, enemy_dir);
}
