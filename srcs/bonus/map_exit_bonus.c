/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_exit_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:08:13 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/12 19:45:54 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	get_exit_image(t_data *data)
{
	mlx_texture_t	*exit_text;

	exit_text = mlx_load_png(EXIT_PATH);
	if (!exit_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->exit_img = mlx_texture_to_image(data->mlx, exit_text);
	mlx_delete_texture(exit_text);
	if (!data->exit_img)
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

int	validate_exit_x(t_map *map, int j, int map_width)
{
	if (j == 0 || j == map_width - 1)
		return (-1);
	if (map[j - 1].type != '1' || map[j + 1].type != '1')
		return (-1);
	return (0);
}

int	validate_exit_y(char **exit_line, int x_pos)
{
	if (exit_line[-1][x_pos] != '1' || exit_line[1][x_pos] != '1')
		return (-1);
	return (0);
}
