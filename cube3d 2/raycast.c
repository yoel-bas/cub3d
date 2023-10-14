#include "cub3d.h"
void	player_init(t_cube *main_game)
{
	main_game->player->turn_direction = 0;
	main_game->player->walk_direction = 0;
	main_game->player->speed = 6.00;
	main_game->player->r_speed = 2 * (M_PI / 180);
	if(main_game->dir_flag == 1)
		main_game->player->r_angle =  M_PI / 2;
	if(main_game->dir_flag == 2)
		main_game->player->r_angle =  M_PI;
	if(main_game->dir_flag == 3)
		main_game->player->r_angle =  (3 * M_PI) / 2;
	if(main_game->dir_flag == 4)
		main_game->player->r_angle =  2 * M_PI ;

	main_game->player->flg = 0;
	main_game->ray->FOV_ANGLE = 60 * (M_PI / 180);
	main_game->ray->num_arays =  main_game->ray->FOV_ANGLE / main_game->x_p;
	// main_game->iter = 0;
}
void ft_upload_texture_img(t_cube *main_game)
{
	main_game->north_img = mlx_load_png(main_game->cp->n);
	main_game->south_img = mlx_load_png(main_game->cp->s);
	main_game->east_img = mlx_load_png(main_game->cp->e);
	main_game->west_img = mlx_load_png(main_game->cp->w);
	if (!main_game->north_img || !main_game->south_img || !main_game->east_img || !main_game->west_img) 
		ft_error("ERROR: load_png failed");
	main_game->m_north = mlx_texture_to_image(main_game->mlx, main_game->north_img);
	main_game->m_south = mlx_texture_to_image(main_game->mlx, main_game->south_img);
	main_game->m_east = mlx_texture_to_image(main_game->mlx, main_game->east_img);
	main_game->m_west = mlx_texture_to_image(main_game->mlx, main_game->west_img);
	if (!main_game->m_north || !main_game->m_south || !main_game->m_east || !main_game->m_west)
		ft_error("ERROR: texture loading issue!");
}

unsigned int ft_pixel(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
    return (r << 24 | g << 16 | b << 8 | a);
}

void	get_player_pos(t_cube *main_game)
{
	int y = 0;
	int x = 0;
	while(main_game->lmt->map[y])
	{
		x = 0;
		while(main_game->lmt->map[y][x])
		{	
			if(main_game->lmt->map[y][x] == 'N' || main_game->lmt->map[y][x] == 'S'
				|| main_game->lmt->map[y][x] == 'W' || main_game->lmt->map[y][x] == 'E')
			{
				main_game->player->x = x * TILE_SIZE;
				main_game->player->y = y * TILE_SIZE;
			}
			x++;
		}
		y++;
	} 
}

