#include "cub3d.h"
int main(int ac , char **av)
{
    if(ac > 1)
    {
    t_way main_game;

    int fd = open(av[1], O_RDONLY);
    cub(&main_game, fd);
    }
    return(0);
}