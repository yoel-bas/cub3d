/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:22:27 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/18 10:57:58 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	check_extension(char *path)
{
	int	i;

	if (path)
	{
		i = 0;
		while (path[i])
		{
			if (path[i] == '.'
				&& path[i + 1] == 'c'
				&& path[i + 2] == 'u'
				&& path[i + 3] == 'b'
				&& path[i + 4] == '\0')
				return ;
			i++;
		}
		ft_error("Not a '.cub' format!");
	}
	else
		ft_error("Unexistant map!");
}
