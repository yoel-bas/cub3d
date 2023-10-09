/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_perimeter.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 04:28:07 by melayoub          #+#    #+#             */
/*   Updated: 2023/09/26 21:31:03 by melayoub         ###   ########.fr       */
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
		if (map[j][i] != '1')
			ft_error("ERROR: Missing walls!");
		i++;
	}
}

void	check_sides(char **map)
{
	int	j;

	j = 1;
	while (map[j])
	{
		if (map[j][0] != '1' || map[j][ft_strlen(map[j]) - 2] != '1')
			ft_error("ERROR: Missing walls!");
		j++;
	}
}

void	ft_line_check(char *lng, char *shrt)
{
	int	i;

	i = ft_strlen(shrt);
	while (lng[i])
	{
		if (lng[i] != '1' && lng[i] != '\n')
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
