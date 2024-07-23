/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:17:31 by llitovuo          #+#    #+#             */
/*   Updated: 2024/07/22 11:17:37 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

void init_data(t_data *data)
{
	data->map = NULL;
	data->mlx = NULL;
	data->wall_img = NULL;
}

int main(int argc, char *argv[])
{
	t_data *data;

	if (argc == 1 || argv == NULL) // ARGV is here just to satisfy the compiler :D
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Please pass a map (.cub -file) as an argument", 2);
		return (1);
	}

	data = malloc(sizeof(data));
	if (data == NULL)
		sys_error_exit(data, "Malloc failed", 0);
	init_data(data);

	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);

	return (0);
}
