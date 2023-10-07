/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: admin <admin@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/12 01:00:05 by melayoub          #+#    #+#             */
/*   Updated: 2023/10/01 18:59:18 by admin            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "cube.h"


// static void	ft_extra_line_or_none(char *all_lines)
// {
// 	int	i;

// 	i = 0;
// 	if (all_lines == (void *)0)
// 		ft_error("no map");
// 	while (all_lines[i])
// 	{
// 		if (all_lines[i] == '\n' && all_lines[i + 1] == '\0')
// 			ft_error("ERROR: extra line");
// 		i++;
// 	}
// }


int	main(int ac, char **av)
{

	t_cube	content;

	if (ac != 2)
		ft_error("ERROR: Missing or too many arguments!");
	check_extension(av[1]);
	content.cl = ft_calloc(sizeof(t_clr), 1);
	content.cp = ft_calloc(sizeof(t_cmp), 1);
	content.lmt = ft_calloc(sizeof(t_elem), 1);
	maper(&content, av[1]); 
	read_components(&content);
	if (content.lmt->map && !foreign_material(content.lmt->map))
		ft_error("foreing material");
	// check_components(content.lmt->map);
	// player_pos_dir(content.lmt->file);
	
}