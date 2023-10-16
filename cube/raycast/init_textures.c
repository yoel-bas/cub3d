/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init_txtures.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 16:35:56 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 17:06:20 by melayoub         ###   ########.fr       */
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
