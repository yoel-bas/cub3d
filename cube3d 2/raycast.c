#include "cub3d.h"
void	player_init(t_way *main_game)
{
	main_game->player->turn_direction = 0;
	main_game->player->walk_direction = 0;
	main_game->player->speed = 3.00;
	main_game->player->r_speed = 2 * (M_PI / 180);
	main_game->player->r_angle =  M_PI / 2;
	main_game->player->flg = 0;
	main_game->ray->FOV_ANGLE = 60 * (M_PI / 180);
	main_game->ray->num_arays = main_game->player->x - 1;
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
double 	distance(double x, double y, double x1, double y1)
{
	return(sqrt(pow((x1 - x), 2) + pow((y1 - y), 2)));
}
int		is_wall(t_way *main_game, int x, int y)
{
	if(x / 32 < 0  && x / 32 >= (main_game->x_p - 1) * 32 && y / 32 <= 0  && y / 32 >= (main_game->y_p - 1) * 32 )
		return(1);
	if(main_game->map[y / 32][x / 32] == '1')
		return(1);
	return(0);
}
void	line(t_way *main_game, double x, double y, double x1, double y1)
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
			mlx_put_pixel(main_game->image, round(x += (x_inc)),round(y += (y_inc)) , 0x00DDB2);
		x += x_inc;
		y += y_inc;
		i++;
	}
	
}
void	player(t_way *main_game)
{
		int i = 0;
		int j;
		mlx_put_pixel(main_game->image, main_game->player->x, main_game->player->y, 0xffffff);
		while(i < main_game->y_p * 32)
		{
			j = 0;
			while (j < main_game->x_p * 32)
			{
				if(distance(main_game->player->x , main_game->player->y, j, i) <= 3)
				{
					mlx_put_pixel(main_game->image, j, i, 0xffffff);
				}
				j++;
			}
			i++;
		}
}
int	normalize(double angle)
{
	if(angle < 0)
		angle += (2 * M_PI);
	else if(angle >= 2 * M_PI)
		angle -= (2 * M_PI);
	return(angle);
}
void	horizontal_cast(t_way *main_game,double angle)
{

	double x_step;
	double y_step;
	double x_inter;
	double y_inter;
	y_inter = floor(main_game->player->y / TILE_SIZE) * TILE_SIZE;
	if(main_game->ray->face_down)
		y_inter += TILE_SIZE;
	x_inter = main_game->player->x + ((y_inter - main_game->player->y) / tan(angle));
	y_step = TILE_SIZE;
	if(main_game->ray->face_up)
		y_step *= -1;
	x_step = y_step / tan(angle);
	if(main_game->ray->face_left && x_step > 0)
		x_step *= -1;
	if(main_game->ray->face_right && x_step < 0)
		x_step *= -1;
	double check_x = x_inter;
	double check_y = y_inter;
	while(check_x >= 0 && check_x <= ((main_game->x_p - 1) * 32) && check_y >= 0 && check_y <= ((main_game->y_p - 1) * 32))
	{
		if(main_game->ray->face_up)
			check_y -= 1;
		if(is_wall(main_game, check_x, check_y))
		{
			puts("hh");
			main_game->ray->wall_horzx = check_x;
			main_game->ray->wall_horzy = check_y;
			break;
		}
		else
		check_x += x_step;
		check_y += y_step;
	}

}
void	cast_ray(t_way *main_game, double angle)
{
	horizontal_cast(main_game,angle);
	// vertical_cast(main_game,angle);
	printf("%f-----------   %f\n",main_game->ray->wall_horzx, main_game->ray->wall_horzx); 
	// line(main_game, main_game->player->x, main_game->player->y, main_game->ray->wall_horzx, main_game->ray->wall_horzy);
	mlx_put_pixel(main_game->image, main_game->ray->wall_horzx, main_game->ray->wall_horzy, 0xffffff);
}
void	cast(t_way *main_game)
{
	// int i = 0;
	double ray_angle = main_game->player->r_angle - (main_game->ray->FOV_ANGLE / 2);
	// while(i <= main_game->ray->num_arays)
	// {
		ray_angle = normalize(ray_angle);
		main_game->ray->face_right=  (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI );
		main_game->ray->face_left = !(main_game->ray->face_right);
		main_game->ray->face_down = (ray_angle > 0 && ray_angle < M_PI);
		main_game->ray->face_up = !(main_game->ray->face_down);
		cast_ray(main_game, ray_angle);
	// 	ray_angle += ray_angle + (main_game->ray->FOV_ANGLE / (main_game->x_p - 1));
	// 	i++;
	// }

}
void	player_update(t_way *main_game)
{
		main_game->player->steps = main_game->player->walk_direction * main_game->player->speed;
		main_game->player->r_angle += main_game->player->turn_direction * main_game->player->r_speed;
		int old_x = main_game->player->x;
		int old_y = main_game->player->y;
		main_game->player->x += cos(main_game->player->r_angle) * main_game->player->steps;
		main_game->player->y += sin(main_game->player->r_angle) * main_game->player->steps;
		main_game->player->x_r = main_game->player->x + cos(main_game->player->r_angle) * 30;
		main_game->player->y_r = main_game->player->y + sin(main_game->player->r_angle) * 30;
		if(is_wall(main_game, main_game->player->x, main_game->player->y))
		{
			main_game->player->x = old_x;
			main_game->player->y = old_y;
		}
		player(main_game);
		cast(main_game);
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
	main_game->image = mlx_new_image(main_game->mlx, (main_game->x_p - 1)  * 32 , ( main_game->y_p - 1) * 32);
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_A)) 
    	main_game->player->turn_direction = -1;
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_W))
		main_game->player->walk_direction = 1;
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_S)) 
		main_game->player->walk_direction = -1;
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_D))
    	main_game->player->turn_direction = 1;
    frame(main_game);
}

void	cub(t_way *main_game, int fd)
{

	main_game->player = malloc(sizeof(t_player));
	main_game->ray = malloc(sizeof(t_ray));
	map_init(main_game, fd);
	get_player_pos(main_game);
	player_init(main_game);
	main_game->mlx = mlx_init((main_game->x_p - 1)  * 32 , ( main_game->y_p - 1) * 32 , "cube", FALSE);
	main_game->image = mlx_new_image(main_game->mlx, (main_game->x_p - 1)  * 32 , ( main_game->y_p - 1) * 32);
	frame(main_game);
	mlx_loop_hook(main_game->mlx, dd_callback, main_game);
	mlx_loop(main_game->mlx);
}