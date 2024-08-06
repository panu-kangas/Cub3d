/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_animation_images.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:06:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/06 10:11:30 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	make_image(mlx_image_t *sprite, char *sprite_path, t_data *data)
{
	mlx_texture_t	*gun_text;

	gun_text = mlx_load_png(sprite_path);
	if (!gun_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	sprite = mlx_texture_to_image(data->mlx, gun_text);
	if (!sprite)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_delete_texture(gun_text);
}

void	get_weapon_images(t_data *data)
{
	int		i;
	char	*sprite_paths[W_S_COUNT];

	sprite_paths[0] = WS0;
	sprite_paths[1] = WS1;
	sprite_paths[2] = WS2;
	sprite_paths[3] = WS3;
	sprite_paths[4] = WS4;
	i = 0;
	while (i < W_S_COUNT)
		make_image(&data->anim.sprites[i], sprite_paths[i], data);
}
