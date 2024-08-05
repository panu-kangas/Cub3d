/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   debug.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/29 18:31:41 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/01 11:30:39 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"
#include "stdio.h"

void	print_info(t_data *data)
{
	printf("printing info\n");
	printf("path n: %s\n", data->texture_path_n);
	printf("path e: %s\n", data->texture_path_e);
	printf("path s: %s\n", data->texture_path_s);
	printf("path w: %s\n", data->texture_path_w);
	printf("ceiling color: ");
	printf("%d %d %d\n", data->ceiling_color->r, data->ceiling_color->g, data->ceiling_color->b); 
	printf("\n");
	printf("floor color: ");
	printf("%d %d %d\n", data->floor_color->r, data->floor_color->g, data->floor_color->b);
	printf("\n");
}

void	print_map(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (i < data->map_height)
	{
		j = 0;
		while (j < data->map_width)
		{
			printf("%c", data->map[i][j].type);
			j++;
		}
		printf("\n");
		i++;
	}
}

void	print_data(t_data *data)
{
	int	i;
	int	j;

	i = 0;
	while (data->file[i] != NULL)
	{
		j = 0;
		while (data->file[i][j] != '\0')
		{
			printf("%c", data->file[i][j]);
			j++;
		}
		printf("\n");
		i++;
	}
	printf("\n\n printing map\n");
	print_map(data);
	print_info(data);
}

void	print_map_lines(t_data *data)
{
	int	i;

	i = 0;
	while (data->map_lines[i] != NULL)
	{
		printf("%s\n", data->map_lines[i]);
		i++;
	}
}
