#include<fcntl.h>
#include"cub3d.h"


int main(){
     int fd = open("map.cube", O_RDONLY);


    char *line = get_next_line(fd);
    while(line)
    {
        free(line);
        line = get_next_line(fd);
    }

}