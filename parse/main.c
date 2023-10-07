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

void	ft_parser(t_cube *content)
{
	if (!foreign_material(content->lmt->map))
		ft_error("foreing material");
	check_top_bottom(content->lmt->map);
	check_sides(content->lmt->map);
	check_extranous_spaces(content->lmt->map);
}

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
	ft_parser(&content);	
}