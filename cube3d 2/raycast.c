#include "cub3d.h"
void	player_init(t_way *main_game)
{
	main_game->player->turn_direction = 0;
	main_game->player->walk_direction = 0;
	main_game->player->speed = 3;
	main_game->player->r_speed = 2 * (M_PI / 180);
	main_game->player->r_angle =  M_PI / 2;
	main_game->player->flg = 0;
}
void	get_player_pos(t_way *main_game)
{
	int y = 0;
	int x = 0;
	while(main_game->map[y])
	{
		x = 0;
		while(main_game->map[y][x])
		{	
			if(main_game->map[y][x] == 'P')
			{
				main_game->player->x = x * 32;
				main_game->player->y = y * 32;
			}
			x++;
		}
		y++;
	} 
}
void    map_init(t_way *main_game, int fd)
{
    char *line;
    int count = 1;
    char *str = ft_strdup("");
	line = get_next_line(fd);
    main_game->x_p = ft_strlen(line);
	if (!line)
		ft_wrong();
	while (line)
	{
        count++;
		str = ft_strjoin(str, line);
		free(line);
		line = get_next_line(fd);
	}
    main_game->y_p = count;
    main_game->map = ft_split(str, '\n');
}
void	line(t_way *main_game, int x, int y, int x1, int y1)
{
	int i = 0;
	double dx, dy, step, x_inc, y_inc;
	dx = x1 - x;
	dy = y1 - y;
	if(fabs(dx) > fabs(dy))
		step = fabs(dx);
	else 
		step = fabs(dy);
	x_inc = dx / step;
	y_inc = dy / step;
	while(i < step)
	{
		mlx_put_pixel(main_game->image, (x += round(x_inc)),(y += round(y_inc)) , 0x00DDB2);
		x += x_inc;
		y += y_inc;
		i++;
	}

}
void	player_update(t_way *main_game)
{
		printf("%d\n", main_game->player->turn_direction);
		main_game->player->r_angle += main_game->player->turn_direction * main_game->player->r_speed;
		main_game->player->x_r = main_game->player->x + cos(main_game->player->r_angle) * 30;
		main_game->player->y_r = main_game->player->y + sin(main_game->player->r_angle) * 30;
		mlx_put_pixel(main_game->image, main_game->player->x, main_game->player->y , 0x00DDB2);
		mlx_put_pixel(main_game->image, main_game->player->x + 1,main_game->player->y , 0x00DDB2);
		mlx_put_pixel(main_game->image, main_game->player->x - 1,main_game->player->y , 0x00DDB2);
		mlx_put_pixel(main_game->image, main_game->player->x,main_game->player->y +1 , 0x00DDB2);
		mlx_put_pixel(main_game->image, main_game->player->x,main_game->player->y - 1, 0x00DDB2);
		line(main_game, main_game->player->x, main_game->player->y, main_game->player->x_r, (main_game->player->y_r) );
}
void	draw_w(t_way *main_game, int *x, int* y, int color)
{
	int i, j ;
	i = 0;j = 0;
			i = *y * 32; 
			while(i < (32 + (*y * 32)))
			{
				j = *x * 32; 
				while(j < (32 + (*x * 32)))
				{
				mlx_put_pixel(main_game->image, j,i , color);
				j++;
				}
				i++;
			}
}
void	draw_map(t_way *main_game)
{
	int x, y, i ,j;
	x = 0;
	y = 0;
	i = 0;
	j = 0;
	while(main_game->map[y])
	{
		x = 0;
		while(main_game->map[y][x])
		{
			if(main_game->map[y][x] == '1')
				draw_w(main_game, &x,&y, 0xFF5B33);			
			x++;
		}
		y++;

	} 
}
void	frame(void * main)
{
	t_way* main_game = (t_way *)main;
	draw_map(main_game);
	player_update(main_game);
	mlx_image_to_window(main_game->mlx,main_game->image, 0 , 0);
}
void dd_callback(void *param)
{
    t_way *main_game = (t_way *)param;

    main_game->player->walk_direction = 0;
    main_game->player->turn_direction = 0;
	if(main_game->image)
		mlx_delete_image(main_game->mlx, main_game->image);
     if (mlx_is_key_down(main_game->mlx, MLX_KEY_LEFT))
    {
		// main_game->player->x -= 1;
        main_game->player->turn_direction = -1;
    }
    else if (mlx_is_key_down(main_game->mlx, MLX_KEY_RIGHT))
    {
		// main_game->player->x += 1;
        main_game->player->turn_direction = 1;
    }
		main_game->image = mlx_new_image(main_game->mlx, (main_game->x_p - 1)  * 32 , ( main_game->y_p - 1) * 32);
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_A)) // a
		main_game->player->x -= 1;
	else if(mlx_is_key_down(main_game->mlx, MLX_KEY_W)) //w
		main_game->player->y -= 1;
	else if(mlx_is_key_down(main_game->mlx, MLX_KEY_S)) //s
		main_game->player-> y += 1;
	else if(mlx_is_key_down(main_game->mlx, MLX_KEY_D)) //d
		main_game->player->x += 1;
    frame(main_game);

    return ; // Return 0 to keep the loop running
}


void	cub(t_way *main_game, int fd)
{
	main_game->player = malloc(sizeof(t_player));
	map_init(main_game, fd);
	get_player_pos(main_game);
	player_init(main_game);
	main_game->mlx = mlx_init((main_game->x_p - 1)  * 32 , ( main_game->y_p - 1) * 32 , "cube", FALSE);
	mlx_loop_hook(main_game->mlx, dd_callback, main_game);
	mlx_loop(main_game->mlx);
}