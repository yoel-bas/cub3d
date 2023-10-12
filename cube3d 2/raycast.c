#include "cub3d.h"
void	player_init(t_cube *main_game)
{
	main_game->player->turn_direction = 0;
	main_game->player->walk_direction = 0;
	main_game->player->speed = 6.00;
	main_game->player->r_speed = 2 * (M_PI / 180);
	main_game->player->r_angle =  M_PI / 2;
	main_game->player->flg = 0;
	main_game->ray->FOV_ANGLE = 60 * (M_PI / 180);
	main_game->ray->num_arays =  main_game->ray->FOV_ANGLE / main_game->x_p;
	main_game->iter = 0;
}

unsigned int ft_pixel(unsigned int r, unsigned int g, unsigned int b, unsigned int a)
{
	// printf("%X\n", r << 24 | g << 16 | b << 8 | a);
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
			if(main_game->lmt->map[y][x] == 'P')
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

unsigned int get_color(t_cube *main_game, unsigned int y_texture, unsigned int x_texture)
{
	//printf("ana = %d %d %d %d\n", main_game->m_north->pixels[0], main_game->m_north->pixels[1], main_game->m_north->pixels[2], main_game->m_north->pixels[3]);
    // Check for valid inputs and dimensions
    if (main_game == NULL || main_game->m_north == NULL || y_texture >= main_game->m_north->height || x_texture >= main_game->m_north->width) {
        return 0; // Default color (black or another valid color)
    }
	uint8_t *colors = &main_game->m_north->pixels[(y_texture * main_game->m_north->width + x_texture) * 4];
	//uint8_t* pixelstart = &image->pixels[(y * image->width + x) * BPP];

    // Calculate the offsets for each RGB component
    // unsigned int offset0 = main_game->m_north->pixels[(y_texture * main_game->m_north->width) + x_texture];

	//printf("ana = %d %d %d %d\n", main_game->m_north->pixels[offset0], main_game->m_north->pixels[offset0 + 1], main_game->m_north->pixels[offset0 + 2], main_game->m_north->pixels[offset0 + 3]);

    // unsigned int offset1 = offset0 + 1;
    // unsigned int offset2 = offset0 + 2;
    // unsigned int offset3 = offset0 + 3;


    // Call ft_pixel function with the calculated offsets
	//printf("%d %d %d %d\n", colors[0], colors[1], colors[2], colors[4]);
	//exit(0);
	//unsigned int a = ft_pixel(colors[1], colors[2], colors[3], colors[0]);
	//printf("%d\n", a);
    return ft_pixel(colors[0], colors[1], colors[2], colors[3]);
	//return (*colors);
	// return ((y_texture * main_game->m_north->width) + x_texture);
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
	mlx_image_t *sight = main_game->m_north;
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
		unsigned int color = get_color(main_game, y_texture, texturs_x);
		mlx_put_pixel(main_game->image, *i, y, color);
		y++;
	}
	line(main_game, main_game->player->x  * SCALE , main_game->player->y  * SCALE, hitx  * SCALE , hity  * SCALE);
}
void	cast(t_cube *main_game)
{
	int i = 0;
	// double nor_ra= normalize(main_game->player->r_angle);
	double ray_angle = main_game->player->r_angle - (main_game->ray->FOV_ANGLE / 2);
	while(i < main_game->x_p)
	{
		ray_angle = normalize(ray_angle);
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
		player(main_game);
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
	draw_map(main_game);
	mlx_image_to_window(main_game->mlx,main_game->image, 0 , 0);
}
void dd_callback(void *param)
{
    t_cube *main_game = (t_cube *)param;

    main_game->player->walk_direction = 0;
    main_game->player->turn_direction = 0;
	if(main_game->image)
		mlx_delete_image(main_game->mlx, main_game->image);
	main_game->image = mlx_new_image(main_game->mlx, (main_game->x_p), ( main_game->y_p ));
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




void ft_upload_texture_img(t_cube *main_game)
{
	
	main_game->north_img = mlx_load_png("textures/download.png");
	// main_game->north_img->pixels;
	main_game->m_north = mlx_texture_to_image(main_game->mlx, main_game->north_img);
	if (!main_game->m_north)
		exit(2);

	// main_game->south_img = mlx_load_png(main_game->cp->s); // height width "important!!"
	// main_game->north_img = mlx_load_png(main_game->cp->e); // height width "important!!"
	// main_game->north_img = mlx_load_png(main_game->cp->w); // height width "important!!"
	if (!main_game->north_img)
		ft_error("ERROR: load_png failed");
	// for (size_t i = 0; i < main_game->north_img->width * main_game->north_img->height)
	// {
	// 	printf("%hhu\n", main_game->north_img->pixels[i]);
	// }
	
	// printf("%ld | %u\n",  m_north->pixels, (main_game->north_img->width * main_game->north_img->height));
	// // exit(1);
	// main_game->rgbs[0] = ft_calloc(sizeof(int), ((main_game->north_img->width * main_game->north_img->height) / 4));
	// main_game->rgbs[1] = ft_calloc(sizeof(int), main_game->south_img->width * main_game->south_img->height);
	// main_game->rgbs[2] = ft_calloc(sizeof(int), main_game->east_img->width * main_game->east_img->height);
	// main_game->rgbs[3] = ft_calloc(sizeof(int), main_game->west_img->width * main_game->west_img->height);

	// unsigned int i = 0;
	// int j = 0;
	// while (i < (main_game->north_img->width * main_game->north_img->height) / 4)
	// {
	// 	main_game->rgbs[0][i] = ft_pixel(main_game->north_img->pixels[j], main_game->north_img->pixels[j + 1], main_game->north_img->pixels[j + 2], main_game->north_img->pixels[j + 3]);
	// 	i++;
	// 	// if (j <= main_game->north_img->width * main_game->north_img->height * 4) // -4 for some reason ?? 
	// 	j += 4;
	// }
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