/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:56:26 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 04:42:50 by melayoub         ###   ########.fr       */
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
	
	i = 0;
	while(is_white_space(line[i]))
		i++;
	// printf("lne: |%s|", line);
	if (flag == 2)
		i += 2;
	else
		i += 1;
	if(!is_white_space(line[i]))
		ft_error("ERROR: incorrect dir/clr syntax!");
	while (is_white_space(line[i]))
		i++;
	start = i;
	while(line[i])
		i++;
	end = i;
	str = ft_substr(line, start, end - start - 1);
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
	check_extranous_revsp(content->lmt->map);
	int x = 0;
	while(content->lmt->map[x])
	{
		int z = 0;
		while(content->lmt->map[x][z])
		{
			if(content->lmt->map[x][z] && is_white_space(content->lmt->map[x][z]))
				content->lmt->map[x][z] = '1';
			z++;
		}
		x++;
	}

}

void	ft_is_clr(char *line, t_cube *cnt)
{
	int i;

	i = 0;
	while (is_white_space(line[i]))
		i++;
	if (line[i] == 'F' && !cnt->cl->fl)
		cnt->cl->fl = ft_fill(line, 1);
	else if (line[i] == 'C' && !cnt->cl->cl)
		cnt->cl->cl = ft_fill(line, 1);
	else
		ft_error("ERROR: floor/ceiling plan!");
	free(line);
}

// char *ftstrcpy(char *src)
// {
// 	int		i;
// 	int		j;
// 	char	*dst;

// 	i = 0;
// 	j = 0;
// 	while(src[i])
// 		dst[j++] = src[i++];
// 	dst[j] = '\0';
// 	return;
// }

void	ft_is_dir(char *line, t_cube *cnt)
{
	int i = 0;
	while(is_white_space(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && !cnt->cp->n)
		cnt->cp->n = ft_fill(line, 2);
	else if (line[i] == 'S' && line[i + 1] == 'O' && !cnt->cp->s)
			cnt->cp->s = ft_fill(line, 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && !cnt->cp->e)
		cnt->cp->e = ft_fill(line, 2);
	else if (line[i] == 'W' && line[i + 1] == 'E' && !cnt->cp->w)
		cnt->cp->w = ft_fill(line, 2);
	else
		ft_error("ERROR: Player Orientation!");
	free(line);
}

void 	space_skipper(char *str)
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







// char	*ft_fill_cmp(char *line, int flag)
// {
// 	int		i;
// 	int		start;
// 	int		end;
// 	char	*str;

// 	// if (flag == 2)
// 	// 	i = 2;
// 	// else
// 	// 	i = 1;
// 	i = 2;
// 	if(!is_white_space(line[i]))
// 		ft_error("ERROR: incorrect dir/clr syntax!");
// 	while (is_white_space(line[i]))
// 		i++;
// 	start = i;
// 	while(line[i])
// 		i++;
// 	end = i;
// 	str = ft_substr(line, start, end - start);
// 	// if (flag == 1)
// 	// 	clr_parse(str);
// 	return (str);
// }

// void	ft_fill_clrs(char *line, t_cube *cnt, int flag)
// {
// 	int i;
// 	int end;
// 	int start;
// 	char *str;

// 	i = 1;
// 	if(!is_white_space(line[i]))
// 		ft_error("ERROR: incorrect dir/clr syntax!");
// 	while (is_white_space(line[i]))
// 		i++;
// 	while(line[i])
// 		i++;
// 	end = i;
// 	str = ft_substr(line, start, end - start);
// 	if (flag)
// 		clr_parse(str, cnt, 1);
// 	else
// 		clr_parse(str, cnt, 0);
// }

// void	ft_fill_map(t_cube *content, int *j)
// {
// 	int y = 0;
// 	content->lmt->map = malloc(sizeof(char **) * line_count(content->lmt->file, &(*j)));
// 	if (!content->lmt->map)
// 		ft_error("ERROR: alloc error!");
// 	while (content->lmt->file[*j])
// 	{
// 		content->lmt->map[y] = ft_strcpy(content->lmt->file[*j]);
//         ft_empty_line(content->lmt->map[y]);
// 		(*j)++;
// 		y++;
// 	}
// 	content->lmt->map[y] = NULL;
// }

// void	ft_is_clr(char *line, t_cube *cnt)
// {
// 	if (!ft_strncmp(line, "F", 1)  && !cnt->cl->fl)
// 		ft_fill_clrs(line, cnt, 0);
// 	else if (!ft_strncmp(line, "C", 1) && !cnt->cl->cl)
// 		ft_fill_clrs(line, cnt, 1);
// 	else
// 		ft_error("ERROR: floor/ceiling plan!");
// 	free(line);
// }
