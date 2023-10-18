/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_filler.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:45:16 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/18 11:02:40 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	line_count(char	**dbl, int *j)
{
	int	x;

	x = (*j);
	while (dbl[x])
		(x)++;
	return (x);
}

void	ft_empty_line(char *line)
{
	int	i;

	i = 0;
	while (is_white_space(line[i]))
		i++;
	if (!line[i])
		ft_error("empty line in map!\n");
	else
		return ;
}

void	ft_rearrange(t_cube *content)
{
	int	x;
	int	z;

	x = 0;
	while (content->lmt->map[x])
	{
		z = 0;
		while (content->lmt->map[x][z])
		{
			if (content->lmt->map[x][z] &&
			is_white_space(content->lmt->map[x][z]))
				content->lmt->map[x][z] = '1';
			z++;
		}
		x++;
	}
}

void	ft_fill_map(t_cube *content, int *j)
{
	int	y;
	int	len;

	y = 0;
	len = line_count(content->lmt->file, &(*j)); 
	content->lmt->map = malloc(sizeof(char **) * len);
	if (!content->lmt->map)
		ft_error("alloc error!\n");
	while (content->lmt->file[*j])
	{
		content->lmt->map[y] = ft_strdup(content->lmt->file[*j]);
		ft_empty_line (content->lmt->map[y]);
		(*j)++;
		y++;
	}
	content->lmt->map[y] = NULL;
	check_inner_extranous(content->lmt->map);
	recheck_rev(content->lmt->map);
	check_extranous_revsp(content->lmt->map);
	ft_rearrange(content);
}
