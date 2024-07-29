#include "cubed.h"

void	change_player_coord_left(t_data *data, double direction, int speed)
{
	if (direction > 157.5 && direction <= 202.5)
		data->player_coord[1] += speed;
	else if (direction > 202.5 && direction <= 247.5)
	{
		data->player_coord[0] -= speed;
		data->player_coord[1] += speed;
	}
	else if (direction > 247.5 && direction <= 292.5)
		data->player_coord[0] -= speed;
	else if (direction > 292.5 && direction <= 337.5)
	{
		data->player_coord[0] -= speed;
		data->player_coord[1] -= speed;
	}
}

void	change_player_coord(t_data *data, double direction, int speed)
{
	if (direction > 337.5 || direction <= 22.5)
		data->player_coord[1] -= speed;
	else if (direction > 22.5 && direction <= 67.5)
	{
		data->player_coord[0] += speed;
		data->player_coord[1] -= speed;
	}
	else if (direction > 67.5 && direction <= 112.5)
		data->player_coord[0] += speed;
	else if (direction > 112.5 && direction <= 157.5)
	{
		data->player_coord[0] += speed;
		data->player_coord[1] += speed;
	}
	else
		change_player_coord_left(data, direction, speed);
}

int	check_for_collision(t_data *data, double direction)
{
	int			i;
	long long	orig_coord[2];
	long long	*p_coord;

	i = PLAYER_SPEED;
	orig_coord[0] = data->player_coord[0];
	orig_coord[1] = data->player_coord[1];
	p_coord = data->player_coord;
	while (i > 0)
	{
		change_player_coord(data, direction, 1);
		if (data->map[p_coord[1] / IMG_SIZE][p_coord[0] / IMG_SIZE].type == '1')
		{
			p_coord[0] = orig_coord[0];
			p_coord[1] = orig_coord[1];
			return (1);
		}
		i--;
	}
	return (0);
}
