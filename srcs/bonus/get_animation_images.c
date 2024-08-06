/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_animation_images.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:06:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/06 13:47:19 by llitovuo         ###   ########.fr       */
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
	mlx_delete_texture(gun_text);
	if (!sprite)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	//does it need to be resized? mlx_resize_image()
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
	anim->delay = ANIM_DELAY;
	while (i < anim->frame_count)
		make_image(&anim->sprites[i], sprite_paths[i], data);
}
/*
uint32_t	get_pixel(mlx_image_t *sprite, uint32_t x, uint32_t y)
{
	uint32_t *px_start;

	if (x > sprite->width || y > sprite->height)
		return (0xFF000000);
	px_start = sprite->pixels + (y * sprite->width) * sizeof(uint32_t);
	return (get_rgba(*(px_start), *(px_start + 1), *(px_start + 2), *(px_start + 3)));
}
*/

void	init_animation_canvas(mlx_t *mlx, t_anim *anim, t_data *data)
{
	int			x_pos;
	int			y_pos;
	int			i;
	int			j;
	uint32_t	px;

	anim->canvas = mlx_new_image(mlx, anim->sprites[0]->width, \
					anim->sprites[0]->height);
	if (!anim->canvas)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	x_pos = (mlx->width - anim->canvas->width) / 2;
	y_pos = mlx->width - anim->canvas->height;
	if (mlx_image_to_window(mlx, anim->canvas, x_pos, y_pos) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(anim->canvas->instances, 5);
	ft_memcpy(anim->canvas->pixels, anim->sprites[0]->pixels, \
		anim->canvas->width * anim->canvas->height * sizeof(uint32_t));
	/*
	i = -1;
	while (++i < anim->sprites[0]->height)
	{
		j = -1;
		while (j++ < anim->sprites[0]->width)
		{
			px = get_pixel(anim->sprites[0], j, i);
			mlx_put_pixel(anim->canvas, j, i, px);
		}
	}
	*/
}

void	init_gun_animation(t_anim *anim, t_data *data)
{
	get_gun_images(anim, data);
	init_animation_canvas(data->mlx, anim, data);
}
