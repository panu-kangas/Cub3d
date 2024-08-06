/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_animation_images.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:06:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/06 12:10:19 by llitovuo         ###   ########.fr       */
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

void	get_gun_images(t_anim *anim, t_data *data)
{
	int		i;
	char	*sprite_paths[W_S_COUNT];

	sprite_paths[0] = WS0;
	sprite_paths[1] = WS1;
	sprite_paths[2] = WS2;
	sprite_paths[3] = WS3;
	sprite_paths[4] = WS4;
	i = 0;
	anim->frame_count = W_S_COUNT;
	while (i < anim->frame_count)
		make_image(&anim->sprites[i], sprite_paths[i], data);
}

void init_gun_animation(t_anim *anim, t_data *data)
{
	anim->canvas = mlx_new_image(data->mlx, WINDOW_WIDTH, WINDOW_HEIGHT);
	if (!anim->canvas)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	get_gun_images(anim, data);
}
