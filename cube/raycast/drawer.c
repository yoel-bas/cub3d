/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   drawer.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:52:10 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 16:58:49 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

double	normalize(double angle)
{
	while (angle < 0)
		angle += 2 * M_PI;
	while (angle >= 2 * M_PI)
		angle -= 2 * M_PI;
	return (angle);
}

void	calcul_vertical(t_cube *main_game, double angle)
{
	main_game->x_inter = floor(main_game->player->x / TILE_SIZE) * TILE_SIZE;
	if (main_game->ray->face_right)
		main_game->x_inter += TILE_SIZE;
	main_game->y_inter = main_game->player->y 
		+ ((main_game->x_inter - main_game->player->x) * tan(angle));
	main_game->x_step = TILE_SIZE;
	if (main_game->ray->face_left)
		main_game->x_step *= -1;
	main_game->y_step = main_game->x_step * tan(angle);
	if (main_game->ray->face_up && main_game->y_step > 0)
		main_game->y_step *= -1;
	if (main_game->ray->face_down && main_game->y_step < 0)
		main_game->y_step *= -1;
}

void	vertical_cast(t_cube *main_game, double angle)
{
	double	check_x;
	double	check_y;
	double	to_checkx;
	double	to_checky;

	calcul_vertical(main_game, angle);
	check_x = main_game->x_inter;
	check_y = main_game->y_inter;
	while (check_x >= 0 && check_x <= (main_game->x_p) 
		&& check_y >= 0 && check_y <= main_game->y_p)
	{
		to_checkx = check_x;
		to_checky = check_y;
		if (main_game->ray->face_left)
			to_checkx -= 1;
		if (is_wall(main_game, to_checkx, to_checky))
			break ;
		check_x += main_game->x_step;
		check_y += main_game->y_step;
	}
	main_game->ray->wall_vertx = check_x;
	main_game->ray->wall_verty = check_y;
}

void	calcul_horizontal(t_cube *main_game, double angle)
{
	main_game->y_inter = floor(main_game->player->y / TILE_SIZE) * TILE_SIZE;
	if (main_game->ray->face_down)
		main_game->y_inter += TILE_SIZE;
	main_game->x_inter = main_game->player->x 
		+ ((main_game->y_inter - main_game->player->y) / tan(angle));
	main_game->y_step = TILE_SIZE;
	if (main_game->ray->face_up)
		main_game->y_step *= -1;
	main_game->x_step = main_game->y_step / tan(angle);
	if (main_game->ray->face_left && main_game->x_step > 0)
		main_game->x_step *= -1;
	if (main_game->ray->face_right && main_game->x_step < 0)
		main_game->x_step *= -1;
}

void	horizontal_cast(t_cube *main_game, double angle)
{
	double	check_x; 
	double	check_y;
	double	to_checkx;
	double	to_checky;

	calcul_horizontal(main_game, angle);
	check_x = main_game->x_inter;
	check_y = main_game->y_inter;
	while (check_x >= 0 && check_x <= (main_game->x_p) 
		&& check_y >= 0 && check_y <= main_game->y_p)
	{
		to_checkx = check_x;
		to_checky = check_y;
		if (main_game->ray->face_up)
			to_checky -= 1;
		if (is_wall(main_game, to_checkx, to_checky))
			break ;
		check_x += main_game->x_step;
		check_y += main_game->y_step;
	}
	main_game->ray->wall_horzx = check_x;
	main_game->ray->wall_horzy = check_y;
}
