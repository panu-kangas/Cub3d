#include "cubed_bonus.h"

void	execute_drawing(t_data *data, int column, double wall_height)
{
	int				i;
	long long		start_coord;
	int				ray_iter;
	int				fl_colour;

//		printf("Execute\n");

//	printf("P COOED: x=%lld, y=%lld\n", data->player_coord[0], data->player_coord[1]);


	i = 0;
	ray_iter = data->ray_iterator;
	fl_colour = data->fl_colour;
	start_coord = (WINDOW_HEIGHT / 2) - (wall_height / 2);
	while (start_coord > 0 && i < start_coord)
		mlx_put_pixel(data->game_img, ray_iter, i++, data->ceil_colour);
	start_coord = draw_wall(data, (column * 4), wall_height, start_coord);
	while (start_coord < WINDOW_HEIGHT)
		mlx_put_pixel(data->game_img, ray_iter, start_coord++, fl_colour);
	data->door_found_vert = 0;
	data->door_found_horiz = 0;
	data->found_open_door_vert = 0;
	data->found_open_door_horiz = 0;
}

void	get_closed_door_pixels(t_data *data)
{
	char	direction;

	// separate function
	if (data->v_h_flag == 0 && data->player_coord[0] > data->vert_intersection_coord[0])
		direction = 'W';
	else if (data->v_h_flag == 0)
		direction = 'E';
	else if (data->v_h_flag == 1 && data->player_coord[1] > data->horizon_intersection_coord[1])
		direction = 'N';
	else
		direction = 'S';

	if (data->door_found_vert == 1)
	{
		if (direction == 'W')
			fix_door_img(data->door_closed_img[data->door_idle_iter], data->wall_img_w);
		else
			fix_door_img(data->door_closed_img[data->door_idle_iter], data->wall_img_e);
	}
	else if (data->door_found_horiz == 1)
	{
		if (direction == 'N')
			fix_door_img(data->door_closed_img[data->door_idle_iter], data->wall_img_n);
		else
			fix_door_img(data->door_closed_img[data->door_idle_iter], data->wall_img_s);
	}
	data->pixels = data->door_closed_img[data->door_idle_iter]->pixels;
}

void	draw_pixels(t_data *data, double wall_height)
{
	int		column_to_draw;

//		printf("DRAW_PIXELS wall height: %f\n", wall_height);


	if (data->v_h_flag == 0)
	{
		if (data->player_coord[0] > data->vert_intersection_coord[0])
			data->pixels = data->wall_img_w->pixels;
		else
			data->pixels = data->wall_img_e->pixels;
		if (data->door_found_vert == 1)
			get_closed_door_pixels(data);
		column_to_draw = (int)data->vert_intersection_coord[1] % IMG_SIZE;
	}
	else
	{
		if (data->player_coord[1] > data->horizon_intersection_coord[1])
			data->pixels = data->wall_img_n->pixels;
		else
			data->pixels = data->wall_img_s->pixels;
		if (data->door_found_horiz == 1)
			get_closed_door_pixels(data);
		column_to_draw = (int)data->horizon_intersection_coord[0] % IMG_SIZE;
	}
	execute_drawing(data, column_to_draw, wall_height);
}

void put_images_to_window(t_data *data)
{
	if (mlx_image_to_window(data->mlx, data->game_img, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(&data->game_img->instances[0], 1);
	if (mlx_image_to_window(data->mlx, data->door_canvas, 0, 0) < 0)
		error_exit(data, mlx_strerror(mlx_errno), 1);
	mlx_set_instance_depth(&data->door_canvas->instances[0], 2);
}

void	draw_image(t_data *data, double ray_angle, double window_width)
{
	double		dist_to_wall;
	double		drawn_wall_height;
	double		addition;

	printf("DRAW_IMAGE\n");


	if (ray_angle < 0)
		ray_angle = 360 - (ray_angle * -1);
	data->ray_iterator = 0;
	addition = 60.0 / window_width;
	while (data->ray_iterator < WINDOW_WIDTH)
	{
		dist_to_wall = find_wall_distance(data, ray_angle, addition);

//		printf("DIST TO WALL%f\n", dist_to_wall);

		drawn_wall_height = (IMG_SIZE / dist_to_wall) * PP_DIST;

//		printf("DRAWN WALL HEIGHT %f\n", drawn_wall_height);

		drawn_wall_height += 30; // TEST
		draw_pixels(data, drawn_wall_height);
		data->ray_iterator++;
		ray_angle = ray_angle + addition;
		if (ray_angle > 360)
			ray_angle = 0;
	}
	printf("DRAW_IMAGE_END\n\n");

	draw_open_door(data, data->player_angle - 30.0, WINDOW_WIDTH);
	draw_minimap(data);
	put_images_to_window(data);
	// draw_enemy(data);
}
