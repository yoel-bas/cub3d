/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   moves.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 22:37:27 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/10/16 22:37:30 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	between(t_cube *main_game, int x, int y)
{
	x = x / 64;
	y = y / 64;
	if (main_game->lmt->map[y][(int)main_game->player->x / TILE_SIZE] == '1'
		&& main_game->lmt->map[(int)main_game->player->y / TILE_SIZE][x] == '1')
		return (1);
	return (0);
}

void	move_side(t_cube *main_game, int side)
{
	double	x; 
	double	y;

	x = main_game->player->x;
	y = main_game->player->y;
	main_game->player->x += cos(main_game->player->r_angle
			+ (M_PI / 2)) * side * main_game->player->speed;
	main_game->player->y += sin(main_game->player->r_angle
			+ (M_PI / 2)) * side * main_game->player->speed;
	if (is_wall(main_game, main_game->player->x, main_game->player->y))
	{
		main_game->player->x = x;
		main_game->player->y = y;
	}
}

void	dd_callback(void *param)
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

void	close_(void *param)
{
	t_cube	*main_game;

	main_game = (t_cube *)param;
	exit(1);
}

void	cub(t_cube *main_game)
{
	main_game->player = malloc(sizeof(t_player));
	main_game->ray = malloc(sizeof(t_ray));
	get_player_pos(main_game);
	get_border(main_game);
	player_init(main_game);
	main_game->mlx = mlx_init(WIDTH, HEIGHT, "cube", FALSE);
	main_game->image = mlx_new_image(main_game->mlx, WIDTH, HEIGHT);
	ft_upload_texture_img(main_game);
	frame(main_game);
	mlx_loop_hook(main_game->mlx, dd_callback, main_game);
	mlx_close_hook(main_game->mlx, close_, main_game);
	mlx_loop(main_game->mlx);
}
