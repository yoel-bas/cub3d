/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_textures.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:35:56 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/17 18:38:16 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_upload_texture_img(t_cube *content)
{
	content->north_img = mlx_load_png(content->cp->n);
	content->south_img = mlx_load_png(content->cp->s);
	content->east_img = mlx_load_png(content->cp->e);
	content->west_img = mlx_load_png(content->cp->w);
	if (!content->north_img || !content->south_img
		|| !content->east_img || !content->west_img) 
		ft_error("ERROR: load_png failed");
	content->m_north = mlx_texture_to_image(content->mlx, content->north_img);
	content->m_south = mlx_texture_to_image(content->mlx, content->south_img);
	content->m_east = mlx_texture_to_image(content->mlx, content->east_img);
	content->m_west = mlx_texture_to_image(content->mlx, content->west_img);
	if (!content->m_north || !content->m_south
		|| !content->m_east || !content->m_west)
		ft_error("ERROR: texture loading issue!");
}

void	get_border(t_cube *main_game)
{
	int	i;
	int	j;
	int	k;

	i = -1;
	k = 0;
	while (main_game->lmt->map[++i])
	{
		j = 0;
		while (main_game->lmt->map[i][j])
			j++;
		if (j > k)
			k = j;
	}
	main_game->x_p = (k - 1) * TILE_SIZE;
	main_game->y_p = (i) * TILE_SIZE;
}

double	distance(double x, double y, double x1, double y1)
{
	return (sqrt(pow((x1 - x), 2) + pow((y1 - y), 2)));
}

void	texture(t_cube *main_game, mlx_image_t *sight)
{
	if (main_game->check_vert)
		main_game->texturs_x = (int)(main_game->ray->wall_verty
				* ((float)sight->width / TILE_SIZE)) % sight->width;
	else
		main_game->texturs_x = (int)(main_game->ray->wall_horzx
				* ((float)sight->width / TILE_SIZE)) % sight->width;
}
