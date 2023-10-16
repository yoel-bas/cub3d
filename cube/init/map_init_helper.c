/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:56:26 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 14:53:09 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	space_skipper(char *str)
{
	int	i;

	i = 0;
	while(is_white_space(str[i]))
		i++;
}

void	read_components(t_cube *content)
{
	int j;
	int	i;

	j = 0;
	while(content->lmt->file[j])
	{
		i = 0;
		while(is_white_space(content->lmt->file[j][i]))
			i++;
		if (content->lmt->file[j][i] == 'N' || content->lmt->file[j][i] == 'S'
		|| content->lmt->file[j][i] == 'E' || content->lmt->file[j][i] == 'W')
			ft_is_dir(content->lmt->file[j], content);
		else if (content->lmt->file[j][i] == 'F' || content->lmt->file[j][i] == 'C')
			ft_is_clr(content->lmt->file[j], content);
		else if (content->lmt->file[j][0] == '\n')
		{
			j++;
			continue ;
		}
		else
		{
			if (content->lmt->file[j] && fullfilled(content))
				return(ft_fill_map(content, &j));
			else
				ft_error("Error: components order");
		}
		j++;
	}
	if (!content->lmt->file[j])
		ft_error("empty map!");
}
