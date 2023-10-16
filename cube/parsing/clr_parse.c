/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:20 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 13:20:23 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}

void	free_dbl(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

void	clr_parse(char *str)
{
	char	**splt;
	int		j;
	int		i;

	splt = ft_split(str, ',');
	if (!splt[2] || splt[3])
		ft_error("ERROR: incorrect RGB format");
	j = 0;
	while (splt[j])
	{
		if (ft_atoi(splt[j]) > 255 || ft_atoi(splt[j]) < 0)
			ft_error("ERROR: incorrect RGB format");
		i = 0;
		while (splt[j][i])
		{
			if (splt[j][i] == '\n')
				break ;
			if (!ft_is_digit(splt[j][i]))
				ft_error("ERROR: incorrect RGB format");
			i++;
		}
		j++;
	}
	free_dbl (splt);
}