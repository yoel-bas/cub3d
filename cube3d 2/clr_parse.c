#include "cub3d.h"

int ft_is_digit(int c)
{
    if (c >= '0' && c <= '9')
        return (1);
    else
        return (0);
}

void clr_parse(char *str)
{
    char **splt;
    int j;
    int i;

    splt = ft_split(str, ',');
    if (!splt[2] || splt[3])
        ft_error("ERROR: incorrect RGB format");
    j = 0;
    while(splt[j])
    {
        if (ft_atoi(splt[j]) > 255 || ft_atoi(splt[j]) < 0)
            ft_error("ERROR: incorrect RGB format");
        i = 0;
        while (splt[j][i])
        {
            if (splt[j][i] == '\n')
                break ;
            if (!ft_is_digit(splt[j][i]))
                ft_error("ERROR: incorrect RGB format");
            i++;
        }
        j++;
    }
}

// void    clr_parse(char *str, t_cube *content, int flag)
// {
//     char **splt;
//     int j;
//     int i;

//     splt = ft_split(str, ',');
//     if (!splt[2] || splt[3])
//         ft_error("ERROR: incorrect RGB format");
//     j = 0;
//     while(splt[j])
//     {
//         if (ft_atoi(splt[j]) > 255 || ft_atoi(splt[j]) < 0)
//             ft_error("ERROR: incorrect RGB format");
//         i = 0;
//         while (splt[j][i])
//         {
//             if (splt[j][i] == '\n')
//                 break ;
//             if (!ft_is_digit(splt[j][i]))
//                 ft_error("ERROR: incorrect RGB format");
//             i++;
//         }
//         j++;
//     }
//     if (flag)
//         content->cl->cl = splt;
//     else
//         content->cl->fl = splt;
// }