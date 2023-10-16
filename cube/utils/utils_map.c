/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils_map.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:50:57 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 13:56:30 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	fullfilled(t_cube *cnt)
{
	if (!cnt->cp->n || !cnt->cp->w || !cnt->cp->e || !cnt->cp->s
		|| !cnt->cl->fl || !cnt->cl->cl)
		return (0);
	return (1);
}

int	line_count(char	**dbl, int *j)
{
	int	x;

	x = (*j);
	while (dbl[x])
		(x)++;
	return (x);
}

int	is_white_space(char x)
{
	if (x == 32 || (x <= 13 && x >= 9))
		return (1);
	else
		return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}
