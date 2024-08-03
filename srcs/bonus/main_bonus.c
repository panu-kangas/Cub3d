/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:17:31 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/03 16:02:03 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->map = NULL;
	data->map_lines = NULL;
	data->wall_img_n = NULL;
	data->wall_img_w = NULL;
	data->wall_img_s = NULL;
	data->wall_img_w = NULL;
	data->v_h_flag = -1;
	data->map_height = 0;
	data->map_name = NULL;
	data->file = NULL;
	data->map_width = 0;
	data->info_lines_count = 0;
	data->map_start = 0;
	data->file_height = 0;
	data->texture_path_n = NULL;
	data->texture_path_e = NULL;
	data->texture_path_s = NULL;
	data->texture_path_w = NULL;
	data->ceiling_color = NULL;
	data->floor_color = NULL;
	data->cc = 0;
	data->fc = 0;
	data->enemy_count = 0;
}

static int	check_ac(int ac)
{
	if (ac < 2)
	{
		ft_putendl_fd("Error\n", 2);
		ft_putendl_fd("Please give one map (.cub -file) as an argument", 2);
		return (1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (check_ac(argc) != 0)
		return (1);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		sys_error_exit(data, "Malloc failed", 0);
	init_data(data);
	get_map(data, argv[1]);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	if (get_texture_paths(data) < 0 || check_texture_paths(data) == -1)
		error_exit(data, "Invalid game settings given", 0);
	if (!data->mlx)
		error_exit(data, mlx_strerror(mlx_errno), 0);
	get_images(data);
	draw_image(data);
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(&data->game_img->instances[0], 1);
	mlx_key_hook(data->mlx, &keyhook, (void *)data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	print_goodbye_message();
	free_data(data);
	return (0);
}
