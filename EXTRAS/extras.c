double	check_if_ray_hits_enemy(t_data *data, double ray_angle)
{
//	double		dist_to_enemy_center;
	double		enemy_slope;
	double		ray_slope;
	long long	enemy_border[2][2]; // coordinates for enemy borders --> maybe a double...?
	long long	intersect_coord[2]; // --> maybe a double...?
	long long	enemy_line_add;
	long long	ray_line_add;


	// TEST
	double	x_diff;
	double	y_diff;

	x_diff = data->player_coord[0] - data->enemy[0].e_coord[0];
	if (x_diff < 0)
		x_diff *= -1;
	if (x_diff == 0) // TEST
		x_diff = 0.1;
	y_diff = data->player_coord[1] - data->enemy[0].e_coord[1];
	if (y_diff < 0)
		y_diff *= -1;
	if (y_diff == 0) // TEST
		y_diff = 0.1;


//	dist_to_enemy_center = get_enemy_distance(data);

	if (ray_angle < 90) // up right, just for test
	{

		enemy_slope = tan (convert_to_radians(90.0 - convert_to_degrees(atan(y_diff / x_diff)))); // Maybe brake into smaller pieces :D
		if ((data->player_angle > 90 && data->player_angle < 180) || data->player_angle > 270)
			enemy_slope *= -1; // ascending line
		enemy_line_add = data->enemy[0].e_coord[1] - (enemy_slope * data->enemy[0].e_coord[0]);

	//	printf("X_DIFF=%f, Y_DIFF=%f\n", x_diff, y_diff);

	//	printf("ANG: %f\n", convert_to_degrees(atan(y_diff / x_diff)));

		ray_slope = tan(convert_to_radians(90.0 - ray_angle));
		if (ray_angle < 90 || (ray_angle > 180 && ray_angle > 270))
			ray_slope *= -1; // ascending line
		ray_line_add = data->player_coord[1] + (ray_slope * data->player_coord[0]);

	
		// Only true with up right direction
		// save slope_ang (90 - atan(y_diff / x_diff)) to a separate var
		enemy_border[0][0] = data->enemy[0].e_coord[0] - ((ENEMY_WIDTH / 2) \
		* cos(convert_to_radians(90 - convert_to_degrees(atan(y_diff / x_diff)))));
		enemy_border[0][1] = data->enemy[0].e_coord[1] - ((ENEMY_WIDTH / 2) \
		* sin(convert_to_radians(90 - convert_to_degrees(atan(y_diff / x_diff)))));
		enemy_border[1][0] = data->enemy[0].e_coord[0] + ((ENEMY_WIDTH / 2) \
		* cos(convert_to_radians(90 - convert_to_degrees(atan(y_diff / x_diff)))));
		enemy_border[1][1] = data->enemy[0].e_coord[1] + ((ENEMY_WIDTH / 2) \
		* sin(convert_to_radians(90 - convert_to_degrees(atan(y_diff / x_diff)))));


		intersect_coord[0] = (enemy_line_add - ray_line_add) / (ray_slope - enemy_slope);
		intersect_coord[1] = (enemy_slope * intersect_coord[0]) + enemy_line_add;


		/*	printf("PLAYER_ANG: %f\n", data->player_angle);
			printf("ENEMY BORDER: first_x: %lld, first_y=%lld, second_x=%lld, second_y=%lld\n", enemy_border[0][0], enemy_border[0][1], enemy_border[1][0], enemy_border[1][1]);

			printf("ENEMY: slope=%f, line_add=%lld\n", enemy_slope, enemy_line_add);
			printf("RAY: slope=%f, line_add=%lld\n", ray_slope, ray_line_add);
			printf("INTERSECT COORD: x=%lld, y=%lld\n\n", intersect_coord[0], intersect_coord[1]);
	*/


		if (intersect_coord[0] < data->player_coord[0] && intersect_coord[1] > data->player_coord[1]) // this is wrong
			return (0);
		else if (intersect_coord[0] >= enemy_border[0][0] && intersect_coord[0] <= enemy_border[1][0])
		{
			int	i;

		/*	printf("RAY_SLOPE: %f\n", ray_slope);
			printf("PLAYER_ANG: %f\n", data->player_angle);
			printf("PLAYER_COORD: x=%lld, y=%lld\n", data->player_coord[0], data->player_coord[1]);


			printf("ENEMY BORDER: first_x: %lld, first_y=%lld, second_x=%lld, second_y=%lld\n", enemy_border[0][0], enemy_border[0][1], enemy_border[1][0], enemy_border[1][1]);

			printf("ENEMY: slope=%f, line_add=%lld\n", enemy_slope, enemy_line_add);
			printf("RAY: slope=%f, line_add=%lld\n", ray_slope, ray_line_add);
			printf("INTERSECT COORD: x=%lld, y=%lld\n\n", intersect_coord[0], intersect_coord[1]);
		*/

			i = 0;
			while (i < 64)
			{
				mlx_put_pixel(data->game_img, data->ray_iterator, (WINDOW_HEIGHT / 2) - 40 + i, get_rgba(255, 255, 255, 255));
				i++;
			}
		//	printf("We got a hit!\n");
		}
	}
	else if (ray_angle > 270) // up right, just for test
	{

		enemy_slope = tan (convert_to_radians(90.0 - convert_to_degrees(atan(y_diff / x_diff)))); // Maybe brake into smaller pieces :D
		if ((data->player_angle > 90 && data->player_angle < 180) || data->player_angle > 270)
			enemy_slope *= -1; // ascending line
		enemy_line_add = data->enemy[0].e_coord[1] - (enemy_slope * data->enemy[0].e_coord[0]);

	//	printf("X_DIFF=%f, Y_DIFF=%f\n", x_diff, y_diff);

	//	printf("ANG: %f\n", convert_to_degrees(atan(y_diff / x_diff)));

		ray_slope = tan(convert_to_radians(ray_angle - 270));
		if (ray_angle < 90 || (ray_angle > 180 && ray_angle > 270))
			ray_slope *= -1; // ascending line
		ray_line_add = data->player_coord[1] + (ray_slope * data->player_coord[0]);

	
		// Only true with up right direction
		// save slope_ang (90 - atan(y_diff / x_diff)) to a separate var
		enemy_border[0][0] = data->enemy[0].e_coord[0] - ((ENEMY_WIDTH / 2) \
		* cos(convert_to_radians(90 - convert_to_degrees(atan(y_diff / x_diff)))));
		enemy_border[0][1] = data->enemy[0].e_coord[1] + ((ENEMY_WIDTH / 2) \
		* sin(convert_to_radians(90 - convert_to_degrees(atan(y_diff / x_diff)))));
		enemy_border[1][0] = data->enemy[0].e_coord[0] + ((ENEMY_WIDTH / 2) \
		* cos(convert_to_radians(90 - convert_to_degrees(atan(y_diff / x_diff)))));
		enemy_border[1][1] = data->enemy[0].e_coord[1] - ((ENEMY_WIDTH / 2) \
		* sin(convert_to_radians(90 - convert_to_degrees(atan(y_diff / x_diff)))));


		intersect_coord[0] = (enemy_line_add - ray_line_add) / (ray_slope - enemy_slope);
		intersect_coord[1] = (enemy_slope * intersect_coord[0]) + enemy_line_add;


		/*	printf("PLAYER_ANG: %f\n", data->player_angle);
			printf("ENEMY BORDER: first_x: %lld, first_y=%lld, second_x=%lld, second_y=%lld\n", enemy_border[0][0], enemy_border[0][1], enemy_border[1][0], enemy_border[1][1]);

			printf("ENEMY: slope=%f, line_add=%lld\n", enemy_slope, enemy_line_add);
			printf("RAY: slope=%f, line_add=%lld\n", ray_slope, ray_line_add);
			printf("INTERSECT COORD: x=%lld, y=%lld\n\n", intersect_coord[0], intersect_coord[1]);
	*/


		if (intersect_coord[0] > data->player_coord[0] && intersect_coord[1] > data->player_coord[1]) // this is wrong
			return (0);
		else if (intersect_coord[0] >= enemy_border[0][0] && intersect_coord[0] <= enemy_border[1][0])
		{
			int	i;

		/*	printf("RAY_SLOPE: %f\n", ray_slope);
			printf("PLAYER_ANG: %f\n", data->player_angle);
			printf("PLAYER_COORD: x=%lld, y=%lld\n", data->player_coord[0], data->player_coord[1]);


			printf("ENEMY BORDER: first_x: %lld, first_y=%lld, second_x=%lld, second_y=%lld\n", enemy_border[0][0], enemy_border[0][1], enemy_border[1][0], enemy_border[1][1]);

			printf("ENEMY: slope=%f, line_add=%lld\n", enemy_slope, enemy_line_add);
			printf("RAY: slope=%f, line_add=%lld\n", ray_slope, ray_line_add);
			printf("INTERSECT COORD: x=%lld, y=%lld\n\n", intersect_coord[0], intersect_coord[1]);
		*/

			i = 0;
			while (i < 64)
			{
				mlx_put_pixel(data->game_img, data->ray_iterator, (WINDOW_HEIGHT / 2) - 40 + i, get_rgba(255, 255, 255, 255));
				i++;
			}
		//	printf("We got a hit!\n");
		}
	}


	return (0);

}