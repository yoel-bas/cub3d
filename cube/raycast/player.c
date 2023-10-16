/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   player.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 17:06:09 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 17:11:55 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	player_init(t_cube *main_game)
{
	main_game->player->turn_direction = 0;
	main_game->player->walk_direction = 0;
	main_game->player->speed = 5.00;
	main_game->player->r_speed = 2 * (M_PI / 180);
	if (main_game->dir_flag == 1)
		main_game->player->r_angle = M_PI / 2;
	if (main_game->dir_flag == 2)
		main_game->player->r_angle = M_PI;
	if (main_game->dir_flag == 3)
		main_game->player->r_angle = (3 * M_PI) / 2;
	if (main_game->dir_flag == 4)
		main_game->player->r_angle = 2 * M_PI ;
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

void	frame(void *main)
{
	t_cube	*main_game;

	main_game = (t_cube *)main;
	ceiling_floor (main_game);
	player_update (main_game);
	mlx_image_to_window(main_game->mlx, main_game->image, 0, 0);
}
