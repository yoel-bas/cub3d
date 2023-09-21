/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/20 13:54:37 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/09/11 15:20:50 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

static char	*get_line(char *str)
{
	int		i;
	int		len;
	char	*s;

	i = 0;
	if (!str[i])
		return (NULL);
	while (str[i] && str[i] != '\n')
		i++;
	len = i + 2;
	s = malloc(len);
	if (!s)
		return (NULL);
	i = 0;
	while (str[i] && str[i] != '\n')
	{
		s[i] = str[i];
		i++;
	}
	if (str[i] == '\n')
		s[i++] = '\n';
	s[i] = '\0';
	return (s);
}

static char	*full_line(char *str)
{
	char	*p;
	size_t	i;
	int		y;

	i = 0;
	y = 0;
	while (str[i] && str[i] != '\n')
		i++;
	if (str[i] == '\n')
		i++;
	if (i == ft_strlen(str))
		return (free(str), NULL);
	p = malloc((ft_strlen(str) - i) + 1);
	if (!p)
		return (NULL);
	while (str[i])
		p[y++] = str[i++];
	p[y] = '\0';
	return (free(str), str = NULL, p);
}

char	*get_next_line(int fd)
{
	char			*buff;
	static char		*str;
	char			*line;
	int				i;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	if (!str)
		str = ft_strdup("");
	buff = malloc(BUFFER_SIZE + 1);
	if (!buff)
		return (NULL);
	i = 1;
	while (i && !ft_strchr(str, '\n'))
	{
		i = read(fd, buff, BUFFER_SIZE);
		if (i < 0)
			return (free(buff), free(str), str = NULL, NULL);
		buff[i] = '\0';
		str = ft_strjoin(str, buff);
	}
	free(buff);
	line = get_line(str);
	str = full_line(str);
	return (line);
}
