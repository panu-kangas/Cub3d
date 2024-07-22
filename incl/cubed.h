/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cubed.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/22 11:18:06 by llitovuo          #+#    #+#             */
/*   Updated: 2024/07/22 11:18:35 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef CUBED_H
# define CUBED_H

# include <unistd.h> // open
# include <fcntl.h> // open flags
# include <stdio.h> // printf, perror
# include <stdlib.h> // malloc

# include <MLX42/MLX42.h>
# include "libft.h"

# define WINDOW_WIDTH 1024
# define WINDOW_HEIGHT 768


typedef struct s_map
{
	char	type; // wall ('1'), empty space('0'), player ('P') etc

	// here we can add additional flags, for example is_enemy, is_door etc
}			t_map;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*wall_img;

	t_map		**map;
	
	int			map_height; // is this needed?
	int			map_width; // is this needed?
	long int	player_coord[2];
}			t_data;



// ERROR HANDLING

void	error_exit(t_data *data, char *err_str, int init_flag);
void	sys_error_exit(t_data *data, char *err_str, int mlx_flag);


#endif
