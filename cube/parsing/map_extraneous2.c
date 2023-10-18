/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extraneous2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/18 12:56:50 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/18 13:17:07 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

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
			ft_error("Unsealed map!\n");
	}
	x = -1;
	if (map[j + 1])
	{
		while (++x < i)
		{
			while (is_whitesp_butnl(map[j + 1][x]))
				x++;
			if (map[j + 1][x] != '1')
				ft_error("Unsealed map!\n");
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

void	recheck_rev(char **map)
{
	int	j;
	int	i;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if ((map[j][i] == '0' || dir_op(map[j][i])))
			{
				if (map[j][i - 1] && is_white_space(map[j][i - 1]))
					ft_error("Unsealed map!\n");
			}
			i++;
		}
		j++;
	}
}
