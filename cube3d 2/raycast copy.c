#include "cub3d.h"

int main(int ac, char **av)
{
    int fd = open(av[1], O_RDONLY);
    t_way *main_game;
    char *str = strdup("");
    main_game = malloc(sizeof(t_way *));
    char *line = get_next_line(fd);
	if (!line || !str)
		return (0);
	while (line)
	{
		str = ft_strjoin(str, line);
		free(line);
		line = get_next_line(fd);
	}
    main_game->map
    main_game->mlx = mlx_init();
	main_game->mlx_window = mlx_new_window(main_game->mlx, y_p * 50, x_p * 50,
			"so_long");
}