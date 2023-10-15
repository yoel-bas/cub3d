/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_perimeter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 04:28:07 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/15 20:10:34 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	check_top_bottom(char **map)
{
	int	i = 0;
	int	j = 0;

	while (map[0][i])
	{
		if (map[0][i] == '\n')
			break ;
		while(is_whitesp_butnl(map[0][i]))
			i++;
		if (map[0][i] != '1')
			ft_error("ERROR: Missing walls!");
		i++;
	}
	while (map[j])
		j++;
	j--;
	i = 0;
	while (map[j][i])
	{
		if (map[j][i] == '\n')
			return ;
		while(is_whitesp_butnl(map[j][i]))
			i++;
		if (map[j][i] != '1')
			ft_error("ERROR: Missing walls!");
		i++;
	}
}

void	check_sides(char **map)
{
	int	j;
	int i;

	j = 0;
	while (map[j])
	{
		i = 0;
		while(is_whitesp_butnl(map[j][i]))
			i++;
		if (map[j][i] != '1' || map[j][ft_strlen(map[j]) - 2] != '1')
			ft_error("ERROR: Missing walls44!");
		j++;
	}
}

void	ft_line_check(char *lng, char *shrt)
{
	int	i;

	i = ft_strlen(shrt) - 1;
	while (lng[i])
	{
		// if (lng[i] != '1' && lng[i] != '\n')
		if (lng[i] == '0')
			ft_error("ERROR: Unsealed perimeter");
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

void	check_extranous_revsp(char **map)
{
	int j;
	int i;
	int x;
	
	j = 1;
	while(map[j])
	{
		if (is_whitesp_butnl(map[j][0]))
		{
			x = 0;
			i = 0;
			while(is_whitesp_butnl(map[j][i]))
				i++;
			while(x < i)
			{
				if (map[j - 1][x] == '0')
					ft_error("TF1");
				x++;
			}
			puts("ok");	
			x = 0;
			if (map[j + 1])
			{
				while(x < i)
				{
					if (map[j + 1][x] == '0')
						ft_error("TF2");
					x++;
				}
			}
			
		}
		j++;
	}
}
