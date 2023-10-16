/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/15 02:46:07 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 13:55:09 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(char *str)
{
	write (2, str, ft_strlen(str));
	write (2, "\n", 1);
	exit (1);
}

void	*ft_memset(void *str, int c, int n)
{
	int		i;
	char	*p;

	p = str;
	i = 0;
	while (i < n)
	{
		p[i] = (unsigned char)c;
		i++;
	}
	return (str);
}

char	*ft_strchr(const char *str, int c)
{
	while (*str != '\0' && *str != (char)c)
		str++;
	if (*str == (char) c)
		return ((char *)str);
	return (0);
}

int	ft_strcmp(char *s1, char *s2)
{
	int	i;

	i = 0;
	while (s1[i] != '\0' && s2[i] != '\0' && s1[i] == s2[i])
	{
		i++;
	}
	return (s1[i] - s2[i]);
}

int	is_whitesp_butnl(char c)
{
	if (c == 32 || c == 9 || (c >= 11 && c <= 13))
		return (1);
	return (0);
}
