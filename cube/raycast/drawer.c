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

void	draw_w(t_cube *main_game, int *x, int* y, int color)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	i = *y * TILE_SIZE; 
	while (i < (TILE_SIZE + (*y * TILE_SIZE)))
	{
		j = *x * TILE_SIZE; 
		while (j < (TILE_SIZE + (*x * TILE_SIZE)))
		{
			mlx_put_pixel(main_game->image, j  * SCALE,i  * SCALE, color);
			j++;
		}
		i++;
	}
}

void	draw_map(t_cube *main_game)
{
	int	x;
	int	y;
	int	i;
	int	j;

	x = 0;
	y = 0;
	i = 0;
	j = 0;
	while (main_game->lmt->map[y])
	{
		x = 0;
		while (main_game->lmt->map[y][x])
		{
			if (main_game->lmt->map[y][x] == '1')
				draw_w(main_game, &x,&y, 0xFF0000);
			x++;
		}
		y++;

	}
}
