/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_strmem.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/17 23:51:41 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/17 23:52:59 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_strcpy(char *src)
{
	int		i;
	size_t	len;
	char	*dest;

	len = strlen(src);
	i = 0;
	dest = (char *)malloc((len + 1) * sizeof(char));
	if (!dest)
		ft_error("Error: allocation error!");
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

char	*ft_strtrim(char *s1, char *set)
{
	int	len;

	if (!s1 || !set)
		return (NULL);
	while (*s1 && ft_strchr(set, *s1))
		s1++;
	len = ft_strlen((char *)s1);
	while (len && ft_strrchr(set, s1[len]))
		len--;
	return (ft_substr(s1, 0, len + 1));
}
