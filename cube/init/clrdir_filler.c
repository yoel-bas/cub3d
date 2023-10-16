/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clrdir_filler.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: melayoub <melayoub@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/16 14:47:49 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/16 14:54:52 by melayoub         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../cub3d.h"

char	*ft_fill(char *line, int flag)
{
	int		i;
	int		start;
	int		end;
	char	*str;

	i = 0;
	while (is_white_space(line[i]))
		i++;
	if (flag == 2)
		i += 2;
	else
		i += 1;
	if (!is_white_space(line[i]))
		ft_error("ERROR: incorrect dir/clr syntax!");
	while (is_white_space(line[i]))
		i++;
	start = i;
	while (line[i])
		i++;
	end = i;
	str = ft_substr(line, start, end - start - 1);
	if (flag == 1)
		clr_parse(str);
	return (str);
}

void	ft_is_clr(char *line, t_cube *cnt)
{
	int	i;

	i = 0;
	while (is_white_space(line[i]))
		i++;
	if (line[i] == 'F' && !cnt->cl->fl)
		cnt->cl->fl = ft_fill(line, 1);
	else if (line[i] == 'C' && !cnt->cl->cl)
		cnt->cl->cl = ft_fill(line, 1);
	else
		ft_error("ERROR: floor/ceiling plan!");
	free(line);
}

void	ft_is_dir(char *line, t_cube *cnt)
{
	int	i;

	i = 0;
	while (is_white_space(line[i]))
		i++;
	if (line[i] == 'N' && line[i + 1] == 'O' && !cnt->cp->n)
		cnt->cp->n = ft_fill(line, 2);
	else if (line[i] == 'S' && line[i + 1] == 'O' && !cnt->cp->s)
		cnt->cp->s = ft_fill(line, 2);
	else if (line[i] == 'E' && line[i + 1] == 'A' && !cnt->cp->e)
		cnt->cp->e = ft_fill(line, 2);
	else if (line[i] == 'W' && line[i + 1] == 'E' && !cnt->cp->w)
		cnt->cp->w = ft_fill(line, 2);
	else
		ft_error("ERROR: Player Orientation!");
	free(line);
}
