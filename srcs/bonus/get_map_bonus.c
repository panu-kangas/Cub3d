#include "cubed_bonus.h"

void	assign_map(t_data *data)
{
	int	x;
	int	y;

	x = 0;
	while (x < data->map_width)
		data->map[0][x++].type = '1';
	y = 0;
	while (++y < (data->map_height - 1))
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (x == 0 || x == data->map_width - 1)
				data->map[y][x].type = '1';
			else if (x == 2 && y == 2)
				data->map[y][x].type = 'P';
			else if ((x == 4 && y == 4) || (x == 8 && y == 7))
				data->map[y][x].type = '1';
			else
				data->map[y][x].type = '0';
		}
	}
	x = 0;
	while (x < data->map_width)
		data->map[y][x++].type = '1';
}

void	allocate_map(t_data *data)
{
	int	i;

	data->map = malloc((data->map_height) * sizeof(t_map));
	if (data->map == NULL)
		sys_error_exit(data, "Malloc failed", 0);
	i = 0;
	while (i < data->map_height)
	{
		data->map[i] = malloc((data->map_width) * sizeof(t_map));
		if (data->map[i] == NULL)
			sys_error_exit(data, "Malloc failed", 0);
		i++;
	}
}

void	is_map_valid(char *map_name)
{
	if (map_name == NULL)
		return ;
}

void	get_map(t_data *data, char *map_name)
{
	is_map_valid(map_name);
	data->map_width = 12;
	data->map_height = 12;
	allocate_map(data);
	assign_map(data);
}

/* TEST FOR PRINTING OUT MAP TYPE INFO:

    int x;
    int y;

    y = 0;
    while (y < data->map_height)
    {
        x = 0;
        while (x < data->map_width)
        {
            printf("%c", data->map[y][x].type);
            x++;
        }
        printf("\n");
        y++;
    }
*/