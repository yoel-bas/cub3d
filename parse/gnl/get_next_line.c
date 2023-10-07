/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/08 17:29:00 by melayoub          #+#    #+#             */
/*   Updated: 2022/12/14 16:11:49 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include"get_next_line.h"

char	*get_next_line(int fd)
{
	static char	*stash;
	char		*line;
	char		*buf;
	int			readed;

	if (fd < 0 || BUFFER_SIZE <= 0)
		return (NULL);
	readed = 1;
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	while (!found_newline(stash) && readed)
	{
		readed = read(fd, buf, BUFFER_SIZE);
		if (readed < 0)
			return (free(stash), stash = NULL, free(buf), NULL);
		buf[readed] = '\0';
		stash = ft_strjoin(stash, buf);
	}
	free(buf);
	line = get_linee(stash);
	if (!line || line[0] == 0)
		return (free(stash), stash = NULL, free(line), NULL);
	stash = update_it(stash);
	return (line);
}

char	*ft_strjoin(char *str1, char *str2)
{
	int		len_s1;
	int		len_s2;
	int		i;
	int		j;
	char	*str;

	if (!str2 && !str1)
		return (NULL);
	if (!str1)
		return (ft_strdup(str2));
	len_s1 = ft_strlen(str1);
	len_s2 = ft_strlen(str2);
	i = 0;
	j = 0;
	str = malloc((sizeof(char)) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	while (str1[j])
		str[i++] = str1[j++];
	while (*str2)
		str[i++] = *str2++;
	str[i] = '\0';
	free(str1);
	return (str);
}

char	*get_linee(char *src)
{
	int		i;
	char	*new;

	i = 0;
	while (src[i] && src[i] != '\n')
		i++;
	new = (char *)malloc(sizeof(char) * i + 2);
	if (!new)
		return (NULL);
	i = 0;
	while (src[i] && src[i] != '\n')
	{
		new[i] = src[i];
		i++;
	}
	if (src[i] == '\n')
	{
		new[i] = src[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}