/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   raycast.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 15:25:21 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 17:12:13 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"




double	distance(double x, double y, double x1, double y1)
{
	return (sqrt(pow((x1 - x), 2) + pow((y1 - y), 2)));
}

int	is_wall(t_cube *main_game, double x1, double y1)
{
	int	x;
	int	y;

	x = x1 / TILE_SIZE;
	y = y1 / TILE_SIZE;
	if (x < 0  && x  >= (main_game->x_p) && y < 0  && y >= (main_game->y_p))
		return (1);
	if (main_game->lmt->map[y][x] && main_game->lmt->map[y][x] == '1')
		return (1);
	return (0);
}

void	line(t_cube *main_game, double x, double y, double x1, double y1)
{
	int		i;
	double	x_inc;
	double	y_inc;
	double	dx;
	double	dy;

	i = 0;
	dx = x1 - x;
	dy = y1 - y;
	if (fabs(dx) > fabs(dy))
		main_game->step = fabs(dx);
	else 
		main_game->step = fabs(dy);
	x_inc = dx / main_game->step;
	y_inc = dy / main_game->step;
	while (i < main_game->step)
	{
		mlx_put_pixel(main_game->image, round(x),round(y) , 0x00DDB2);
		x += x_inc;
		y += y_inc;
		i++;
	}
}


