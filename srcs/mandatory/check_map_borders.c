/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check_map_borders.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/30 16:42:51 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/01 10:08:43 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

int	check_for_nl(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
		return (-1);
	if (*str == '\0')
		return (-1);
	while (str[i] != '\0')
	{
		if (ft_strchr("10 SNEW", str[i]) != NULL)
			i++;
		else
			return (-1);
	}
	return (0);
}

int	check_first_last(char *str)
{
	while (*str)
	{
		if (*str != '1' && *str != ' ')
			return (-1);
		str++;
	}
	return (0);
}

int	check_surrounding_tiles(char **tile, int x_pos)
{
	//printf("pos -1 xpos-1 %c\n", tile[-1][x_pos - 1]);
	if (tile[-1][x_pos - 1] == ' ' || tile[-1][x_pos - 1] == '\0')
		return (-1);
	//printf("pos -1 xpos %c\n", tile[-1][x_pos]);
	if (tile[-1][x_pos] == ' ' || tile[-1][x_pos] == '\0')
		return (-1);
	//printf("pos -1 xpos+1 %c\n", tile[-1][x_pos + 1]);
	if (tile[-1][x_pos + 1] == ' ' || tile[-1][x_pos + 1] == '\0')
		return (-1);
	//printf("pos xpos-1 %c\n", tile[0][x_pos - 1]);
	if (tile[0][x_pos - 1] == ' ' || tile[0][x_pos - 1] == '\0')
		return (-1);
	//printf("pos xpos %c\n", tile[0][x_pos]);
	if (tile[0][x_pos] == ' ' || tile[0][x_pos] == 0)
		return (-1);
	//printf("pos xpos+1 %c\n", tile[0][x_pos + 1]);
	if (tile[0][x_pos + 1] == ' ' || tile[0][x_pos + 1] == '\0')
		return (-1);
	//printf("pos+1 xpos-1 %c\n", tile[1][x_pos - 1]);
	if (tile[1][x_pos - 1] == ' ' || tile[1][x_pos - 1] == '\0')
		return (-1);
	//printf("pos+1 xpos %c\n", tile[1][x_pos]);
	if (tile[1][x_pos] == ' ' || tile[1][x_pos] == '\0')
		return (-1);
	//printf("pos+1 xpos+1 %c\n", tile[1][x_pos + 1]);
	if (tile[1][x_pos + 1] == ' ' || tile[1][x_pos + 1] == '\0')
		return (-1);
	//printf("tile: %c\n", tile[0][x_pos]);
	return (0);
}

int	check_if_map_closed(char **map_line)
{
	int	i;

	i = 0;
	while (map_line[0][i])
	{
		if (ft_strchr("0SNEW", map_line[0][i]) != NULL)
		{
			if (check_surrounding_tiles(map_line, i) == -1)
				return (-1);
		}
		i++;
	}
	return (0);
}

int	check_map_borders(t_data *data)
{
	int	i;
	int	ret;

	ret = 0;
	i = 0;
	//printf("Checking map borders\n");
	while (ret == 0 && data->map_lines[i] != NULL)
	{
		ret = check_for_nl(data->map_lines[i]);
		//printf("ret: %d\n", ret);
		if (i == 0 || i == data->map_height - 1)
		{
			if (check_first_last(data->map_lines[i]) == -1)	
				return (-1);
		}
		else
		{
			//printf("should go here: i: %d\n", i);
			if (check_if_map_closed(&data->map_lines[i]) == -1)
			{
				//printf("map not closed\n");
				return (-1);
			}
		}
		i++;
	}
	return (0);
}
