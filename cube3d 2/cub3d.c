#include "cub3d.h"

void	ft_parser(t_cube *content)
{
	if (!foreign_material(content->lmt->map))
		ft_error("foreing material");
	check_top_bottom(content->lmt->map);
	check_sides(content->lmt->map);
	check_extranous_spaces(content->lmt->map);
}
int main(int ac , char **av)
{
    if(ac > 1)
    {
    t_cube	main_game;

	if (ac != 2)
		ft_error("ERROR: Missing or too many arguments!");
	check_extension(av[1]);
	main_game.cl = ft_calloc(sizeof(t_clr), 1);
	main_game.cp = ft_calloc(sizeof(t_cmp), 1);
	main_game.lmt = ft_calloc(sizeof(t_elem), 1);
	maper(&main_game, av[1]); 
	read_components(&main_game);
	// ft_parser(&main_game);	
    cub(&main_game);
    }
    return(0);
}