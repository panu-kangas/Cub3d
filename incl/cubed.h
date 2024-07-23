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

# define WINDOW_WIDTH 1920
# define WINDOW_HEIGHT 1080
# define IMG_SIZE 64 // 64 x 64 pixels


typedef struct s_map
{
	char	type; // wall ('1'), empty space('0'), player ('P') etc
	int		is_blank; 
	/* IS_BLANK USAGE:

	If we have a map like this:

	  11111
	  10001
		10001
		11111 
		
	I think the easiest way to handle it is to make it a rectangle:

	  11111XX
	  10001XX
	  XX10001
	  XX11111 

	Here all the positions with X are "blank spaces", and should have is_blank = 1.
	I'll initialize is_blank to 0 =)

	*/

	// Here we can add additional flags, for example is_enemy, is_door etc
}			t_map;

typedef struct s_data
{
	mlx_t		*mlx;
	mlx_image_t	*wall_img_n; // North-facing wall image
	mlx_image_t	*wall_img_e; // etc...
	mlx_image_t	*wall_img_s;
	mlx_image_t	*wall_img_w;

	t_map		**map;
	
	int			map_height; // is this needed?
	int			map_width; // is this needed?
	long int	player_coord[2]; // x and y coord of the player (will be in pixels)
}			t_data;



// ERROR HANDLING

void	error_exit(t_data *data, char *err_str, int init_flag);
void	sys_error_exit(t_data *data, char *err_str, int mlx_flag);

// FREE FUNCTIONS

void	free_data(t_data *data);
void	free_map(t_data *data);


// MAP HANDLING

void	get_map(t_data *data, char *map_name);



#endif
