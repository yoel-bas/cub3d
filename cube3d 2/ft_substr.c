/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_substr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: yoel-bas <yoel-bas@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/10/17 20:34:59 by yoel-bas          #+#    #+#             */
/*   Updated: 2023/09/11 15:13:32 by yoel-bas         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

// char	*ft_substr(char  *s, unsigned int start, size_t len)
// {
// 	char			*src;
// 	unsigned int	i;
// 	unsigned int	j;

// 	i = 0;
// 	j = 0;
// 	src = 0;
// 	if (!s)
// 		return (NULL);
// 	if (start >= ft_strlen(s))
// 		return (ft_strdup(""));
// 	if (len >= ft_strlen(s + start))
// 		len = ft_strlen(s + start);
// 	src = (char *)malloc(sizeof(char) * (len + 1));
// 	if (!src)
// 		return (0);
// 	while (s[i])
// 	{
// 		if (i >= start && len > j)
// 			src[j++] = s[i];
// 		i++;
// 	}
// 	src[j] = 0;
// 	return (src);
// }
