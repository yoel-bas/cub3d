/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   map_init_helper.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/27 23:56:26 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/18 10:50:48 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

int	dir_op(char x)
{
	if (x == 'N' || x == 'S' || x == 'E' || x == 'W')
		return (1);
	else
		return (0);
}

int	fullfilled(t_cube *cnt)
{
	if (!cnt->cp->n || !cnt->cp->w || !cnt->cp->e || !cnt->cp->s
		|| !cnt->cl->fl || !cnt->cl->cl)
		return (0);
	return (1);
}

void	is_map(t_cube *cont, int *j)
{
	if (cont->lmt->file[*j] && fullfilled(cont))
		ft_fill_map(cont, j);
	else
		ft_error("Error: components order\n");
}

void	read_components(t_cube *cont)
{
	int	j;
	int	i;

	j = 0;
	while (cont->lmt->file[j])
	{
		i = 0;
		while (is_white_space(cont->lmt->file[j][i]))
			i++;
		if (cont->lmt->file[j][i] && dir_op(cont->lmt->file[j][i]))
			ft_is_dir(cont->lmt->file[j], cont);
		else if (cont->lmt->file[j][i] && (cont->lmt->file[j][i] == 'F'
		|| cont->lmt->file[j][i] == 'C'))
			ft_is_clr(cont->lmt->file[j], cont);
		else if (cont->lmt->file[j][0] == '\n')
		{
			j++;
			continue ;
		}
		else
			return (is_map(cont, &j));
		j++;
	}
	if (!cont->lmt->file[j])
		ft_error("empty map!\n");
}
