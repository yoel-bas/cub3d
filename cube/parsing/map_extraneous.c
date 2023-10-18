/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_extraneous.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 02:07:07 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/18 13:16:26 by melayoub         ###   ########.fr       */
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
			if ((map[j][i] == '0' || dir_op(map[j][i])))
			{
				if (map[j][i + 1] && is_white_space(map[j][i + 1]))
					ft_error("unsealed map!\n");
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
				&& (map[j][i] == '0' || dir_op(map[j][i])))
			{
				if ((map[j - 1][i] && is_whitesp_butnl(map[j - 1][i]))
				|| (map[j + 1][i] && is_whitesp_butnl(map[j + 1][i])))
					ft_error("Unsealed map!\n");
			}
			i++;
		}
		j++;
	}
}

void	ext_updwn(char **map)
{
	int	j;
	int	i;
	int	x;

	j = 1;
	while (map[j])
	{
		i = 0;
		x = i;
		while (map[j][i])
		{
			if (map[j][i] == '0' || dir_op(map[j][i]))
			{
				if (map[j - 1][x] && is_white_space(map[j - 1][x]))
					ft_error("Unsealed map!\n");
				if (map[j + 1] && map[j + 1][x]
					&& is_white_space(map[j + 1][x]))
					ft_error("Unsealed map!\n");
			}
			i++;
			x++;
		}
		j++;
	}
}

void	ft_line_check(char *lng, char *shrt)
{
	int	i;

	i = ft_strlen(shrt);
	while (lng[i])
	{
		if ((lng[i] != '1' && !is_white_space(lng[i])) || lng[i] == '0')
			ft_error("ERROR: Unsealed perimeter");
		i++;
	}
	return ;
}

void	check_extra_len(char **map)
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
