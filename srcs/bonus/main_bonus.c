/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:17:31 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/12 12:05:11 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void init_ptrs(t_data *data)
{
	data->mlx = NULL;
	data->map = NULL;
	data->map_lines = NULL;
	data->wall_img_n = NULL;
	data->wall_img_w = NULL;
	data->wall_img_s = NULL;
	data->wall_img_w = NULL;
	data->text = NULL;
	data->enemy = NULL;
	data->draw_order = NULL;
	data->texture_path_n = NULL;
	data->texture_path_e = NULL;
	data->texture_path_s = NULL;
	data->texture_path_w = NULL;
	data->ceiling_color = NULL;
	data->floor_color = NULL;
	data->map_name = NULL;
	data->file = NULL;
	data->anim.sprites = NULL;
}

void	init_data(t_data *data)
{
	init_ptrs(data);
	data->enemy_anim_height_iter = -10;
	data->shooting = 0;
	data->is_dead = 0;
	data->v_h_flag = 0;
	data->door_found_vert = 0;
	data->door_found_horiz = 0;
	data->door_idle_iter = 0;
	data->opening_in_action = 0;
	data->handling_open_door = 0;
	data->found_open_door_vert = 0;
	data->found_open_door_horiz = 0;
	data->map_height = 0;
	data->map_width = 0;
	data->info_lines_count = 0;
	data->map_start = 0;
	data->file_height = 0;
	data->cc = 0;
	data->fc = 0;
	data->enemy_count = 0;
	data->show_menu = 1;
}

static int	check_ac(int ac)
{
	if (ac < 2)
	{
		ft_putendl_fd("Error\n", 2);
		ft_putendl_fd("Please give one map (.cub -file) as an argument", 2);
		exit(1);
	}
	return (0);
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	check_ac(argc);
	data = malloc(sizeof(t_data));
	if (data == NULL)
		sys_error_exit(data, "Malloc failed", 0);
	init_data(data);
	get_map(data, argv[1]);
	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		error_exit(data, mlx_strerror(mlx_errno), 0);
	get_images(data);
	init_gun_animation(&data->anim, data);
	mlx_loop_hook(data->mlx, &enemy_handler, data);
	mlx_loop_hook(data->mlx, keyhook, data);
	mlx_loop_hook(data->mlx, &door_animation, data);
	mlx_loop_hook(data->mlx, &animate, data);
	mlx_key_hook(data->mlx, &special_keys, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	print_goodbye_message();
	free_data(data);
	return (0);
}
