#include "cubed.h"

int check_for_wall(t_data *data, long long *wall_coord)
{
    long long   x;
    long long   y;

    x = wall_coord[0];
    y = wall_coord[1];

    if (data->map[y][x].type == '1')
        return (1);

    return (0);
}

void    get_horizon_intersection(t_data *data, double ray_angle, long long *w_coord, int counter)
{
    long long   *p_coord;
    long long   temp_coord[2];

    p_coord = data->player_coord;
    if (ray_angle < 90 || ray_angle > 270)
        temp_coord[1] = (p_coord[1] - (p_coord[1] % IMG_SIZE)) - (counter * IMG_SIZE);
    else
        temp_coord[1] = (p_coord[1] + (IMG_SIZE - (p_coord[1] % IMG_SIZE))) + (counter * IMG_SIZE);
    
    w_coord[1] = (temp_coord[1] - 1) / IMG_SIZE;

    // add other quarters here too
    if (ray_angle < 90)
    {
        temp_coord[0] = p_coord[0] + ((p_coord[1] - temp_coord[1]) / tan(convert_to_radians(90 - ray_angle)));
        if (temp_coord[0] < 0)
            w_coord[0] = 0;
        else
            w_coord[0] = temp_coord[0] / IMG_SIZE;
    }
    else if (ray_angle > 270)
    {
        temp_coord[0] = p_coord[0] - ((p_coord[1] - temp_coord[1]) / tan(convert_to_radians(ray_angle - 270)));
        if (temp_coord[0] < 0)
            w_coord[0] = 0;
        else
            w_coord[0] = temp_coord[0] / IMG_SIZE;
    }

    data->horizon_intersection_coord[0] = temp_coord[0];
    data->horizon_intersection_coord[1] = temp_coord[1];
    
}

void    get_vert_intersection(t_data *data, double ray_angle, long long *w_coord, int counter)
{
    long long   *p_coord;
    long long   temp_coord[2];

    p_coord = data->player_coord;
    if (ray_angle < 180)
        temp_coord[0] = (p_coord[0] + (IMG_SIZE - (p_coord[0] % IMG_SIZE))) + (counter * IMG_SIZE);
    else
        temp_coord[0] = (p_coord[0] - (p_coord[0] % IMG_SIZE)) - (counter * IMG_SIZE);
    
    w_coord[0] = (temp_coord[0] - 1) / IMG_SIZE;

    // add other quarters here too


    if (ray_angle < 90)
    {
        temp_coord[1] = p_coord[1] - ((temp_coord[0] - p_coord[0]) * tan(convert_to_radians(90 - ray_angle)));
        if (temp_coord[1] < 0)
            w_coord[1] = 0;
        else
            w_coord[1] = temp_coord[1] / IMG_SIZE;
    }
    else if (ray_angle > 270)
    {
        temp_coord[1] = p_coord[1] - ((p_coord[0] - temp_coord[0]) * tan(convert_to_radians(ray_angle - 270)));
        if (temp_coord[1] < 0)
            w_coord[1] = 0;
        else
            w_coord[1] = temp_coord[1] / IMG_SIZE;
    }

    data->vert_intersection_coord[0] = temp_coord[0];
    data->vert_intersection_coord[1] = temp_coord[1];
    

}

double  compare_distance(t_data *data, double ray_angle, long long *vert_coord, long long *horizon_coord)
{
    long long   *p_coord;
    double  vert_distance;
    double  horizon_distance;

    p_coord = data->player_coord;
    vert_distance = 0;
    horizon_distance = 0;

//    printf("VERT_COORDS: x=%lld y=%lld\nHORIZON_COORDS: x=%lld y=%lld\n", vert_coord[0], vert_coord[1], horizon_coord[0], horizon_coord[1]);

    if (ray_angle < 90)
        vert_distance = (((vert_coord[0] + 1) * IMG_SIZE) - p_coord[0]) / cos(convert_to_radians(90 - ray_angle));  // eventually use ABS-value
    else if (ray_angle > 270)
        vert_distance = (p_coord[0] - ((vert_coord[0] + 1) * IMG_SIZE)) / cos(convert_to_radians(ray_angle - 270));  // eventually use ABS-value

    if (ray_angle < 90)
        horizon_distance = (p_coord[1] - ((horizon_coord[1] + 1) * IMG_SIZE)) / sin(convert_to_radians(90 - ray_angle));  // eventually use ABS-value
	else if (ray_angle > 270)
    	horizon_distance = (p_coord[1] - ((horizon_coord[1] + 1) * IMG_SIZE)) / sin(convert_to_radians(ray_angle - 270));  // eventually use ABS-value


//	printf("VERT_DIST: %f\n", vert_distance);
//	printf("CORRECTED VERT_DIST: %f\n", vert_distance * cos(convert_to_radians (data->player_angle - ray_angle)));
//	printf("HORIZON_DIST: %f\n", horizon_distance);

	if (vert_distance < horizon_distance)
    {
        data->v_h_flag = 0;
		return (vert_distance * cos(convert_to_radians (data->player_angle - ray_angle)));
    }
	else
    {
        data->v_h_flag = 1;
		return (horizon_distance * cos(convert_to_radians (data->player_angle - ray_angle)));
    }
}

double  find_wall_distance(t_data *data, double ray_angle)
{
    int         i;
    long long   vert_wall_coord[2];
    long long   horizon_wall_coord[2];

    // special condition if ray-angle is 0, 90, 180 or 270

    get_vert_intersection(data, ray_angle, vert_wall_coord, 0);    
    i = 1;
    while (check_for_wall(data, vert_wall_coord) != 1)
		get_vert_intersection(data, ray_angle, vert_wall_coord, i++);


    get_horizon_intersection(data, ray_angle, horizon_wall_coord, 0);
    i = 1;
    while (check_for_wall(data, horizon_wall_coord) != 1)
        get_horizon_intersection(data, ray_angle, horizon_wall_coord, i++);


    return (compare_distance(data, ray_angle, vert_wall_coord, horizon_wall_coord));


    //printf("%lld and %lld\n", vert_wall_coord[0], vert_wall_coord[1]);
    // printf("%d intersection at: %lld and %lld\n", i, vert_wall_coord[0], vert_wall_coord[1]);
    
}
