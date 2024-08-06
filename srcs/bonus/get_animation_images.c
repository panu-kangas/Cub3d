/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_animation_images.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 10:06:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/06 14:56:12 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

mlx_image_t	*make_image(char *sprite_path, t_data *data)
{
	mlx_texture_t	*gun_text;
	mlx_image_t		*sprite;

	gun_text = mlx_load_png(sprite_path);
	if (!gun_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	sprite = mlx_texture_to_image(data->mlx, gun_text);
	mlx_delete_texture(gun_text);
	if (!sprite)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	//does it need to be resized? mlx_resize_image()
	return (sprite);
}

void	get_gun_images(t_anim *anim, t_data *data)
{
	ft_bzero(anim, sizeof(t_anim));
	anim->sprites = ft_calloc(W_S_COUNT, sizeof(mlx_image_t *));
	if (!anim->sprites)
		error_exit(data, "calloc", 1);
	anim->frame_count = W_S_COUNT;
	anim->delay = ANIM_DELAY;
	anim->sprites[0] = make_image(WS0, data);
	anim->sprites[1] = make_image(WS1, data);
	anim->sprites[2] = make_image(WS2, data);
	anim->sprites[3] = make_image(WS3, data);
	anim->sprites[4] = make_image(WS4, data);
	anim->sprites[5] = make_image(WS5, data);
	if (!anim->sprites[0] || !anim->sprites[1] || !anim->sprites[2]
		||!anim->sprites[3] || !anim->sprites[4] || !anim->sprites[5])
			error_exit(data, "make animation images failed", 1);
	
}

uint32_t	get_pixel(mlx_image_t *sprite, uint32_t x, uint32_t y)
{
	uint8_t	*px_start;

	if (x > sprite->width || y > sprite->height)
		return (0xFF000000);
	px_start = sprite->pixels + (y * sprite->width + x) * sizeof(uint32_t);
	return (get_rgba(*(px_start), *(px_start + 1), *(px_start + 2), *(px_start + 3)));
}

void	init_animation_canvas(t_anim *anim, t_data *data)
{
	int			x_pos;
	int			y_pos;
	int			i;
	int			j;
	uint32_t	px;

	anim->canvas = mlx_new_image(data->mlx, 158, 120);
	if (!anim->canvas)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	x_pos = (data->mlx->width - anim->canvas->width) / 2;
	y_pos = data->mlx->height - anim->canvas->height;
	if (mlx_image_to_window(data->mlx, anim->canvas, x_pos, y_pos) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(anim->canvas->instances, 5);
	//ft_memcpy(anim->canvas->pixels, anim->sprites[0]->pixels, anim->canvas->width * anim->canvas->height * sizeof(uint32_t));
	i = -1;
	while (++i < (int)anim->sprites[0]->height)
	{
		j = -1;
		while (j++ < (int)anim->sprites[0]->width)
		{
			px = get_pixel(anim->sprites[0], j, i);
			mlx_put_pixel(anim->canvas, j, i, px);
		}
	}
}

void	init_gun_animation(t_anim *anim, t_data *data)
{
	get_gun_images(anim, data);
	init_animation_canvas(anim, data);
}
