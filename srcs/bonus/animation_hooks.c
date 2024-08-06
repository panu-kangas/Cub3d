/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   animation_hooks.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/06 12:25:14 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/06 12:37:32 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	update_anim(void *ptr1, void *ptr2)
{
	t_anim		*anim;
	mlx_image_t *img;

	anim = (t_anim *)ptr1;
	if (!anim)
		return ;
	if (time == anim->delay)
	{
		anim->frame_num++;
		if (anim->frame_num >= anim->frame_count)
			anim->frame_num = 0;
		
	}

}
