/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/26 14:37:13 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/03 11:20:52 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed.h"

static int	check_map_name(char *map_name)
{
	int	i;

	i = 0;
	if (map_name == NULL)
		return (-1);
	if (map_name[0] == '\0')
		return (-1);
	while (map_name[i] != '\0')
		i++;
	if (map_name[i - 1] != 'b' || map_name[i - 2] != 'u'
		|| map_name[i - 3] != 'c' || map_name[i - 4] != '.')
		return (-1);
	return (0);
}

static int	get_file_height(t_data *data, char *map_name)
{
	int			fd;
	char		*buffer;

	fd = open(map_name, O_RDONLY);
	if (fd < 0)
		error_exit(data, "Map file could not be opened", 0);
	while (1)
	{
		buffer = get_next_line(fd);
		if (buffer == NULL)
			break ;
		if (data->map_start == 0 && (buffer[0] != '1' && buffer[0] != '0'
				&& buffer[0] != ' '))
			data->info_lines_count++;
		else
			data->map_start = data->info_lines_count;
		data->file_height++;
		free(buffer);
	}
	close (fd);
	data->map_height = data->file_height - data->info_lines_count;
	return (0);
}

int	is_map_valid(t_data *data, char *map_name)
{
	if (check_map_name(map_name) < 0)
		error_exit(data, "Map name is invalid", 0);
	if (get_file_height(data, map_name) < 0)
		error_exit(data, "Map file is invalid", 0);
	if (data->info_lines_count < 6)
		error_exit(data, "Some info is missing", 0);
	return (0);
}
