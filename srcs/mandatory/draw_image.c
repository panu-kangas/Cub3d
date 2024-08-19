/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   draw_image.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/02 11:11:33 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/02 11:11:35 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	colour_the_pixel(t_data *data, long long *start_coord, int px_count, int i)
{
	int		colour;
	uint8_t	*pixels;

	pixels = data->pixels;
	colour = get_rgba(pixels[i], pixels[i + 1], pixels[i + 2], pixels[i + 3]);
	mlx_put_pixel(data->game_img, data->ray_iterator, *start_coord, colour);
	*start_coord += 1;
	return (px_count + 1);
}

int	draw_wall(t_data *data, int i, double wall_height, long long start_coord)
{
	int		px_cnt;
	double	pixel_iter;

	px_cnt = 0;
	pixel_iter = 0.0;
	if (start_coord < -1000)
		start_coord = -300;
	while (i < (IMG_SIZE * IMG_SIZE * 4) && px_cnt < WINDOW_HEIGHT)
	{
		if (start_coord < 0)
			start_coord++;
		else
			px_cnt = colour_the_pixel(data, &start_coord, px_cnt, i);
		pixel_iter += (IMG_SIZE / wall_height);
		if (pixel_iter > 1)
		{
			while (pixel_iter > 1)
			{
				pixel_iter -= 1;
				i += (IMG_SIZE * 4);
			}
		}
	}
	return (start_coord);
}

void	execute_drawing(t_data *data, int column, double wall_height)
{
	int				i;
	long long		start_coord;
	int				ray_iter;
	int				fl_colour;

	i = 0;
	ray_iter = data->ray_iterator;
	fl_colour = data->fl_colour;
	start_coord = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	while (start_coord > 0 && i < start_coord)
		mlx_put_pixel(data->game_img, ray_iter, i++, data->ceil_colour);
	start_coord = draw_wall(data, (column * 4), wall_height, start_coord);
	while (start_coord < WINDOW_HEIGHT)
		mlx_put_pixel(data->game_img, ray_iter, start_coord++, fl_colour);
}

void	draw_pixels(t_data *data, double wall_height)
{
	int		column;

	if (data->v_h_flag == 0)
	{
		if (data->player_coord[0] > data->vert_inters_crd[0])
			data->pixels = data->wall_img_e->pixels;
		else
			data->pixels = data->wall_img_w->pixels;
		if (data->player_coord[0] > data->vert_inters_crd[0])
			column = IMG_SIZE - ((int)data->vert_inters_crd[1] % IMG_SIZE);
		else
			column = (int)data->vert_inters_crd[1] % IMG_SIZE;
	}
	else
	{
		if (data->player_coord[1] > data->horiz_inters_crd[1])
			data->pixels = data->wall_img_s->pixels;
		else
			data->pixels = data->wall_img_n->pixels;
		if (data->player_coord[1] > data->horiz_inters_crd[1])
			column = (int)data->horiz_inters_crd[0] % IMG_SIZE;
		else
			column = IMG_SIZE - (int)data->horiz_inters_crd[0] % IMG_SIZE;
	}
	execute_drawing(data, column, wall_height);
}

void	draw_image(t_data *data)
{
	double	ray_angle;
	double	dist_to_wall;
	double	drawn_wall_height;
	double	addition;
	double	window_width;

	ray_angle = data->player_angle - 30;
	if (ray_angle < 0)
		ray_angle += 360;
	data->ray_iterator = 0;
	window_width = WINDOW_WIDTH;
	addition = 60.0 / window_width;
	while (data->ray_iterator < WINDOW_WIDTH)
	{
		dist_to_wall = find_wall_distance(data, ray_angle, addition);
		drawn_wall_height = (IMG_SIZE / dist_to_wall) * PP_DIST;
		draw_pixels(data, drawn_wall_height);
		data->ray_iterator++;
		ray_angle = ray_angle + addition;
		if (ray_angle > 360)
			ray_angle -= 360;
	}
}