double 	distance(double x, double y, double x1, double y1)
{
	return(sqrt(pow((x1 - x), 2) + pow((y1 - y), 2)));
}
int		is_wall(t_cube *main_game, double x1, double y1)
{
	int x = x1 / TILE_SIZE;
    int y = y1 / TILE_SIZE;
	if(x < 0  && x  >= (main_game->x_p) && y < 0  && y >= (main_game->y_p) )
		return(1);

	if(main_game->lmt->map[y][x] && main_game->lmt->map[y][x] == '1')
		return(1);
	return(0);
}
void	line(t_cube *main_game, double x, double y, double x1, double y1)
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
		mlx_put_pixel(main_game->image, round(x),round(y) , 0x00DDB2);
		x += x_inc;
		y += y_inc;
		i++;
	}
	
}
void	player(t_cube *main_game)
{
		int i = 0;
		int j;
		mlx_put_pixel(main_game->image, main_game->player->x * SCALE, main_game->player->y * SCALE, 0xffffff);
		while(i <= main_game->y_p)
		{
			j = 0;
			while (j <= main_game->x_p)
			{
				if(distance(main_game->player->x , main_game->player->y, j, i) <= 3)
						mlx_put_pixel(main_game->image, j  * SCALE, i * SCALE, 0xffffff);
				j++;
			}
			i++;
		}
}
double	normalize(double angle)
{
	while(angle < 0)
	  angle += 2 * M_PI;
  	while(angle >= 2 * M_PI)
        angle -= 2 * M_PI;
    return angle;
}
void	vertical_cast(t_cube *main_game,double angle)
{

	double x_step;
	double y_step;
	double x_inter;
	double y_inter;

	x_inter = floor(main_game->player->x / TILE_SIZE) * TILE_SIZE;
	if(main_game->ray->face_right)
		x_inter += TILE_SIZE;
	y_inter = main_game->player->y + ((x_inter - main_game->player->x) * tan(angle));
	x_step = TILE_SIZE;
	if(main_game->ray->face_left)
		x_step *= -1;
	y_step = x_step * tan(angle);
	if(main_game->ray->face_up && y_step > 0)
		y_step *= -1;
	if(main_game->ray->face_down && y_step < 0)
		y_step *= -1;


	double check_x = x_inter;
	double check_y = y_inter;
	main_game->ray->wall_vertx = check_x;
	main_game->ray->wall_verty = check_y;
	while(check_x >= 0 && check_x <= (main_game->x_p) && check_y >= 0 && check_y <= main_game->y_p)
	{
		double to_checkx = check_x;
		double to_checky = check_y;
		if(main_game->ray->face_left)
			to_checkx -= 0.000001;
		if(is_wall(main_game, to_checkx, to_checky))
		{
			// main_game->ray->wall_vertx = check_x;
			// main_game->ray->wall_verty = check_y;
			break;
		}
		check_x += x_step;
		check_y += y_step;
	}
	main_game->ray->wall_vertx = check_x;
	main_game->ray->wall_verty = check_y;
	// printf("vert %f -- %f  - %f\n", main_game->ray->wall_vertx, main_game->ray->wall_verty, tan(angle));
}
void	horizontal_cast(t_cube *main_game,double angle)
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
	main_game->ray->wall_horzx = check_x;
	main_game->ray->wall_horzy = check_y;
	while(check_x >= 0 && check_x <= (main_game->x_p) && check_y >= 0 && check_y <= main_game->y_p)
	{
				double to_checkx = check_x;
		double to_checky = check_y;
		if(main_game->ray->face_up)
			to_checky -= 0.000001;
		if(is_wall(main_game, to_checkx, to_checky))
		{
			// main_game->ray->wall_horzx = check_x;
			// main_game->ray->wall_horzy = check_y;
			break;
		}
		check_x += x_step;
		check_y += y_step;
	}
	main_game->ray->wall_horzx = check_x;
	main_game->ray->wall_horzy = check_y;
}

// unsigned int get_color(t_cube *main_game, unsigned int y_texture, unsigned int x_texture)
// {
// 	unsigned int rgb0 = (y_texture * main_game->m_north->width  + x_texture) * 4 ;
// 	unsigned int rgb1 = (y_texture * main_game->m_north->width  + x_texture) * 4 + 1;
// 	unsigned int rgb2 = (y_texture * main_game->m_north->width  + x_texture) * 4 + 2;
// 	unsigned int rgb3 = (y_texture * main_game->m_north->width  + x_texture) * 4 + 3;
	
// 	return (ft_pixel(rgb0, rgb1, rgb2, rgb3));
// }

// unsigned int get_north_color(t_cube *main_game, unsigned int y_texture, unsigned int x_texture)
// {
// 	uint8_t *colors;

//     if (main_game == NULL || main_game->m_north == NULL || y_texture >= main_game->m_north->height || x_texture >= main_game->m_north->width)
// 		return (0);
// 	colors = &main_game->m_north->pixels[(y_texture * (main_game->m_north->width * 4) + x_texture * 4)];
// 		return ft_pixel(colors[0], colors[1], colors[2], colors[3]);
// }

// unsigned int get_south_color(t_cube *main_game, unsigned int y_texture, unsigned int x_texture)
// {
// 	uint8_t *colors;

//     if (main_game == NULL || main_game->m_south == NULL || y_texture >= main_game->m_south->height || x_texture >= main_game->m_south->width)
// 		return (0);
// 	colors = &main_game->m_south->pixels[(y_texture * (main_game->m_south->width * 4) + x_texture * 4)];
// 		return ft_pixel(colors[0], colors[1], colors[2], colors[3]);
// }

