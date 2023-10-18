/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clr_parse.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 13:16:20 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/17 23:56:41 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	free_dbl(char **str)
{
	int	i;

	i = 0;
	while (str[i])
		free(str[i++]);
	free(str);
}

int	ft_count(char **spt)
{
	int	l;

	l = 0;
	while (spt[l])
		l++;
	return (l);
}

void	count_commas(char *str)
{
	int	i;
	int	c_count;

	c_count = 0;
	i = 0;
	while (str[i])
	{
		if (str[i] == ',')
			c_count++;
		i++;
	}
	if (c_count != 2)
		ft_error("ERROR: incorrect RGB format");
}

int	check_dgts(char *num)
{
	int	i;

	i = 0;
	while (num[i])
	{
		while (is_white_space(num[i]))
			i++;
		if (!ft_is_digit(num[i]))
			return (0);
		i++;
	}
	i = 0;
	while (num[i] == '0' || is_white_space(num[i]))
		i++;
	if (ft_strlen(&num[i]) > 3 || !ft_strlen(&num[i]))
		return (puts("fk"), 0);
	return (1);
}

void	clr_parse(char *str)
{
	char	**splt;
	int		j;
	char	*alloc;

	count_commas(str);
	splt = ft_split(str, ',');
	if (ft_count(splt) != 3)
		ft_error("ERROR: incorrect RGB format3");
	j = 0;
	while (splt[j])
	{
		alloc = ft_strtrim(splt[j], " \t");
		if (ft_atoi(alloc) != 0 && !check_dgts(alloc))
			ft_error("ERROR: incorrect RGB format1");
		if (ft_atoi(alloc) > 255 || ft_atoi(alloc) < 0)
			ft_error("ERROR: incorrect RGB format0");
		free (alloc);
		j++;
	}
	free_dbl (splt);
}
