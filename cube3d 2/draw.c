// #include "cub3d.h"
// void	draw_ground(t_way *main_game, int x_p, int y_p)
// {
// 	int	img_w;
// 	int	img_h;
// 	int i = 0;
// 	img_w = 0;
// 	img_h = 0;
// 	main_game->img_ptrg = mlx_xpm_file_to_image(main_game->mlx,
// 			"background.xpm",
// 			&img_w, &img_h);
// 	if (main_game->img_ptrg == NULL)
// 		ft_wrong();
// 	while(y_p <= 32)
// 	{
// 		while(x_p <= 32)
// 		{
// 		printf("%d\n", i);
// 		
// 		x_p++;
// 		}
// 		y_p++;
// 	}
// }
// void	draw_walls(t_way *main_game, int x_p, int y_p)
// {
// 	int	img_w;
// 	int	img_h;

// 	img_w = 0;
// 	img_h = 0;
// 	main_game->img_ptrw = mlx_xpm_file_to_image(main_game->mlx,
// 			"wall501679190024.xpm", &img_w,
// 			&img_h);
// 	if (main_game->img_ptrw == NULL)
// 		ft_wrong();
	
// }