unsigned int get_color(mlx_image_t *sight, unsigned int y_texture, unsigned int x_texture)
{
	uint8_t *colors;

    if (sight == NULL || sight == NULL || y_texture >= sight->height || x_texture >= sight->width)
		return (0);
	colors = &sight->pixels[(y_texture * (sight->width * 4) + x_texture * 4)];
		return ft_pixel(colors[0], colors[1], colors[2], colors[3]);
}


void	cast_ray(t_cube *main_game, double angle, int *i)
{
	// printf("angle  : %f \n", angle );
	// printf("FOV : %f\n", (main_game->ray->FOV_ANGLE ));
	// if(main_game->ray->face_up)
	// 	puts("up");
	// if(!main_game->ray->face_up)
	// 	puts("down");
	// if(main_game->ray->face_right)
	// 	puts("right");
	// if(!main_game->ray->face_right)
	// 	puts("left");
	horizontal_cast(main_game,angle);
	vertical_cast(main_game,angle);
	double ray_distance;
	double perpdistance;
	double projection;
	double wallstrip;
	int wall_top;
	int wall_bottom;
	
	double horz_distance = distance(main_game->player->x, main_game->player->y, main_game->ray->wall_horzx, main_game->ray->wall_horzy);
	double vert_distance = distance(main_game->player->x, main_game->player->y, main_game->ray->wall_vertx, main_game->ray->wall_verty);
	double hitx = 0;
	double hity = 0;
	main_game->check_vert = 0;
	if(horz_distance < vert_distance)
	{	
		hitx = main_game->ray->wall_horzx;
		hity = main_game->ray->wall_horzy;
		ray_distance = horz_distance;
	}
	else
	{
		main_game->check_vert = 1;
		hitx = main_game->ray->wall_vertx;
		hity = main_game->ray->wall_verty;
		ray_distance = vert_distance;
	}
	perpdistance = ray_distance * cos(angle - main_game->player->r_angle);
			//printf("lsss %f\n", perpdistance);

	if(perpdistance <= 0)
		perpdistance = 4;
	projection = (main_game->x_p / 2) / tan(main_game->ray->FOV_ANGLE / 2);
	wallstrip = (TILE_SIZE / perpdistance) * projection;
	wall_top = (main_game->y_p / 2) - (wallstrip / 2); 
	if(wall_top < 0)
		wall_top = 0;
	wall_bottom = (main_game->y_p / 2) + (wallstrip / 2); 
	if(wall_bottom > main_game->y_p)
		wall_bottom = main_game->y_p;
	int y = wall_top;

	mlx_image_t *sight;
	unsigned int color;

	if ((main_game->ray_angle_image > M_PI && main_game->ray_angle_image < 2 * M_PI) && main_game->check_vert == 0)
		sight = main_game->m_south;
	else if (main_game->check_vert == 0)
		sight = main_game->m_north;
	if ((main_game->ray_angle_image < (3 * M_PI / 2) && main_game->ray_angle_image > M_PI / 2 )&&  main_game->check_vert == 1)
		sight = main_game->m_east;
	else if(main_game->check_vert == 1)
		sight = main_game->m_west;
	// mlx_image_t *north_sight = main_game->m_north;
	// mlx_image_t *south_sight = main_game->m_south;
	// mlx_image_t *east_sight = main_game->m_east;
	// mlx_image_t *west_sight = main_game->m_west;
	
	int texturs_x;
	if (main_game->check_vert)
		texturs_x = (int)(main_game->ray->wall_verty * ((float)sight->width / TILE_SIZE)) % sight->width;
	else 
		texturs_x = (int)(main_game->ray->wall_horzx * ((float)sight->width / TILE_SIZE)) % sight->width;
		// texturs_x = (int)((main_game->ray->wall_horzx * sight->width) / TILE_SIZE) % sight->width;
	while(y < wall_bottom)
	{
	 	int mm = y + ( wallstrip / 2) - (main_game->y_p / 2); 
        int y_texture = mm * ((double)sight->height / wallstrip);
		// if (main_game->ray->face_up  && main_game->check_vert == 1)
		// 	color = get_north_color(main_game, y_texture, texturs_x);
		// else if (main_game->ray->face_down  && main_game->check_vert == 1)
		// 	color = get_south_color(main_game, y_texture, texturs_x);
		// else if (main_game->ray->face_left  && !main_game->check_vert)
		// 	color = get_east_color(main_game, y_texture, texturs_x);
		// else if (main_game->ray->face_right  && !main_game->check_vert)
		color = get_color(sight, y_texture, texturs_x);
		mlx_put_pixel(main_game->image, *i, y, color);
		y++;
	}
}
void	cast(t_cube *main_game)
{
	int i = 0;
	// double nor_ra= normalize(main_game->player->r_angle);
	double ray_angle = main_game->player->r_angle - (main_game->ray->FOV_ANGLE / 2);
	while(i < main_game->x_p)
	{
		ray_angle = normalize(ray_angle);
		main_game->ray_angle_image = ray_angle;
		main_game->ray->face_right=  (ray_angle < 0.5 * M_PI || ray_angle > 1.5 * M_PI);
		main_game->ray->face_left = !(main_game->ray->face_right);
		main_game->ray->face_down = (ray_angle > 0 && ray_angle < M_PI);
		main_game->ray->face_up = !(main_game->ray->face_down);
		cast_ray(main_game, ray_angle, &i);
		ray_angle += (main_game->ray->FOV_ANGLE / ((main_game->x_p)));
		i++;
	}

}
void	player_update(t_cube *main_game)
{
		main_game->player->steps = main_game->player->walk_direction * main_game->player->speed;
		main_game->player->r_angle += main_game->player->turn_direction * main_game->player->r_speed;
		double old_x = main_game->player->x;
		double old_y = main_game->player->y;
		main_game->player->x += cos(main_game->player->r_angle) * main_game->player->steps;
		main_game->player->y += sin(main_game->player->r_angle) * main_game->player->steps;
		main_game->player->x_r = main_game->player->x + cos(main_game->player->r_angle) * 40;
		main_game->player->y_r = main_game->player->y + sin(main_game->player->r_angle) * 40;
		if(is_wall(main_game, main_game->player->x, main_game->player->y))
		{
			main_game->player->x = old_x;
			main_game->player->y = old_y;
		}
		cast(main_game);
}
void	draw_w(t_cube *main_game, int *x, int* y, int color)
{
	int i, j ;
	i = 0;j = 0;
			i = *y * TILE_SIZE; 
			while(i < (TILE_SIZE + (*y * TILE_SIZE)))
			{
				j = *x * TILE_SIZE; 
				while(j < (TILE_SIZE + (*x * TILE_SIZE)))
				{
				mlx_put_pixel(main_game->image, j  * SCALE,i  * SCALE, color);
				j++;
				}
				i++;
			}
}
void	draw_map(t_cube *main_game)
{
	int x, y, i ,j;
	x = 0;
	y = 0;
	i = 0;
	j = 0;
	while(main_game->lmt->map[y])
	{
		x = 0;
		while(main_game->lmt->map[y][x])
		{
			if(main_game->lmt->map[y][x] == '1')
				draw_w(main_game, &x,&y, 0xFF0000);
			x++;
		}
		y++;

	} 
}

