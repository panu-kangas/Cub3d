/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error_and_exit.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:11:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/02 13:17:53 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map != NULL)
	{
		while (i < data->map_height)
		{
			if (data->map[i] == NULL)
				break ;
			free(data->map[i++]);
		}
	}
	free(data->map);
}

void	free_data(t_data *data)
{
	if (data != NULL)
	{
		if (data->map != NULL)
			free_map(data);
		if (data->map_lines != NULL)
			free_2d_array_len(data->map_lines, data->map_height);
		if (data->file != NULL)
			free_2d_array_len(data->file, data->file_height);
		if (data->ceiling_col != NULL)
			free(data->ceiling_col);
		if (data->floor_color != NULL)
			free(data->floor_color);
		if (data->texture_path_e != NULL)
			free(data->texture_path_e);
		if (data->texture_path_n != NULL)
			free(data->texture_path_n);
		if (data->texture_path_s != NULL)
			free(data->texture_path_s);
		if (data->texture_path_w != NULL)
			free(data->texture_path_w);
		free(data);
	}
}

void	error_exit(t_data *data, const char *err_str, int init_flag)
{
	if (err_str != NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd((char *)err_str, 2);
	}
	if (init_flag == 1 && data->mlx != NULL)
		mlx_terminate(data->mlx);
	free_data(data);
	exit(1);
}

void	sys_error_exit(t_data *data, char *err_str, int init_flag)
{
	ft_putendl_fd("Error", 2);
	perror(err_str);
	if (init_flag == 1 && data->mlx != NULL)
		mlx_terminate(data->mlx);
	free_data(data);
	exit(1);
}

void	success_exit(t_data *data)
{
	print_goodbye_message();
	mlx_terminate(data->mlx);
	free_data(data);
	exit(0);
}
