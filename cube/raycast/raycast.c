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

int	is_wall(t_cube *main_game, double x1, double y1)
{
	int	x;
	int	y;

	x = x1 / TILE_SIZE;
	y = y1 / TILE_SIZE;
	if (x < 0 && x >= (main_game->x_p) && y < 0 && y >= (main_game->y_p))
		return (1);
	if (main_game->lmt->map[y][x] && main_game->lmt->map[y][x] == '1')
		return (1);
	return (0);
}

mlx_image_t	*sight_face(t_cube *main_game)
{
	mlx_image_t	*sight;

	if ((main_game->ray_angle_image > M_PI && 
			main_game->ray_angle_image < 2 * M_PI) 
		&& main_game->check_vert == 0)
		sight = main_game->m_south;
	else if (main_game->check_vert == 0)
		sight = main_game->m_north;
	if ((main_game->ray_angle_image < (3 * M_PI / 2) 
			&& main_game->ray_angle_image > M_PI / 2)
		&& main_game->check_vert == 1)
		sight = main_game->m_east;
	else if (main_game->check_vert == 1)
		sight = main_game->m_west;
	return (sight);
}

void	calc(t_cube *mg, int horz_distance, int vert_distance, double angle)
{
	mg->check_vert = 0;
	if (horz_distance < vert_distance)
		mg->ray_distance = horz_distance;
	else
	{
		mg->check_vert = 1;
		mg->ray_distance = vert_distance;
	}
	mg->perpdistance = mg->ray_distance * cos(angle - mg->player->r_angle);
	mg->projection = (WIDTH / 2) / tan(mg->ray->fov_angle / 2);
	mg->wallstrip = (TILE_SIZE / mg->perpdistance) * mg->projection;
	mg->wall_top = (HEIGHT / 2) - (mg->wallstrip / 2); 
	if (mg->wall_top < 0)
		mg->wall_top = 0;
	mg->wall_bottom = (HEIGHT / 2) + (mg->wallstrip / 2); 
	if (mg->wall_bottom > HEIGHT)
		mg->wall_bottom = HEIGHT;
}

void	cast_ray(t_cube *main_game, double angle, int *i)
{
	mlx_image_t		*sight;
	double			horz_distance;
	double			vert_distance;

	horizontal_cast(main_game, angle);
	vertical_cast(main_game, angle);
	horz_distance = distance(main_game->player->x, main_game->player->y,
			main_game->ray->wall_horzx, main_game->ray->wall_horzy);
	vert_distance = distance(main_game->player->x, main_game->player->y, 
			main_game->ray->wall_vertx, main_game->ray->wall_verty);
	calc(main_game, horz_distance, vert_distance, angle);
	sight = sight_face(main_game);
	texture(main_game, sight);
	while (main_game->wall_top < main_game->wall_bottom)
	{
		main_game->mm = main_game->wall_top 
			+ (main_game->wallstrip / 2) - (HEIGHT / 2);
		main_game->y_texture = main_game->mm 
			* ((double)sight->height / main_game->wallstrip);
		main_game->color = get_color(sight, 
				main_game->y_texture, main_game->texturs_x);
		mlx_put_pixel(main_game->image, *i, 
			main_game->wall_top, main_game->color);
		main_game->wall_top++;
	}
}

void	cast(t_cube *main_game)
{
	int		i;
	double	ray_angle;

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
