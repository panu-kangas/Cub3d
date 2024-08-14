/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_exit_bonus.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/12 19:08:13 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/14 16:34:52 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	get_exit_pixels(t_data *data)
{
	char	direction;

	direction = get_closed_door_direction(data);
	if (direction == 'N')
		data->pixels = data->exit_img[NORTH]->pixels;
	if (direction == 'E')
		data->pixels = data->exit_img[EAST]->pixels;
	if (direction == 'S')
		data->pixels = data->exit_img[SOUTH]->pixels;
	if (direction == 'W')
		data->pixels = data->exit_img[WEST]->pixels;
}

void	get_exit_image(t_data *data)
{
	int i;
	mlx_texture_t	*exit_text;

	i = 0;
	while (i < 4)
	{
		exit_text = mlx_load_png(EXIT_PATH);
		if (!exit_text)
			error_exit(data, mlx_strerror(mlx_errno), 1);
		data->exit_img[i] = mlx_texture_to_image(data->mlx, exit_text);
		mlx_delete_texture(exit_text);
		if (!data->exit_img[i])
			error_exit(data, mlx_strerror(mlx_errno), 1);
		i++;
	}
	fix_door_img(data->exit_img[NORTH], data->wall_img_n, 0);
	fix_door_img(data->exit_img[EAST], data->wall_img_e, 0);
	fix_door_img(data->exit_img[SOUTH], data->wall_img_s, 0);
	fix_door_img(data->exit_img[WEST], data->wall_img_w, 0);
	printf("getting_exit_image succeeded!");
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
