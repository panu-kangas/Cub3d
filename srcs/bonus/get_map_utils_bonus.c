/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_map_utils_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: llitovuo <llitovuo@student.hive.fi>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/08/01 16:16:40 by llitovuo          #+#    #+#             */
/*   Updated: 2024/08/03 12:11:14 by llitovuo         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cubed_bonus.h"

void	change_spaces_to_x(t_data *data)
{
	int		x;
	int		y;
	t_map	**map;

	x = 0;
	y = 0;
	map = data->map;
	while (y < data->map_height)
	{
		x = 0;
		while (x < data->map_width)
		{
			if (map[y][x].type == ' ')
				map[y][x].type = 'X';
			x++;
		}
		y++;
	}
}

char	*ft_strdup_nonl(const char *s1)
{
	int		i;
	char	*dest;

	if (s1 == NULL)
		return (NULL);
	dest = (char *) malloc(ft_strlen(s1) + 1);
	if (dest == 0)
		return (0);
	i = 0;
	while (s1[i] != '\0' && s1[i] != '\n')
	{
		dest[i] = s1[i];
		i++;
	}
	if (s1[0] == '\n')
	{
		dest[i] = '\n';
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

void	free_2d_array_len(char **strs, int len)
{
	while (len >= 0)
	{
		free(strs[len]);
		len--;
	}
	free (strs);
}

int	check_path_lines(t_data *data, int i, int no_flag, int so_flag)
{
	int	ea_flag;
	int	we_flag;

	ea_flag = 0;
	we_flag = 0;
	while (i < data->info_lines_count)
	{
		if (ft_strncmp(data->file[i], "NO ", 3) == 0)
			no_flag++;
		else if (ft_strncmp(data->file[i], "SO ", 3) == 0)
			so_flag++;
		else if (ft_strncmp(data->file[i], "EA ", 3) == 0)
			ea_flag++;
		else if (ft_strncmp(data->file[i], "WE ", 3) == 0)
			we_flag++;
		i++;
	}
	if (no_flag == 0 || so_flag == 0 || ea_flag == 0 || we_flag == 0)
		return (-1);
	if (no_flag > 1 || so_flag > 1 || ea_flag > 1 || we_flag > 1)
		return (-1);
	return (0);
}

int	check_color_lines(t_data *data)
{
	int	c_flag;
	int	f_flag;
	int	i;

	i = 0;
	c_flag = 0;
	f_flag = 0;
	while (i < data->info_lines_count)
	{
		if (ft_strncmp(data->file[i], "C ", 2) == 0)
			c_flag++;
		else if (ft_strncmp(data->file[i], "F ", 2) == 0)
			f_flag++;
		i++;
	}
	if (c_flag == 0 || f_flag == 0)
		return (-1);
	if (c_flag > 1 || f_flag > 1)
		return (-1);
	return (0);
}
