#include "cubed_bonus.h"

void	get_enemy_img_3(t_data *data)
{
	mlx_texture_t	*enemy_text;

	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/dead2.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_dead_img[2] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_dead_img[2])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/dead3.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_dead_img[3] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_dead_img[3])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/dead4.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_dead_img[4] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_dead_img[4])
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

void	get_enemy_img_2(t_data *data)
{
	mlx_texture_t	*enemy_text;

	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/enemy_right.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_img[3] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_img[3])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/dead0.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_dead_img[0] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_dead_img[0])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/dead1.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_dead_img[1] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_dead_img[1])
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

void	get_enemy_img_1(t_data *data)
{
	mlx_texture_t	*enemy_text;

	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/enemy_front.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_img[0] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_img[0])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/enemy_left.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_img[1] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_img[1])
		error_exit(data, mlx_strerror(mlx_errno), 1);
	enemy_text = mlx_load_png("./sprites/enemy/cacodeamon/enemy_back.png");
	if (!enemy_text)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	data->enemy_img[2] = mlx_texture_to_image(data->mlx, enemy_text);
	mlx_delete_texture(enemy_text);
	if (!data->enemy_img[2])
		error_exit(data, mlx_strerror(mlx_errno), 1);
}

int	set_enemy_struct(t_data *data, int i, int x, int y)
{
	data->enemy[i].x = x * IMG_SIZE + (IMG_SIZE / 2);
	data->enemy[i].y = y * IMG_SIZE + (IMG_SIZE / 2);
	data->enemy[i].direction = -1;
	data->enemy[i].step_count = -1;
	data->enemy[i].is_dying = 0;
	data->enemy[i].is_dead = 0;
	data->enemy[i].dead_anim_iter = 0;
	data->enemy[i].prev_time = 0;
	data->enemy[i].prev_dead_time = 0;
	data->enemy[i].enemy_anim_height_iter = -10;
	data->enemy[i].distance_to_player = 0;
	data->map[y][x].is_enemy = 1;
	i += 1;
	return (i);
}

void	init_enemies(t_data *data)
{
	int		i;
	int		x;
	int		y;

	data->enemy = malloc(data->enemy_count * sizeof(t_enemy));
	if (data->enemy == NULL)
		sys_error_exit(data, "Malloc failed", 0);
	get_enemy_img_1(data);
	get_enemy_img_2(data);
	get_enemy_img_3(data);
	i = -1;
	y = -1;
	i = 0;
	while (++y < data->map_height && i < data->enemy_count)
	{
		x = -1;
		while (++x < data->map_width)
		{
			if (data->map[y][x].type == 'A')
				i = set_enemy_struct(data, i, x, y);
		}
	}
}
