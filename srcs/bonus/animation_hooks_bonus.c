/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_hooks_bonus.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:25:14 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/07 09:55:16 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	update_anim(t_anim *anim, mlx_t *mlx)
{
	mlx_image_t	*img;

	if (anim->has_shot == 0)
		return ;
	anim->timer += mlx->delta_time;
	if (anim->frame_num > 2 && anim->timer < anim->delay)
		return ;
	else
	{
		anim->frame_num++;
		anim->timer = 0;
		if (anim->frame_num >= anim->frame_count)
		{
			anim->frame_num = 0;
			anim->has_shot = 0;
		}
	}
	img = anim->sprites[anim->frame_num];
	ft_memcpy(anim->canvas->pixels, img->pixels, \
		anim->canvas->width * anim->canvas->height * sizeof(uint32_t));
}

void	animate(void *param)
{
	t_data	*data;

	data = (t_data *)param;
	if (data->is_dead == 1 || data->show_menu == 1)
		return ;
	update_anim(&data->anim, data->mlx);
}
