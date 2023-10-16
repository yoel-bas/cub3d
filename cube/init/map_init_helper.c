/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:56:26 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 19:25:36 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	space_skipper(char *str)
{
	int	i;

	i = 0;
	while (is_white_space(str[i]))
		i++;
}

int	dir_op(char x)
{
	if (x == 'N' || x == 'S'|| x == 'E' || x == 'W')
		return (1);
	else
		return (0);
}



void	read_components(t_cube *cont)
{
	int	j;
	int	i;

	j = 0;
	while (cont->lmt->file[j])
	{
		i = 0;
		while (is_white_space(cont->lmt->file[j][i]))
			i++;
		if (cont->lmt->file[j][i] && dir_op(cont->lmt->file[j][i]))
			ft_is_dir(cont->lmt->file[j], cont);
		else if (cont->lmt->file[j][i] == 'F' || cont->lmt->file[j][i] == 'C')
			ft_is_clr(cont->lmt->file[j], cont);
		else if (cont->lmt->file[j][0] == '\n')
		{
			j++;
			continue ;
		}
		else
		{
			if (cont->lmt->file[j] && fullfilled(cont))
				return (ft_fill_map(cont, &j));
			else
				ft_error("Error: components order");
		}
		j++;
	}
	if (!cont->lmt->file[j])
		ft_error("empty map!");
}
