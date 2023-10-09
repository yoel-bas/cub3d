/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:56:26 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/01 17:52:46 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

void	ft_empty_line(char *line)
{
	int	i;

	i = 0;
    while(is_white_space(line[i]))
        i++;
    if (!line[i])
        ft_error("ERROR: empty line in map!");
    else
        return ;
}

char	*ft_fill(char *line, int flag)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	if (flag == 2)
		i = 2;
	else
		i = 1;
	if(!is_white_space(line[i]))
		ft_error("ERROR: incorrect dir/clr syntax!");
	while (is_white_space(line[i]))
		i++;
	start = i;
	while(line[i])
		i++;
	end = i;
	str = ft_substr(line, start, end - start);
	if (flag == 1)
		clr_parse(str);
	return (str);
}

void	ft_fill_map(t_cube *content, int *j)
{
	int y = 0;
	content->lmt->map = malloc(sizeof(char **) * line_count(content->lmt->file, &(*j)));
	if (!content->lmt->map)
		ft_error("ERROR: alloc error!");
	while (content->lmt->file[*j])
	{
		content->lmt->map[y] = ft_strcpy(content->lmt->file[*j]);
        ft_empty_line(content->lmt->map[y]);
		(*j)++;
		y++;
	}
	content->lmt->map[y] = NULL;
}

void	ft_is_clr(char *line, t_cube *cnt)
{
	if (!ft_strncmp(line, "F", 1)  && !cnt->cl->fl)
		cnt->cl->fl = ft_fill(line, 1);
	else if (!ft_strncmp(line, "C", 1) && !cnt->cl->cl)
		cnt->cl->cl = ft_fill(line, 1);
	else
		ft_error("ERROR: floor/ceiling plan!");
	free(line);
}

void	ft_is_dir(char *line, t_cube *cnt)
{
	
	if (!ft_strncmp(line, "NO", 2) && !cnt->cp->n)
		cnt->cp->n = ft_fill(line, 2);
	else if (!ft_strncmp(line, "SO", 2) && !cnt->cp->s)
		cnt->cp->s = ft_fill(line, 2);
	else if (!ft_strncmp(line, "EA", 2)  && !cnt->cp->e)
		cnt->cp->e = ft_fill(line, 2);
	else if (!ft_strncmp(line, "WE", 2) && !cnt->cp->w)
		cnt->cp->w = ft_fill(line, 2);
	else
		ft_error("ERROR: Player Orientation!");
	free(line);
}

void	read_components(t_cube *content)
{
	int j;

	j = 0;
	while(content->lmt->file[j])
	{

		if (content->lmt->file[j][0] == 'N' || content->lmt->file[j][0] == 'S'
		|| content->lmt->file[j][0] == 'E' || content->lmt->file[j][0] == 'W')
			ft_is_dir(content->lmt->file[j], content);
		else if (content->lmt->file[j][0] == 'F' || content->lmt->file[j][0] == 'C')
			ft_is_clr(content->lmt->file[j], content);
		else if (content->lmt->file[j][0] == '\n')
		{
			j++;
			continue ;
		}
		else
		{
			if (content->lmt->file[j] && fullfilled(content))
			{
				ft_fill_map(content, &j);
			 	return ;
			}
			else
				ft_error("Error: components order");
		}	
		j++;
	}
	if (!content->lmt->file[j])
		ft_error("empty map!");
}