int ceiling_color(t_cube *main_game, int upper_half)
{
	int x;
	int y;
	char	**splt;

	splt = ft_split(main_game->cl->cl, ',');
	y = 0;
	while(y < upper_half)
	{
		x = 0;
		while(x < main_game->x_p)
		{
			unsigned int color_cl = ft_pixel(ft_atoi(splt[0]) , ft_atoi(splt[1]), ft_atoi(splt[2]), 255);
			mlx_put_pixel(main_game->image, x, y, color_cl);
			x++;
		}
	y++;
	}
	int f = 0;
	while(splt[f])
	{
		// printf("%p | %s\n", splt[f], splt[f]);
		free(splt[f++]);
	}
	free(splt);
	
	return(y);
}

void	floor_color(t_cube *main_game, int lower_half)
{
	int y;
	int x;
	char **splt;

	splt = ft_split(main_game->cl->fl, ',');
	y = lower_half;
	while(y < main_game->y_p)
	{
	x = 0;
		while(x < main_game->x_p)
		{
			unsigned int color_fl = ft_pixel(ft_atoi(splt[0]), ft_atoi(splt[1]), ft_atoi(splt[2]), 255);
			// printf("%s\n", main_game->cl->fl);
			// printf("%s\n", main_game->cl->fl[1]);
			mlx_put_pixel(main_game->image, x, y, color_fl);
			x++;
		}
	y++; 
	}
	int f = 0;
	while(splt[f])
		free(splt[f++]);
	free(splt);
}

