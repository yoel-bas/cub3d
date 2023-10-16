/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_peri_extra.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 02:07:07 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 13:36:51 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_line_check(char *lng, char *shrt)
{
	int	i;

	i = ft_strlen(shrt);
	while (lng[i])
	{
		if (lng[i] != '1')
			ft_error("ERROR: Unsealed perimeter (east_side)");
		i++;
	}
	return ;
}

void	check_extranous_spaces(char **map)
{
	int	j;

	j = 0;
	while (map[j])
	{
		if (map[j + 1] && ft_strlen(map[j]) != ft_strlen(map[j + 1]))
		{
			if (ft_strlen(map[j]) > ft_strlen(map[j + 1]))
				ft_line_check(map[j], map[j + 1]);
			else
				ft_line_check(map[j + 1], map[j]);
		}
		j++;
	}
}

void	check_inner_extranous(char **map)
{
	int	j;
	int	i;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j - 1] && map[j + 1] && map[j][i] == '0')
			{
				if ((map[j - 1][i] && is_white_space(map[j - 1][i]))
				|| (map[j - 1][i] && is_white_space(map[j + 1][i])))
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
