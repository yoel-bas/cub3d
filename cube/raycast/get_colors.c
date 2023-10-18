/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_colors.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:44:39 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/18 16:42:11 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

unsigned int	ft_pixel(unsigned int r, unsigned int g
				, unsigned int b, unsigned int a)
{
	return (r << 24 | g << 16 | b << 8 | a);
}

unsigned int	get_color(mlx_image_t *sight,
	unsigned int y_texture, unsigned int x_texture)
{
	uint8_t	*colors;

	if (sight == NULL || y_texture >= sight->height
		|| x_texture >= sight->width)
		return (0);
	colors = &sight->pixels[(y_texture * (sight->width * 4) + x_texture * 4)];
	return (ft_pixel(colors[0], colors[1], colors[2], colors[3]));
}

unsigned int	ceiling_color(t_cube *main_game, int upper_half)
{
	int				f;
	int				x;
	int				y;
	char			**splt;
	unsigned int	color_cl;

	splt = ft_split(main_game->cl->cl, ',');
	y = 0;
	while (y < upper_half)
	{
		x = 0;
		while (x < WIDTH)
		{
			color_cl = ft_pixel(ft_atoi(splt[0]),
					ft_atoi(splt[1]), ft_atoi(splt[2]), 255);
			mlx_put_pixel(main_game->image, x, y, color_cl);
			x++;
		}
		y++;
	}
	f = 0;
	while (splt[f])
		free(splt[f++]);
	free(splt);
	return (y);
}

void	floor_color(t_cube *main_game, int lower_half)
{
	int				f;
	int				y;
	int				x;
	char			**splt;
	unsigned int	color_fl;

	splt = ft_split(main_game->cl->fl, ',');
	y = lower_half;
	while (y < HEIGHT)
	{
		x = 0;
		while (x < WIDTH)
		{
			color_fl = ft_pixel(ft_atoi(splt[0]),
					ft_atoi(splt[1]), ft_atoi(splt[2]), 255);
			mlx_put_pixel(main_game->image, x, y, color_fl);
			x++;
		}
		y++; 
	}
	f = 0;
	while (splt[f])
		free(splt[f++]);
	free(splt);
}

void	ceiling_floor(t_cube *main_game)
{
	int	upper_half;
	int	lower_half;

	upper_half = HEIGHT / 2;
	lower_half = ceiling_color(main_game, upper_half);
	floor_color(main_game, lower_half);
}