void	ceiling_floor(t_cube *main_game)
{
	// floor_color(main_game);
	int upper_half;
	int lower_half;
	// char	**splt_cl;
	// char	**splt_fl;

	// splt_cl = ft_split(main_game->cl->cl, ',');
	upper_half = main_game->y_p / 2;
	lower_half = ceiling_color(main_game, upper_half);
	// y = upper_half;
	floor_color(main_game, lower_half);
}

void	frame(void * main)
{
	t_cube* main_game = (t_cube *)main;
	ceiling_floor(main_game);
	player_update(main_game);
	mlx_image_to_window(main_game->mlx,main_game->image, 0 , 0);
}
// void dd_callback(void *param)
// {
//     t_cube *main_game = (t_cube *)param;

//     main_game->player->walk_direction = 0;
//     main_game->player->turn_direction = 0;
// 	if(main_game->image)
// 		mlx_delete_image(main_game->mlx, main_game->image);
// 	main_game->image = mlx_new_image(main_game->mlx, (main_game->x_p), ( main_game->y_p ));
// 	if(mlx_is_key_down(main_game->mlx, MLX_KEY_A)) 
//     	main_game->player->turn_direction = -1;
// 	if(mlx_is_key_down(main_game->mlx, MLX_KEY_W))
// 		main_game->player->walk_direction = 1;
// 	if(mlx_is_key_down(main_game->mlx, MLX_KEY_S)) 
// 		main_game->player->walk_direction = -1;
// 	if(mlx_is_key_down(main_game->mlx, MLX_KEY_D))
//     	main_game->player->turn_direction = 1;
//     frame(main_game);
// }
void	move_side(t_cube *main_game, int side)
{
	int x = main_game->player->x;
	int y = main_game->player->y;
	x += cos(main_game->player->r_angle + (M_PI / 2)) * side * main_game->player->speed ;
	y += sin(main_game->player->r_angle + (M_PI / 2)) * side * main_game->player->speed ;
	if(!is_wall(main_game, x, y))
	{
		main_game->player->x = x;
		main_game->player->y = y;
	}
}
void dd_callback(void *param)
{
    t_cube *main_game = (t_cube *)param;

    main_game->player->walk_direction = 0;
    main_game->player->turn_direction = 0;
	if(main_game->image)
		mlx_delete_image(main_game->mlx, main_game->image);
	main_game->image = mlx_new_image(main_game->mlx, (main_game->x_p), ( main_game->y_p ));
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_LEFT)) 
    	main_game->player->turn_direction = -1;
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_W))
		main_game->player->walk_direction = 1;
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_D))
		move_side(main_game, 1);
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_A))
		move_side(main_game, -1);
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_S)) 
		main_game->player->walk_direction = -1;
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_RIGHT))
    	main_game->player->turn_direction = 1;
	if(mlx_is_key_down(main_game->mlx, MLX_KEY_ESCAPE))
		exit(1);
	frame(main_game);
}

void	cub(t_cube *main_game)
{
	int i = 0;
	int j = 0;
	int k = 0;
	while(main_game->lmt->map[i])
	{
		j = 0;
		while(main_game->lmt->map[i][j])
			j++;
		if(j > k)
			k = j;
		i++;
	}
	main_game->x_p = (k - 1) * TILE_SIZE;
	main_game->y_p = (i) * TILE_SIZE;

	main_game->player = malloc(sizeof(t_player));
	main_game->ray = malloc(sizeof(t_ray));
	get_player_pos(main_game);
	player_init(main_game);
	main_game->mlx = mlx_init(main_game->x_p ,main_game->y_p , "cube", FALSE);
	main_game->image = mlx_new_image(main_game->mlx,main_game->x_p , main_game->y_p);
	mlx_put_pixel(main_game->image, 0, 0, ft_pixel(255, 172, 28, 255));
	ft_upload_texture_img(main_game);
	frame(main_game);	
	mlx_loop_hook(main_game->mlx, dd_callback, main_game);
	mlx_loop(main_game->mlx);
}