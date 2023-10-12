/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_parse.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/26 21:22:27 by melayoub          #+#    #+#             */
/*   Updated: 2023/09/26 21:22:33 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cub3d.h"

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
				&& path[i + 4] == 'e'
				&& path[i + 5] == '\0')
				return ;
			i++;
		}
		ft_error("ERROR: not a '.cube' format");
	}
	else
		ft_error("ERROR: unexistant map");
}
