/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_components.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 02:36:45 by melayoub          #+#    #+#             */
/*   Updated: 2023/09/26 22:57:26 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

int	foreign_material(char **map)
{
	int	j;
	int	i;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (map[j][i])
		{
			if (map[j][i] == '\n')
				break ;
			if (map[j][i] != '1' && map[j][i] != '0')
				return (0);
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

// int	is_pos_dir(char x)
// {
// 	if (x == 'N' || x == 'S' || x == 'W' || x == 'E')
// 		return (1);
// 	else
// 		return (0);
// }

// int	is_clr(char x)
// {
// 	if (x == 'F' || x == 'C')
// 		return (1);
// 	else
// 		return (0);
// }

// void	player_pos_dir(char **file)
// {
// 	int	i;
// 	int	j;
// 	int	flag;

// 	flag = 0;
// 	i = 0;
// 	j = 0;
// 	while (file[j])
// 	{
// 		while (file[j][i])
// 		{
// 			if (is_pos_dir(file[j][i]))
// 				flag = 1;
// 			else if (is_clr(file[j][i]))
// 				flag = 2;
// 			i++;
// 			if (flag == 1 && is_pos_dir(file[j][i]))
// 				ft_error("ERROR: More than one initial player position");
// 			if (flag == 2  && is_clr(file[j][i]))
// 				ft_error("ERROR: More than 2 color codes"); 
// 		}
// 		j++;
// 	}
// 	if (!flag)
// 		ft_error("ERROR: missing player position or color code!");
// 	else
// 		return ;
// }

void	check_components(char **map)
{
	if (comp_counter(map, '1') < 1)
		ft_error("ERROR: No walls!");
	if (comp_counter(map, '0') < 1)
		ft_error("ERROR: No space to roam!");
	else
		return ;
}