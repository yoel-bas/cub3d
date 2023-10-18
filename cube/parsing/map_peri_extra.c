/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_peri_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 02:07:07 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/18 01:17:05 by melayoub         ###   ########.fr       */
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
				printf("%c\n", map[j][i]);
				printf("-1 %d\n", map[j - 1][i]);
				printf("+1 %d\n", map[j + 1][i]);
				if ((map[j - 1][i] && is_whitesp_butnl(map[j - 1][i]))
				|| (map[j + 1][i] && is_whitesp_butnl(map[j + 1][i])))
					ft_error("ERROR: Unsealed perimeter (mid_map)");
			}
			i++;
		}
		j++;
	}
}

void	norm_extranous(char **map, int j)
{
	int	i;
	int	x;

	i = 0;
	x = -1;
	while (is_whitesp_butnl(map[j][i]))
		i++;
	while (++x < i)
	{
		while (is_whitesp_butnl(map[j - 1][x]))
			x++;
		if (map[j - 1][x] != '1')
			ft_error("ERROR: Unsealed perimeter (west_side)1");
	}
	x = -1;
	if (map[j + 1])
	{
		while (++x < i)
		{
			while (is_whitesp_butnl(map[j + 1][x]))
				x++;
			if (map[j + 1][x] != '1')
				ft_error("ERROR: Unsealed perimeter (west_side2)");
		}
	}
}

void	check_extranous_revsp(char **map)
{
	int	j;

	j = 1;
	while (map[j])
	{
		if (is_whitesp_butnl(map[j][0]))
			norm_extranous(map, j);
		j++;
	}
}
