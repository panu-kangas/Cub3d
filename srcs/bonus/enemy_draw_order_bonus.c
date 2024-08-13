#include "cubed_bonus.h"

int	check_if_already_in_list(t_data *data, int *draw_order, int enemy_i)
{
	int	j;

	j = 0;
	while (j < data->enemy_count)
	{
		if (draw_order[j] == enemy_i)
			return (1);
		j++;
	}
	return (0);
}

int	*init_draw_order(t_data *data)
{
	int	i;
	int	*draw_order;

	draw_order = malloc(data->enemy_count * sizeof(int));
	if (draw_order == NULL)
		sys_error_exit(data, "malloc failed", 1);
	i = 0;
	while (i < data->enemy_count)
		draw_order[i++] = -1;
	return (draw_order);
}

void	get_draw_order(t_data *data)
{
	int		i;
	int		j;
	int		greatest_dist_i;
	double	greatest_dist;

	data->draw_order = init_draw_order(data);
	j = -1;
	while (++j < data->enemy_count)
	{
		i = -1;
		greatest_dist = -1;
		while (++i < data->enemy_count)
		{
			if (data->enemy[i].distance_to_player >= greatest_dist \
			&& check_if_already_in_list(data, data->draw_order, i) == 0)
			{
				greatest_dist = data->enemy[i].distance_to_player;
				greatest_dist_i = i;
			}
		}
		data->draw_order[j] = greatest_dist_i;
	}
}
