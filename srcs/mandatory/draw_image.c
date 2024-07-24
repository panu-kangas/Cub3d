#include "cubed.h"

int check_for_wall(t_data *data, long long *vert_wall_coord)
{
    long long   x;
    long long   y;

    x = vert_wall_coord[0];
    y = vert_wall_coord[1];

    if (data->map[y][x].type == '1')
        return (1);

    return (0);
}

void    get_first_intersection(t_data *data, double ray_angle, long long *w_coord)
{
    long long   *p_coord;
    long long   temp_coord[2];

    p_coord = data->player_coord;
    if (ray_angle > 180 && ray_angle < 360)
        temp_coord[0] = (p_coord[0] - (p_coord[0] % IMG_SIZE));
    else
        temp_coord[0] = (p_coord[0] + (IMG_SIZE - (p_coord[0] % IMG_SIZE)));
    
    w_coord[0] = (temp_coord[0] - 1) / IMG_SIZE;

    // add other quarters here too
    if (ray_angle > 270)
    {
        temp_coord[1] = p_coord[1] - ((p_coord[0] - temp_coord[0]) * tan(convert_to_radians(ray_angle - 270)));
        if (temp_coord[1] < 0)
            w_coord[1] = -1;
        else
            w_coord[1] = temp_coord[1] / IMG_SIZE;
    }
    

    
}

double  find_wall(t_data *data, double ray_angle)
{
    long long   vert_wall_coord[2];
    // long long  horizon_wall_coord[2];

    // special condition if ray-angle is 0, 90, 180 or 270


    get_first_intersection(data, ray_angle, vert_wall_coord);

    printf("%lld and %lld\n", vert_wall_coord[0], vert_wall_coord[1]);

    // if no wall was found at first intersection, enter a loop where you continue ray.



    return (0);
    
}


void    draw_image(t_data *data)
{
    double  ray_angle;
    double  dist_to_wall;

    data->player_angle = 0; // TEST

    ray_angle = data->player_angle - 30;
    if (ray_angle < 0)
        ray_angle = 360 - (ray_angle * -1);

    // while loop here, ray_angle as the iterator

    dist_to_wall = find_wall(data, ray_angle);
    // count wall height (based on the distance)
    // get intersection coord (based on the distance)
    // get pixel info (based on intersection coords)
    // draw pixels

}



/*double  get_vertical_distance(t_data *data, double ray_angle)
{
    double      distance;
    long long   w_coord[2]; // rename this! Leikkauspisteen koordinaaatti tms
    long long   *p_coord;

    p_coord = data->player_coord;
    if (ray_angle > 180 && ray_angle < 360)
        w_coord[0] = p_coord[0] - (p_coord[0] % IMG_SIZE);
    else
        w_coord[0] = p_coord[0] + (IMG_SIZE - (p_coord[0] % IMG_SIZE));

    if (ray_angle > 270)
        w_coord[1] =  p_coord[1] - ((p_coord[0] - w_coord[0]) / tan(convert_to_radians(360 - ray_angle)));


}*/