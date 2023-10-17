/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:40:21 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/17 23:10:08 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*alloc_n_trim(char *line)
{
	int		start;
	int		end;
	int		i;

	i = 0;
	if (!line[i])
		return (ft_strdup("\n"));
	start = i;
	end = ft_strlen(line) - 1;
	while (end >= 0 && is_white_space(line[end]))
		end--;
	return (ft_strjoin(ft_substr(line, start, (end + 1) - start), "\n"));
}

int	line_counter(char *av)
{
	int		fd;
	int		count;
	char	*line;

	count = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		ft_error("ERROR: map_file not found!");
	line = get_next_line(fd);
	while (line)
	{
		free(line);
		line = get_next_line(fd);
		count++;
	}
	return (count);
}

void	bottom_trim(char **file)
{
	int	end;

	end = ft_count(file) - 1;
	while (file[end][0] == '\n')
	{
		free(file[end]);
		file[end--] = 0;
	}
}

void	maper(t_cube	*content, char	*av)
{
	char	*line;
	int		fd;
	char	*res;
	int		i;

	i = 0;
	fd = open(av, O_RDONLY);
	if (fd == -1)
		ft_error("ERROR: map_file not found!");
	content->lmt->file = ft_calloc(sizeof(char *), line_counter(av) + 1);
	while (1)
	{
		line = get_next_line(fd);
		if (!line)
			break ;
		res = alloc_n_trim(line);
		content->lmt->file[i++] = res;
		free(line);
	}
	bottom_trim(content->lmt->file);
}
