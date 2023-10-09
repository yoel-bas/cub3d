/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:14:33 by melayoub          #+#    #+#             */
/*   Updated: 2023/09/21 08:47:39 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

size_t	ft_strlen(char *str)
{
	size_t	i;

	i = 0;
	while (str[i])
		i++;
	return (i);
}

char	*ft_strdup(char *src)
{
	char	*new;
	int		i;

	i = 0;
	new = (char *)malloc(sizeof(char) * ft_strlen(src) + 1);
	if (!new)
		ft_error("Error: alloc error!");
	while (*src != '\0')
		new[i++] = *src++;
	new[i] = '\0';
	return (new);
}

char	*ft_substr(char	*s, size_t start, size_t len)
{
	char	*sub;
	size_t	i;
	size_t	len_s;

	if (!s)
		return (0);
	len_s = ft_strlen(s);
	if (start >= len_s)
		return (ft_strdup(""));
	if (len_s < len)
		len = len_s;
	if (ft_strlen(s + start) < len)
		len = ft_strlen(s + start);
	sub = (char *)malloc (sizeof(char) * (len + 1));
	if (!sub)
		ft_error("Error: alloc error!");
	i = 0;
	while (i < len && s[start + i] != '\0')
	{
		sub[i] = s[start + i];
		i++;
	}
	sub[i] = '\0';
	return (sub);
}

// int	ft_strncmp(char *s1, char *s2, size_t n)
// {
// 	unsigned int	i;
// 	unsigned char	*s1_u;
// 	unsigned char	*s2_u;

// 	s1_u = (unsigned char *)s1;
// 	s2_u = (unsigned char *)s2;
// 	i = 0;
// 	while (i < n && (s1_u[i] || s2_u[i]))
// 	{
// 		if (s1_u[i] != s2_u[i])
// 			return (s1_u[i] - s2_u[i]);
// 		i++;
// 	}
// 	return (0);
// }

char	*ft_strjoin(char *str1, char *str2)
{
	int		len_s1;
	int		len_s2;
	char	*str;
	char	*start;

	if (!str1 && !str2)
		return (NULL);
	len_s1 = ft_strlen(str1);
	len_s2 = ft_strlen(str2);
	str = malloc((sizeof(char)) * (len_s1 + len_s2 + 1));
	if (!str)
		return (NULL);
	start = str;
	while (str1 && *str1)
		*str++ = *str1++;
	while (str2 && *str2)
		*str++ = *str2++;
	*str = '\0';
	return (start);
}