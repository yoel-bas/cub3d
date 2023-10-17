/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_peri_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 02:07:07 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/17 22:17:28 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_extranous_spaces(char **map)
{
	int	j;
	int	i;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if ((map[j][i] == '0' || map[j][i] == 'N' || map[j][i] == 'S'
				|| map[j][i] == 'E' || map[j][i] == 'W'))
			{
				if (map[j][i + 1] && is_white_space(map[j][i + 1]))
					ft_error("ERROR unsealed perimetre");
			}
			i++;
		}
		j++;
	}
}

void	check_inner_extranous(char **map)
{
	int	j;
	int	i;

	j = 1;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j - 1] && map[j + 1]
				&& (map[j][i] == '0' || map[j][i] == 'N'
				|| map[j][i] == 'S' || map[j][i] == 'W' || map[j][i] == 'E'))
			{
				if ((map[j - 1][i] && is_white_space(map[j - 1][i]))
				|| (map[j + 1][i] && is_white_space(map[j + 1][i])))
					ft_error("ERROR: Unsealed perimeter (mid_map)");
			}
			i++;
		}
		j++;
	}
}

void	norm_extranous(char **map, int j, int x, int i)
{
	while (is_whitesp_butnl(map[j][i]))
		i++;
	while (x < i)
	{
		if (map[j - 1][x] != '1')
			ft_error("ERROR: Unsealed perimeter (west_side)");
		x++;
	}
	x = 0;
	if (map[j + 1])
	{
		while (x < i)
		{
			if (map[j + 1][x] != '1')
				ft_error("ERROR: Unsealed perimeter (west_side)");
			x++;
		}
	}
}

void	check_extranous_revsp(char **map)
{
	int	j;
	int	i;
	int	x;

	j = 1;
	while (map[j])
	{
		if (is_whitesp_butnl(map[j][0]))
		{
			x = 0;
			i = 0;
			norm_extranous(map, j, x, i);
		}
		j++;
	}
	check_inner_extranous(map);
}
