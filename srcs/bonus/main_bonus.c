/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_bonus.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:17:31 by llitovuo          #+#    #+#             */
/*   Updated: 2024/07/22 11:17:37 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	init_data(t_data *data)
{
	data->mlx = NULL;
	data->map = NULL;
	data->wall_img_n = NULL;
	data->wall_img_w = NULL;
	data->wall_img_s = NULL;
	data->wall_img_w = NULL;
	data->v_h_flag = 0;
	data->door_found_vert = 0;
	data->door_found_horiz = 0;

	data->door_idle_iter = 0;

	data->opening_in_action = 0;

	data->handling_open_door = 0; // what is this...?
	data->found_open_door_vert = 0;
	data->found_open_door_horiz = 0;

	data->player_coord[0] = 2 * IMG_SIZE - 1; // TEST
    data->player_coord[1] = 2 * IMG_SIZE - 1; // TEST
	data->player_angle = 120; // TEST
	
	data->fl_colour = get_rgba(77, 71, 58, 255); // TEST
	data->ceil_colour = get_rgba(18, 17, 16, 255); // TEST
}

int	main(int argc, char *argv[])
{
	t_data	*data;

	if (argc != 2)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd("Please give one map (.cub -file) as an argument", 2);
		return (1);
	}

	data = malloc(sizeof(t_data));
	if (data == NULL)
		sys_error_exit(data, "Malloc failed", 0);

	init_data(data);
	get_map(data, argv[1]);

	data->mlx = mlx_init(WINDOW_WIDTH, WINDOW_HEIGHT, "Cub3D", false);
	if (!data->mlx)
		error_exit(data, mlx_strerror(mlx_errno), 0);

	get_images(data);
	init_enemies(data);

	draw_image(data, data->player_angle - 30, WINDOW_WIDTH);

//	mlx_loop_hook(data->mlx, &enemy_handler, data);
	mlx_loop_hook(data->mlx, &door_animation, data);
	mlx_key_hook(data->mlx, &keyhook, data);
	mlx_loop(data->mlx);
	mlx_terminate(data->mlx);
	print_goodbye_message();
	free_data(data);
	return (0);
}
