#include "cubed.h"

void	free_map(t_data *data)
{
	int	i;

	i = 0;
	if (data->map != NULL)
	{
		while (i < data->map_height)
		{
			if (data->map[i] == NULL)
				break ;
			free(data->map[i++]);
		}
	}
	free(data->map);
}

void	free_data(t_data *data)
{
	if (data != NULL)
	{
		free_map(data);
		free(data);
	}
}

void	error_exit(t_data *data, const char *err_str, int init_flag)
{
	if (err_str != NULL)
	{
		ft_putendl_fd("Error", 2);
		ft_putendl_fd((char *)err_str, 2);
	}
	if (init_flag == 1 && data->mlx != NULL)
		mlx_terminate(data->mlx);
	free_data(data);
	exit(1);
}

void	sys_error_exit(t_data *data, char *err_str, int init_flag)
{
	ft_putendl_fd("Error", 2);
	perror(err_str);
	if (init_flag == 1 && data->mlx != NULL)
		mlx_terminate(data->mlx);
	free_data(data);
	exit(1);
}

void	success_exit(t_data *data)
{
	print_goodbye_message();
	mlx_terminate(data->mlx);
	free_data(data);
	exit(0);
}
