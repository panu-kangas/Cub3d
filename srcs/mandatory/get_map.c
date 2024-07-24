#include "cubed.h"

void    assign_map(t_data *data)
{
    // Here you can assign information to the map-array based on the .cub-file
    // I'll do a manual map for testing for now

    int x;
    int y;

    x = 0;
    while (x < data->map_width)
        data->map[0][x++].type = '1';
    x = 0;
    y = 1;
    while (y < (data->map_height - 1))
    {
        x = 0;
        while (x < data->map_width)
        {
            if (x == 0 || x == data->map_width - 1)
                data->map[y][x].type = '1';
            else if (x == 6 && y == 6)
                data->map[y][x].type = 'P';
            else
                data->map[y][x].type = '0';
            x++;
        }
        y++;
    }
    x = 0;
    while (x < data->map_width)
        data->map[y][x++].type = '1';

    data->player_coord[0] = 6 * IMG_SIZE - 1; // Player is in the middle of the map in this test
    data->player_coord[1] = 6 * IMG_SIZE - 1;
    
}

void    allocate_map(t_data *data)
{
    int i;

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

void    is_map_valid(char *map_name)
{
    // Check map validation here
    // If something is not right, use error_exit function.


    if (map_name == NULL) // this is just a test
        return ;

}

void    get_map(t_data *data, char *map_name)
{

    // First, we should check if map is valid (surrounded with walls etc)

    is_map_valid(map_name);

    // If map is valid, then we allocate map based on map height and width
    // I'll use now some random values for testing!

    data->map_width = 12;
    data->map_height = 12;

    allocate_map(data);

    // Then we need to assign map information from .cub-file to data->map 2D-array
    // For now, I'll just use a manually assigned map for testing. You can change this when you want =)

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