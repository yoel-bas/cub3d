/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_perimeter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 04:28:07 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 13:46:19 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_top(char **map)
{
	int	i;

	i = 0;
	while (map[0][i])
	{
		if (map[0][i] == '\n')
			break ;
		while (is_whitesp_butnl(map[0][i]))
			i++;
		if (map[0][i] != '1')
			ft_error("ERROR: Missing walls!");
		i++;
	}
}

void	check_bottom(char **map)
{
	int	j;
	int	i;

	j = 0;
	while (map[j])
		j++;
	j--;
	i = 0;
	while (map[j][i])
	{
		if (map[j][i] == '\n')
			return ;
		while (is_whitesp_butnl(map[j][i]))
			i++;
		if (map[j][i] != '1')
			ft_error("ERROR: Missing walls!");
		i++;
	}
}

void	check_sides(char **map)
{
	int	j;
	int	i;

	j = 0;
	while (map[j])
	{
		i = 0;
		while (is_whitesp_butnl(map[j][i]))
			i++;
		if (map[j][i] != '1' || map[j][ft_strlen(map[j]) - 2] != '1')
			ft_error("ERROR: Missing walls!");
		j++;
	}
}
