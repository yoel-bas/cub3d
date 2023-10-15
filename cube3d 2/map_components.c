/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_components.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 02:36:45 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/15 14:56:59 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int is_whitesp_butnl(char c)
{
	if (c == 32 || c == 9 || (c >= 11 && c <= 13))
		return (1);
	return (0);
}

int	foreign_material(char **map)
{
	int	j;
	int	i;
	int wall_flag;

	j = 0;
	while (map[j])
	{
		wall_flag = 0;
		i = 0;
		while (map[j][i])
		{
			// printf("pp-> |%s|\n", map[j]);
			if (map[j][i] == '1')
				wall_flag = 1;
			while(is_whitesp_butnl(map[j][i]) && !wall_flag)
				i++;
			// printf("ZZ>> |%d|\n", map[j][i]);
			if (map[j][i] == '\n')
				break ;
			if (map[j][i] != '1' && map[j][i] != '0' && map[j][i] != 'N' && map[j][i] != 'W' && map[j][i] != 'S' && map[j][i] != 'E')
			{
				// printf("XX>> |%d|\n", map[j][i]);
				return (0);
			}
			i++;
		}
		j++;
	}
	return (1);
}

static int	comp_counter(char **str, char x)
{
	int	count;
	int	i;
	int	j;

	count = 0;
	i = 0;
	j = 0;
	while (str[j])
	{
		while (str[j][i])
		{
			if (str[j][i] == x)
				count++;
			i++;
		}
		i = 0;
		j++;
	}
	return (count);
}

void check_dir(char **map, t_cube *content)
{
	int j;
	int	i;

	content->dir_flag = 0;
	j = 0;
	while(map[j])
	{
		i = 0;
		while(map[j][i])
		{
			if (map[j][i] == 'N' || map[j][i] == 'S' || map[j][i] == 'E' || map[j][i] == 'W')
			{
				if (map[j][i] == 'N')
					content->dir_flag = 1;
				else if (map[j][i] == 'E')
					content->dir_flag = 2;
				else if (map[j][i] == 'S')
					content->dir_flag = 3;
				else if (map[j][i] == 'W')
					content->dir_flag = 4;
			}
			i++;
			if (content->dir_flag && (map[j][i] == 'N' || map[j][i] == 'S'
			|| map[j][i] == 'E' || map[j][i] == 'W'))
				ft_error("ERROR: use of multiple dirrections");			
		}
		j++;
	}
	if (!content->dir_flag)
		ft_error("ERROR: missing dirrection.");
}

void	check_components(char **map)
{
	if (comp_counter(map, '1') < 1)
		ft_error("ERROR: No walls!");
	if (comp_counter(map, '0') < 1)
		ft_error("ERROR: No space to roam!");
	else
		return ;
}