/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:50:57 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/18 10:59:55 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

void	ft_error(char *str)
{
	write (2, "Error:\n", 7);
	write (2, str, ft_strlen(str));
	exit (1);
}

int	is_white_space(char x)
{
	if (x == 32 || (x <= 13 && x >= 9))
		return (1);
	else
		return (0);
}

int	is_whitesp_butnl(char c)
{
	if (c == 32 || c == 9 || (c >= 11 && c <= 13))
		return (1);
	return (0);
}

int	ft_isalpha(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122))
		return (1);
	return (0);
}

int	ft_is_digit(int c)
{
	if (c >= '0' && c <= '9')
		return (1);
	else
		return (0);
}