double	normalize(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
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
			to_checkx -= 1;
		if(is_wall(main_game, to_checkx, to_checky))
		{
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
			to_checky -= 1;
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




void	cast_ray(t_cube *main_game, double angle, int *i)
{
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
		hitx = main_game->ray->wall_horzx ;
		hity = main_game->ray->wall_horzy ;
		ray_distance = horz_distance ;
	}
	else
	{
		main_game->check_vert = 1;
		hitx = main_game->ray->wall_vertx;
		hity = main_game->ray->wall_verty;
		ray_distance = vert_distance ;
	}
	perpdistance = ray_distance * cos(angle - main_game->player->r_angle);
	projection = (WIDTH / 2) / tan(main_game->ray->fov_angle / 2);

	wallstrip = (TILE_SIZE / perpdistance) * projection;

	wall_top = (HEIGHT / 2) - (wallstrip / 2); 
	if(wall_top < 0)
		wall_top = 0;
	wall_bottom = (HEIGHT / 2) + (wallstrip / 2); 
	if(wall_bottom > HEIGHT)
		wall_bottom = HEIGHT;
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
	 	int mm = y + ( wallstrip / 2) - (HEIGHT/ 2); 
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
	int	i;
	double ray_angle;

	// double nor_ra= normalize(main_game->player->r_angle);
	i = 0;
	ray_angle = main_game->player->r_angle - (main_game->ray->fov_angle / 2);
	while (i < WIDTH)
	{
		ray_angle = normalize(ray_angle);
		main_game->ray_angle_image = ray_angle;
		main_game->ray->face_right = (ray_angle < 0.5 * M_PI 
				|| ray_angle > 1.5 * M_PI);
		main_game->ray->face_left = !(main_game->ray->face_right);
		main_game->ray->face_down = (ray_angle > 0 && ray_angle < M_PI);
		main_game->ray->face_up = !(main_game->ray->face_down);
		cast_ray(main_game, ray_angle, &i);
		ray_angle += (main_game->ray->fov_angle / ((WIDTH)));
		i++;
	}
}

int	between(t_cube *main_game, int x, int y)
{
	x = x / 64;
	y = y / 64;
	if (main_game->lmt->map[y][(int)main_game->player->x / TILE_SIZE] == '1'
		&& main_game->lmt->map[(int)main_game->player->y / TILE_SIZE][x] == '1')
		return (1);
	return (0);
}



void	player_init(t_cube *main_game)
{
	main_game->player->turn_direction = 0;
	main_game->player->walk_direction = 0;
	main_game->player->speed = 4.00;
	main_game->player->r_speed = 2 * (M_PI / 180);
	if (main_game->dir_flag == 1)
		main_game->player->r_angle =  M_PI / 2;
	if (main_game->dir_flag == 2)
		main_game->player->r_angle =  M_PI;
	if (main_game->dir_flag == 3)
		main_game->player->r_angle =  (3 * M_PI) / 2;
	if (main_game->dir_flag == 4)
		main_game->player->r_angle =  2 * M_PI ;

	main_game->player->flg = 0;
	main_game->ray->fov_angle = 60 * (M_PI / 180);
	main_game->ray->num_arays = main_game->ray->fov_angle / main_game->x_p;
}

void	get_player_pos(t_cube *game)
{
	int	y;
	int	x;

	y = 0;
	while (game->lmt->map[y])
	{
		x = 0;
		while (game->lmt->map[y][x])
		{
			if (game->lmt->map[y][x] == 'N' || game->lmt->map[y][x] == 'S'
				|| game->lmt->map[y][x] == 'W' || game->lmt->map[y][x] == 'E')
			{
				game->player->x = (x * TILE_SIZE) + TILE_SIZE / 2;
				game->player->y = (y * TILE_SIZE) + TILE_SIZE / 2;
			}
			x++;
		}
		y++;
	}
}

void	player(t_cube *game)
{
	int	i;
	int	j;

	i = 0;
	mlx_put_pixel(game->image, game->player->x * SCALE,
		game->player->y * SCALE, 0xffffff);
	while (i <= game->y_p)
	{
		j = 0;
		while (j <= game->x_p)
		{
			if (distance(game->player->x, game->player->y, j, i) <= 3)
				mlx_put_pixel(game->image, j  * SCALE, i * SCALE, 0xffffff);
			j++;
		}
		i++;
	}
}

void	player_update(t_cube *mg)
{
	double	old_x;
	double	old_y;

	mg->player->steps = mg->player->walk_direction * mg->player->speed;
	mg->player->r_angle += mg->player->turn_direction * mg->player->r_speed;
	old_x = mg->player->x;
	old_y = mg->player->y;
	mg->player->x += cos(mg->player->r_angle) * mg->player->steps;
	mg->player->y += sin(mg->player->r_angle) * mg->player->steps;
	mg->player->x_r = mg->player->x + cos(mg->player->r_angle) * 40;
	mg->player->y_r = mg->player->y + sin(mg->player->r_angle) * 40;
	if (is_wall(mg, mg->player->x, mg->player->y) || between(mg, old_x, old_y))
	{
		mg->player->x = old_x;
		mg->player->y = old_y;
	}
	cast(mg);
}


void	frame(void * main)
{
	t_cube	*main_game;

	main_game = (t_cube *)main;
	ceiling_floor (main_game);
	player_update (main_game);
	mlx_image_to_window(main_game->mlx,main_game->image, 0, 0);
}

void	move_side(t_cube *main_game, int side)
{
	double	x; 
	double	y;

	x = main_game->player->x;
	y = main_game->player->y;
	x += cos(main_game->player->r_angle
			+ (M_PI / 2)) * side * main_game->player->speed;
	y += sin(main_game->player->r_angle
			+ (M_PI / 2)) * side * main_game->player->speed;
	if (!is_wall(main_game, x, y))
	{
		main_game->player->x = x;
		main_game->player->y = y;
	}
}

void dd_callback(void *param)
{
	t_cube	*main_game;

	main_game = (t_cube *)param;
	main_game->player->walk_direction = 0;
	main_game->player->turn_direction = 0;
	if (main_game->image)
		mlx_delete_image(main_game->mlx, main_game->image);
	main_game->image = mlx_new_image(main_game->mlx, (WIDTH), (HEIGHT));
	if (mlx_is_key_down(main_game->mlx, MLX_KEY_LEFT)) 
		main_game->player->turn_direction = -1;
	if (mlx_is_key_down(main_game->mlx, MLX_KEY_W))
		main_game->player->walk_direction = 1;
	if (mlx_is_key_down(main_game->mlx, MLX_KEY_D))
		move_side(main_game, 1);
	if (mlx_is_key_down(main_game->mlx, MLX_KEY_A))
		move_side(main_game, -1);
	if (mlx_is_key_down(main_game->mlx, MLX_KEY_S)) 
		main_game->player->walk_direction = -1;
	if (mlx_is_key_down(main_game->mlx, MLX_KEY_RIGHT))
		main_game->player->turn_direction = 1;
	if (mlx_is_key_down(main_game->mlx, MLX_KEY_ESCAPE))
		exit(1);
	frame(main_game);
}

void	cub(t_cube *main_game)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (main_game->lmt->map[++i])
	{
		j = -1;
		while (main_game->lmt->map[i][++j]);
		if (j > k)
			k = j;
	}
	main_game->x_p = (k - 1) * TILE_SIZE;
	main_game->y_p = (i) * TILE_SIZE;
	main_game->player = malloc(sizeof(t_player));
	main_game->ray = malloc(sizeof(t_ray));
	get_player_pos(main_game);
	player_init(main_game);
	main_game->mlx = mlx_init(WIDTH ,HEIGHT, "cube", FALSE);
	main_game->image = mlx_new_image(main_game->mlx,WIDTH , HEIGHT);
	ft_upload_texture_img(main_game);
	frame(main_game);
	mlx_loop_hook(main_game->mlx, dd_callback, main_game);
	mlx_loop(main_game->mlx);
}
